/**
 * SI5351 - Simplest library for the SI5351
 */

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#include "si5351.h"
#include "i2c.h"

// ----------------------------------------------------------------------------
//  Initialize the si5351 chip via I2C
void si5351_init () {
	si5351_out (183, 192);							// set xtal load cap to 10pF
	si5351_out (3, 0);								// enable all outputs
	si5351_out (15, 0);								// select xtal as PLL input source
	_delay_ms(10);									// wait 10ms just in case
}

// ----------------------------------------------------------------------------
//  Set CLK0 Frequency in Hz; must be within [7810 Hz to 200 Mhz]
void si5351_setfrequency (uint32_t frequency, uint8_t clk) { 
	uint32_t fvco;									// VCO frequency (600-900 MHz) of PLL
	uint32_t outdivider;							// Output divider in range [4,6,8-900], even numbers preferred
	uint8_t R = 1;									// Additional Output Divider in range [1,2,4,...128]
	uint8_t a;										// "a" part of Feedback-Multiplier from XTAL to PLL in range [15,90]
	uint32_t b;										// "b" part of Feedback-Multiplier from XTAL to PLL
	float f;										// floating variable, needed in calculation
	uint32_t MS0_P1;								// Si5351a Output Divider register MS0_P1, P2 and P3 are hardcoded below
	uint32_t MSNA_P1;								// Si5351a Feedback Multisynth register MSNA_P1
	uint32_t MSNA_P2;								// Si5351a Feedback Multisynth register MSNA_P2
	uint32_t MSNA_P3;								// Si5351a Feedback Multisynth register MSNA_P3
	uint8_t r1 = 16, 
			r2 = 26, 
			r3 = 42, 
			v1 = 32, 								// This resets PLL A
			v2 =79;									// Enable output set CLK0 control register IDRV=8ma, SRC=MS0, MS0_INT on PLLA
	if (clk == 1) {
		r1 = 17;
		r2 = 34;
		r3 = 50;
		v1 = 128;									// This resets PLL B
		v2 = 111;									// Enable output set CLK1 control register IDRV=8ma, SRC=MS0, MS0_INT on PLLB
	}

	outdivider = 900000000 / frequency;				// With 900 MHz beeing the maximum internal PLL-Frequency

	while (outdivider > 900) {						// If output divider out of range (>900) use additional Output divider
		R = R * 2;
		outdivider = outdivider / 2;
	}
	if (outdivider % 2) {							// finds the even divider which delivers the intended Frequency
		outdivider--;
	}

	fvco = outdivider * R * frequency;				// Calculate the PLL-Frequency (given the even divider)

	switch (R) {									// Convert the Output Divider to the bit-setting required in register 44
		case 1: R = 0; break;						// Bits [6:4] = 000
		case 2: R = 16; break;						// Bits [6:4] = 001
		case 4: R = 32; break;						// Bits [6:4] = 010
		case 8: R = 48; break;						// Bits [6:4] = 011
		case 16: R = 64; break;						// Bits [6:4] = 100
		case 32: R = 80; break;						// Bits [6:4] = 101
		case 64: R = 96; break;						// Bits [6:4] = 110
		case 128: R = 112; break;					// Bits [6:4] = 111
	}

	a = fvco / F_XTAL;								// Multiplier to get from Quartz-Oscillator Freq. to PLL-Freq.
	f = fvco - a * F_XTAL;							// Multiplier = a+b/c
	f = f * C_FACTOR;								// this is just "int" and "float" mathematics
	f = f / F_XTAL;
	b = f;

	MS0_P1 = 128 * outdivider - 512;				// Calculation of Output Divider registers MS0_P1 to MS0_P3
													// MS0_P2 = 0 and MS0_P3 = 1; these values are hardcoded, see below

	f = 128 * b / C_FACTOR;							// Calculation of Feedback Multisynth registers MSNA_P1 to MSNA_P3
	MSNA_P1 = 128 * a + f - 512;
	MSNA_P2 = f;
	MSNA_P2 = 128 * b - MSNA_P2 * C_FACTOR; 
	MSNA_P3 = C_FACTOR;

	si5351_out (r1, 128);								// Disable output during the following register settings 
	si5351_out (r2, (MSNA_P3 & 65280) >> 8);			// Bits [15:8] of MSNA_P3 in register 26
	si5351_out (r2 + 1, MSNA_P3 & 255);					// Bits [7:0]  of MSNA_P3 in register 27
	si5351_out (r2 + 2, (MSNA_P1 & 196608) >> 16);		// Bits [17:16] of MSNA_P1 in bits [1:0] of register 28
	si5351_out (r2 + 3, (MSNA_P1 & 65280) >> 8);		// Bits [15:8]  of MSNA_P1 in register 29
	si5351_out (r2 + 4, MSNA_P1 & 255);					// Bits [7:0]  of MSNA_P1 in register 30
	si5351_out (r2 + 5, ((MSNA_P3 & 983040) >> 12) | ((MSNA_P2 & 983040) >> 16)); // Parts of MSNA_P3 und MSNA_P1
	si5351_out (r2 + 6, (MSNA_P2 & 65280) >> 8);		// Bits [15:8]  of MSNA_P2 in register 32
	si5351_out (r2 + 7, MSNA_P2 & 255);					// Bits [7:0]  of MSNA_P2 in register 33
	si5351_out (r3, 0);									// Bits [15:8] of MS0_P3 (always 0) in register 42
	si5351_out (r3 + 1, 1);								// Bits [7:0]  of MS0_P3 (always 1) in register 43
	si5351_out (r3 + 2, ((MS0_P1 & 196608) >> 16) | R); // Bits [17:16] of MS0_P1 in bits [1:0] and R in [7:4]
	si5351_out (r3 + 3, (MS0_P1 & 65280) >> 8);			// Bits [15:8]  of MS0_P1 in register 45
	si5351_out (r3 + 4, MS0_P1 & 255);					// Bits [7:0]  of MS0_P1 in register 46
	si5351_out (r3 + 5, 0);								// Bits [19:16] of MS0_P2 and MS0_P3 are always 0
	si5351_out (r3 + 6, 0);								// Bits [15:8]  of MS0_P2 are always 0
	si5351_out (r3 + 7, 0);								// Bits [7:0]   of MS0_P2 are always 0
	if (outdivider == 4) {
		si5351_out (r3 + 2, 12 | R);					// Special settings for R = 4 (see datasheet)
		si5351_out (r3 + 3, 0);							// Bits [15:8]  of MS0_P1 must be 0
		si5351_out (r3 + 4, 0);							// Bits [7:0]  of MS0_P1 must be 0
	} 
	si5351_out (177, v1);								// This resets PLL A or B
	si5351_out (r1, v2);								// Enable output set CLK0/1 control register IDRV=8ma, SRC=MS0/1, MS0_INT on PLLA/B
}

// ----------------------------------------------------------------------------
//  i2c transmission to si5351
void si5351_out (uint8_t sireg, uint8_t sidata) {
	// subroutine sends databyte to register_nbr at i2c address 192 0xC0 (si5351 register read is from address 194)
	// write a single byte (slave address 192, register sireg, value sibyte)
	i2csw_start ();
	i2csw_byte (SI5351_SADDR);
	i2csw_byte (sireg);
	i2csw_byte (sidata);
	i2csw_stop ();
}


// ============================================================================
