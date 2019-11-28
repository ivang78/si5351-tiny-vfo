/**
 * VOLTAGE FREQUENCY OSCILLATOR AND BEAT OSCILLATIR
 * ON ATTINY85 & SSD1306xLED & SI5351
 *
 * @author R2DBH
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                  ATtiny85
 *                 +----------+   (-)--GND------
 *       (RST)-----+ PB5  Vcc +---(+)--VCC------
 * ---[ENC BUTT]---+ PB3  PB2 +---[I2C/SCL]-----
 * ---[ENC LEFT]---+ PB4  PB1 +---[I2C/SDA]-----
 * --------(-)-----+ GND  PB0 +---[ENC RIGHT]---
 *                 +----------+
 * 
 * FUSES: E:FF, H:DF, L:62
 *
 */

// ============================================================================

#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <string.h>

#include "lib/i2c.h"
#include "lib/font8x16.h"
#include "lib/font16x32.h"
#include "lib/ssd1306xled.h"
#include "lib/ssd1306xledtxm.h"
#include "lib/si5351.h"

#define ENC_BTN 		PB3
#define ENC_LEFT 		PB4
#define ENC_RIGHT 		PB0

#define MIN_FREQ		100000 		// 100.000 Hz
#define MAX_FREQ		30000000 	// 30.000.000 Hz
#define BFO_OFFSET		0			// BFO OFFSET 0 Hz
#define SIDEBAND_FREQ	9999999		// If frequency lower that value default sideband is LSB else USB

#define CAL_NONE		0
#define CAL_START_FREQ	1
#define CAL_IF			2

#define MENU_COUNT		2
#define MENU_SIDEBAND	0
#define MENU_RIT		1

#define MENU_HIDE		0
#define MENU_SHOW		1

#define MODE_RX			0
#define MODE_TX			1

#define SIDEBAND_LSB	1
#define SIDEBAND_USB	2

uint32_t freq = 7100000; 			// 7.100.000 Hz
uint32_t ifreq = 7998600;			// IF 7.998.600 Hz
uint32_t tmp_freq = 0;
uint32_t save_freq = 0;
uint32_t min_freq = MIN_FREQ;
uint32_t steps[] = {100, 1000, 5000, 1000000};
uint8_t steps_count = 4;
uint8_t st_id = 2; // 5000 Hz step
uint8_t enc_left = 0;
uint8_t enc_right = 0;
uint8_t enc_l_prev = 0;
uint8_t enc_r_prev = 0;
uint8_t enc_btn = 0;
uint8_t change_freq = 0;
uint8_t work_mode = MODE_RX;
uint8_t old_flen = 0;
uint8_t calibrate = CAL_NONE;
uint32_t enc_count = 0;
uint8_t menu_item = MENU_SIDEBAND;
uint8_t work_sideband = SIDEBAND_LSB;
uint8_t override_sideband = 0;
uint8_t menu_status = MENU_HIDE;
int32_t rit_val = 0;
uint8_t adc_value = 0;		// результат измерения АЦП (0 - button, 76 - PTT, 255 - none)

char char_buffer[11];

// ============================================================================

void update_sideband () {
	if (work_sideband == SIDEBAND_USB) {
		ssd1306tx_stringxy(ssd1306xled_font8x16data,  8,  8,   6, "USB");
	} else {
		ssd1306tx_stringxy(ssd1306xled_font8x16data,  8,  8,   6, "LSB");
	}
	_delay_ms(300);
}

// ============================================================================

void update_step () {
	if (st_id == 0) {
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 88, 4, "100Hz");
	} else if (st_id == 1) {
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 88, 4, " 1kHz");
	} else if (st_id == 2) {
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 88, 4, " 5kHz");
	} else if (st_id == 3) {
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 88, 4, " 1MHz");
	} 
	_delay_ms(300);
}

// ============================================================================

void update_freq (uint32_t fq, uint32_t ifq) {
	uint32_t fq0 = fq / 1000;
	uint32_t rit_abs = abs (rit_val);
	utoa_cycle_sub (fq0, char_buffer);
	uint8_t flen = strlen (char_buffer);
	if (old_flen != flen) {
		if (old_flen != 0) { // band changed, disable forced sideband
			override_sideband = 0;
		}
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 16, 0, "          ");
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 16, 2, "          ");
		if (calibrate == CAL_NONE) {
			if (override_sideband == 0) {
				if (fq > SIDEBAND_FREQ) {
					work_sideband = SIDEBAND_USB;
				} else {
					work_sideband = SIDEBAND_LSB;
				}
			}
			update_sideband ();
		}
		old_flen = flen;
	}
	ssd1306tx_stringxy(ssd1306xled_font16x32data, 16, (5 - flen) * 16 + 16, 0, char_buffer);
	fq0 = fq - (fq0 * 1000);
	utoa_cycle_sub (fq0, char_buffer);
	ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 104, 0, "000");
	ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 104 + (3 - strlen (char_buffer)) * 8 , 0, char_buffer);

	// Show RIT only in work mode
	if (calibrate == CAL_NONE) {
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 96 , 6, "000");
		utoa_cycle_sub (rit_abs, char_buffer);
		flen = strlen (char_buffer);
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, (3 - flen) * 8 + 96, 6, char_buffer);
		if (rit_val >= 0) {
			ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 88 , 6, "+");
		} else {
			ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 88 , 6, "-");
		}
	} else {
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 88 , 6, "    ");
	}
}

// ============================================================================

void update_menu () {
	ssd1306tx_stringxy(ssd1306xled_font8x16data, 8,  0, 6, " ");
	ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 40, 6, " ");
	if (menu_status == MENU_SHOW) {
		if (menu_item == MENU_SIDEBAND) {
			ssd1306tx_stringxy(ssd1306xled_font8x16data, 8,  0, 6, ">");
		} else if (menu_item == MENU_RIT) {
			ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 40, 6, ">");
		} 
	}
}

// ============================================================================

void set_vfo_freq (uint32_t fq, uint32_t ifq) {
	tmp_freq = fq;
	if (rit_val != 0 && work_mode == MODE_RX) { // RIT set and RX mode
		tmp_freq = tmp_freq + rit_val;
	}
	if (work_sideband == SIDEBAND_USB) { // if F > IF use low injection for USB
		if (tmp_freq > ifq) {
			tmp_freq = tmp_freq - ifq;
		} else {
			tmp_freq = ifq - tmp_freq;
		}
	} else { // if F < IF use high injection for LSB
		tmp_freq = tmp_freq + ifq;
	}
	si5351_setfrequency (tmp_freq, 0); // Set VFO frequency
}

// ============================================================================

void set_bfo_freq (uint32_t ifq) {
	// Change BFO frequency only if IF > 0
	if (ifq > 0) {
		tmp_freq = ifq + BFO_OFFSET;
		si5351_setfrequency (tmp_freq, 1); // Set BFO frequency
	}
}

// ============================================================================

uint8_t analog_read () {
	ADCSRA |=(1<<ADSC);
	while ((ADCSRA & (1<<ADIF))==0x00){;}; //дождаться окончания преобразования
	return ADCH; // забираем результат
}

// ============================================================================

int main(void) {

	// Set input ports
	DDRB = 0x00;    // PORTB = Inputs
	// Set Inputs PB0 and PB4 to pull-up
	PORTB |= (1 << ENC_LEFT)|(1 << ENC_RIGHT);
	// Set Inputs PB3 to zero 
	PORTB &= ~(1 << ENC_BTN);

	// Настройка АЦП
	ADMUX = (0<<REFS0) | (1<<ADLAR) | (1<<MUX1) | (1<<MUX0); // опорное напряжение - VCC, левое ориентирование данных, выбран вход PB3
	ADCSRA = (1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (1<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (0<<ADPS0); // включаем АЦП, одиночное преобразование, прескалер - 16
	ADCSRB = (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0); // выбор источника для старта преобразования - ручной запуск
	DIDR0 |= (1 << ENC_BTN); // запрещаем цифровой вход на ноге аналогового входа

	tmp_freq = eeprom_read_dword ((uint32_t*)0);
	if (tmp_freq >= MIN_FREQ && tmp_freq <= MAX_FREQ) {
		freq = tmp_freq;
	}
	tmp_freq = eeprom_read_dword ((uint32_t*)3);
	if (tmp_freq >= 0 && tmp_freq <= MAX_FREQ) {
		ifreq = tmp_freq;
	}
	if (freq > SIDEBAND_FREQ) {
		work_sideband = SIDEBAND_USB;
	}
	override_sideband = eeprom_read_byte ((uint8_t*)6);
	if (override_sideband == SIDEBAND_LSB || override_sideband == SIDEBAND_USB) {
		work_sideband = override_sideband;
		override_sideband = 1;
	}

	adc_value = analog_read ();
	// Encoder button pressed during startup, mean calibration (setup)
	if (adc_value >= 0 && adc_value <= 10) {
		calibrate = CAL_START_FREQ;
		_delay_ms(500);	// Wait 500 ms
	}

	// VFO initialization
	_delay_ms(40);	// Small delay might be necessary
	si5351_init ();
	set_vfo_freq (freq, ifreq); // Set VFO frequency
	set_bfo_freq (ifreq); // Set BFO frequency

	// Display initialization
	_delay_ms(40);	// Small delay might be necessary
	ssd1306_init();
	ssd1306_clear();

	ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 104, 2, "kHz");
	ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 48,  4, "STEP");
	ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 0,   0, "}");

	if (calibrate == CAL_START_FREQ) { // write about setup mode
		ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 48, 6, "#VFO");
		min_freq = 0; // set minimum frequency for setup to 0
	} else {
		ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 48, 6, "RIT ");
	}
	update_freq (freq, ifreq);
	update_step (st_id);

	// Main Loop
	while (1) {
		// Read ADC
		adc_value = analog_read ();

		// Encoder left or right
		enc_left = !(PINB & (1 << ENC_LEFT));
		enc_right = !(PINB & (1 << ENC_RIGHT));
		if (enc_left == enc_right) {
			enc_l_prev = enc_left;
			enc_r_prev = enc_right;
		}
		// Encoder rotate left, change freq
		if (enc_left != enc_l_prev) {
			enc_l_prev = enc_left;
			if (menu_status == MENU_HIDE) {
				if (freq - steps[st_id] > min_freq && freq - steps[st_id] < MAX_FREQ) {
					freq = freq - steps[st_id];
				} else {
					freq = min_freq;
				}
				change_freq = 1;
			} else if (menu_status == MENU_SHOW && menu_item == MENU_SIDEBAND) {
				if (work_sideband == SIDEBAND_USB) {
					work_sideband = SIDEBAND_LSB;
				} else {
					work_sideband = SIDEBAND_USB;
				}
				update_sideband ();
				change_freq = 1;
			} else if (menu_status == MENU_SHOW && menu_item == MENU_RIT) {
				if (rit_val > -600) {
					rit_val = rit_val - 100;
					change_freq = 1;
				}
			} 
		}
		// Encoder rotate right, change freq or parameters
		if (enc_right != enc_r_prev) {
			enc_r_prev = enc_right;
			if (menu_status == MENU_HIDE) {			
				if (freq + steps[st_id] < MAX_FREQ) {
					freq = freq + steps[st_id];
				} else {
					freq = MAX_FREQ;
				}					
				change_freq = 1;
			} else if (menu_status == MENU_SHOW && menu_item == MENU_SIDEBAND) {
				if (work_sideband == SIDEBAND_USB) {
					work_sideband = SIDEBAND_LSB;
				} else {
					work_sideband = SIDEBAND_USB;
				}
				update_sideband ();
				change_freq = 1;
			} else if (menu_status == MENU_SHOW && menu_item == MENU_RIT) {
				if (rit_val < 600) {
					rit_val = rit_val + 100;
					change_freq = 1;
				}
			}
		}

		// Encoder button pressed
  		if (adc_value >= 0 && adc_value <= 10) {
  			if (enc_count == 0) {
  				if (menu_status == MENU_HIDE) { // Change step
					if (st_id < steps_count - 1) {
						st_id ++;
					} else {
						st_id = 0;
					}
					update_step ();
				} else if (menu_status == MENU_SHOW) { // Change menu item
					if (menu_item < MENU_COUNT - 1) {
						menu_item ++;
					} else {
						menu_item = MENU_SIDEBAND;
						menu_status = MENU_HIDE;
						eeprom_write_dword ((uint32_t*)0, freq);
						eeprom_write_byte ((uint8_t*)6, work_sideband);
					}
					update_menu ();
				}
			}
			// Check for long delay
			enc_count ++;
			_delay_ms(100);
			if (calibrate != CAL_NONE && enc_count > 20) { // in setup mode & long press
				enc_count = 0;
				if (calibrate == CAL_START_FREQ) { // setup start frequency
					eeprom_write_dword ((uint32_t*)0, freq);
					save_freq = freq;
					freq = ifreq;
					calibrate = CAL_IF;
					change_freq = 1;
					ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 48, 6, "#BFO");
				} else if (calibrate == CAL_IF) { // setup IF frequency
					eeprom_write_dword ((uint32_t*)3, freq);
					ifreq = freq;
					freq = save_freq;
					calibrate = CAL_NONE;
					change_freq = 1;
					min_freq = MIN_FREQ; // set minimum frequency for working value
					ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 48, 6, "RIT ");
					update_sideband ();
				}
			} else if (calibrate == CAL_NONE && enc_count > 20) { // in work mode & long press
				menu_item = MENU_SIDEBAND;
				menu_status = MENU_SHOW;
				update_menu ();
			}
  		} else {
			enc_count = 0;
		}

  		if (adc_value >= 60 && adc_value <= 90 && work_mode == MODE_RX) { // PTT pressed and last mode was RX
  			work_mode = MODE_TX;
			ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 0, 0, " ");
			ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 0, 2, "{");
			change_freq = 1;
  		} else if ((adc_value < 60 || adc_value > 90) && work_mode == MODE_TX) { // PTT depressed and last mode was TX 
  			work_mode = MODE_RX;
			ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 0, 0, "}");
			ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 0, 2, " ");
			change_freq = 1;
  		}  

		if (change_freq) {
			if (calibrate == CAL_IF) { // if calibrating IF set BFO value
				set_bfo_freq (freq);
			} else { // else set VFO value
				set_vfo_freq (freq, ifreq);
			}
			update_freq (freq, ifreq);
			change_freq = 0;
		}

	}
	return 0; 
}
