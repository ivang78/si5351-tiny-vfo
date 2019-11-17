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
 * ---[ENC LEFT]---+ PB3  PB2 +---[I2C/SCL]-----
 * ---[ENC RIGHT]--+ PB4  PB1 +---[I2C/SDA]-----
 * --------(-)-----+ GND  PB0 +---[ENC BUTTON]--
 *                 +----------+
 * 
 * FUSES: E:FF, H:DF, L:62
 *
 */

// ============================================================================

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <string.h>

#include "lib/i2c.h"
#include "lib/font8x16.h"
#include "lib/font16x32.h"
#include "lib/ssd1306xled.h"
#include "lib/ssd1306xledtxm.h"
#include "lib/si5351.h"

#define ENC_BTN 		PB0
#define ENC_LEFT 		PB4
#define ENC_RIGHT 		PB3

#define MIN_FREQ		100000 		// 100.000 Hz
#define MAX_FREQ		30000000 	// 30.000.000 Hz
#define BFO_OFFSET		0			// BFO OFFSET 0 Hz
#define SIDEBAND_FREQ	9999999		// If frequency lower that value default sideband is LSB else USB

#define CAL_NONE		0
#define CAL_START_FREQ	1
#define CAL_IF			2

#define MENU_COUNT		3
#define MENU_FREQ		0
#define MENU_MODE		1
#define MENU_STEP		2

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
uint8_t old_flen = 0;
uint8_t calibrate = CAL_NONE;
uint32_t enc_count = 0;
uint8_t menu_item = MENU_FREQ;
uint8_t work_sideband = SIDEBAND_LSB;

char char_buffer[11];

// ============================================================================

void update_mode () {
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
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 85, 6, "100Hz");
	} else if (st_id == 1) {
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 85, 6, " 1kHz");
	} else if (st_id == 2) {
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 85, 6, " 5kHz");
	} else if (st_id == 3) {
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 85, 6, " 1MHz");
	} 
	_delay_ms(300);
}

// ============================================================================

void update_freq (uint32_t fq, uint32_t ifq) {
	uint32_t fq0 = fq / 1000;
	utoa_cycle_sub (fq0, char_buffer);
	uint8_t flen = strlen (char_buffer);
	if (old_flen != flen) {
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 0, 0, "          ");
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 0, 2, "          ");
		if (calibrate == CAL_NONE) {
			if (fq > SIDEBAND_FREQ) {
				work_sideband = SIDEBAND_USB;
			} else {
				work_sideband = SIDEBAND_LSB;
			}
			update_mode ();
		}
		old_flen = flen;
	}
	ssd1306tx_stringxy(ssd1306xled_font16x32data, 16, (5 - flen) * 16, 0, char_buffer);
	fq0 = fq - (fq0 * 1000);
	utoa_cycle_sub (fq0, char_buffer);
	ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 102, 0, "000");
	ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 102 + (3 - strlen (char_buffer)) * 8 , 0, char_buffer);
}

// ============================================================================

void update_menu () {
	ssd1306tx_stringxy(ssd1306xled_font8x16data, 8,  0, 6, " ");
	ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 40, 6, " ");
	if (menu_item == MENU_MODE) {
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8,  0, 6, ">");
	} else if (menu_item == MENU_STEP) {
		ssd1306tx_stringxy(ssd1306xled_font8x16data, 8, 40, 6, ">");
	} 
}

// ============================================================================

void set_vfo_freq (uint32_t fq, uint32_t ifq) {
	tmp_freq = fq;
	if (work_sideband == SIDEBAND_USB) { // if F > IF use low injection for USB
		if (fq > ifq) {
			tmp_freq = fq - ifq;
		} else {
			tmp_freq = ifq - fq;
		}
	} else { // if F < IF use high injection for LSB
		tmp_freq = fq + ifq;
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

int main(void) {

	// Set input ports
	DDRB = 0x00;    // PORTB = Inputs
	// Set Inputs PB0, PB3 and PB4 to pull-up
	PORTB |= (1 << ENC_LEFT);
	PORTB |= (1 << ENC_RIGHT);
	PORTB |= (1 << ENC_BTN);

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

	// Encoder button pressed during startup, mean calibration (setup)
	if (!(PINB & (1 << ENC_BTN))) {
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

	ssd1306tx_stringxy(ssd1306xled_font8x16data,  8,  102, 2, "kHz");
	if (calibrate == CAL_START_FREQ) { // write about setup mode
		ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 48, 6, "#VFO");
		min_freq = 0; // set minimum frequency for setup to 0
	} else {
		ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 48, 6, "STEP");
	}
	update_freq (freq, ifreq);
	update_step (st_id);

	// Main Loop
	while (1) {
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
			if (menu_item == MENU_FREQ) {
				if (freq - steps[st_id] > min_freq && freq - steps[st_id] < MAX_FREQ) {
					freq = freq - steps[st_id];
				} else {
					freq = min_freq;
				}
				change_freq = 1;
			} 
		}
		// Encoder rotate right, change freq or parameters
		if (enc_right != enc_r_prev) {
			enc_r_prev = enc_right;
			if (menu_item == MENU_FREQ) {			
				if (freq + steps[st_id] < MAX_FREQ) {
					freq = freq + steps[st_id];
				} else {
					freq = MAX_FREQ;
				}					
				change_freq = 1;
			} 
			if (menu_item == MENU_STEP) {
				if (st_id < steps_count - 1) {
					st_id ++;
				} else {
					st_id = 0;
				}
				update_step ();
			} else if (menu_item == MENU_MODE) {
				if (work_sideband == SIDEBAND_USB) {
					work_sideband = SIDEBAND_LSB;
				} else {
					work_sideband = SIDEBAND_USB;
				}
				update_mode ();
				change_freq = 1;				
			} 			
		}

		// Encoder button pressed
  		if (!(PINB & (1 << ENC_BTN))) {
			if (enc_btn == 0) {
				// Change menu item
				if (menu_item < MENU_COUNT - 1) {
					menu_item ++;
				} else {
					menu_item = 0;
				}
				update_menu	();

				// Check for long delay
				enc_count ++;
				_delay_ms(500);
				if (calibrate != CAL_NONE && enc_count > 5) { // in setup mode & long press
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
						ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 48, 6, "STEP");
					}
				} else if (calibrate == CAL_NONE && enc_count > 3) { // in work mode & long press
					enc_count = 0;					
					eeprom_write_dword ((uint32_t*)0, freq);
					ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 0, 6, "SAVE");
					_delay_ms(500);	// Wait 500 ms	
					ssd1306tx_stringxy(ssd1306xled_font8x16data,  8, 0, 6, " ");
					update_mode ();
					change_freq = 1;
				}
			}
  		} else {
			enc_btn = 0;
			enc_count = 0;
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
