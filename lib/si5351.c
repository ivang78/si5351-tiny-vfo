/**
 * SI5351 - Simplest library for the SI5351
 */

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#include "si5351.h"
#include "i2c.h"

// User program may have reason to poke new values into these 3 RAM variables
uint32_t si5351bx_vcoa = (SI5351BX_XTAL*SI5351BX_MSA);  // 25mhzXtal calibrate
uint8_t  si5351bx_rdiv = 0;             // 0-7, CLK pin sees fout/(2**rdiv)
uint8_t  si5351bx_drive[3] = {3, 3, 3}; // 0=2ma 1=4ma 2=6ma 3=8ma for CLK 0,1,2
uint8_t  si5351bx_clken = 0xFF;         // Private, all CLK output drivers off

// *************  SI5315 routines - tks Jerry Gaffke, KE7ER   ***********************

// An minimalist standalone set of Si5351 routines.
// VCOA is fixed at 875mhz, VCOB not used.
// The output msynth dividers are used to generate 3 independent clocks
// with 1hz resolution to any frequency between 4khz and 109mhz.

// Usage:
// Call si5351_init() once at startup with no args;
// Call si5351_setfrequency(freq, clknum) each time one of the
// three output CLK pins is to be updated to a new frequency.
// A freq of 0 serves to shut down that output clock.

// The global variable si5351bx_vcoa starts out equal to the nominal VCOA
// frequency of 25mhz*35 = 875000000 Hz.  To correct for 25mhz crystal errors,
// the user can adjust this value.  The vco frequency will not change but
// the number used for the (a+b/c) output msynth calculations is affected.
// Example:  We call for a 5mhz signal, but it measures to be 5.001mhz.
// So the actual vcoa frequency is 875mhz*5.001/5.000 = 875175000 Hz,
// To correct for this error:     si5351bx_vcoa=875175000;

// Most users will never need to generate clocks below 500khz.
// But it is possible to do so by loading a value between 0 and 7 into
// the global variable si5351bx_rdiv, be sure to return it to a value of 0
// before setting some other CLK output pin.  The affected clock will be
// divided down by a power of two defined by  2**si5351_rdiv
// A value of zero gives a divide factor of 1, a value of 7 divides by 128.
// This lightweight method is a reasonable compromise for a seldom used feature.

void si5351_init() {                  // Call once at power-up, start PLLA
	uint32_t msxp1;
	si5351_out(149, 0);                     // SpreadSpectrum off
	si5351_out(3, si5351bx_clken);          // Disable all CLK output drivers
	si5351_out(183, ((SI5351BX_XTALPF << 6) | 0x12)); // Set 25mhz crystal load capacitance (tks Daniel KB3MUN)
	msxp1 = 128 * SI5351BX_MSA - 512;     // and msxp2=0, msxp3=1, not fractional
	uint8_t  vals[8] = {0, 1, BB2(msxp1), BB1(msxp1), BB0(msxp1), 0, 0, 0};
	si5351_outn(26, vals, 8);               // Write to 8 PLLA msynth regs
	si5351_out(177, 0x20);                  // Reset PLLA  (0x80 resets PLLB)
}

void si5351_setfrequency(uint32_t fout, uint8_t clknum) {  // Set a CLK to fout Hz
	uint32_t  msa, msb, msc, msxp1, msxp2, msxp3p2top;
	if ((fout < 500000) || (fout > 109000000)) { // If clock freq out of range
		si5351bx_clken |= 1 << clknum;      //  shut down the clock
	} else {
		msa = si5351bx_vcoa / fout;     // Integer part of vco/fout
		msb = si5351bx_vcoa % fout;     // Fractional part of vco/fout
		msc = fout;             // Divide by 2 till fits in reg
		while (msc & 0xfff00000) {
			msb = msb >> 1;
			msc = msc >> 1;
		}
		msxp1 = (128 * msa + 128 * msb / msc - 512) | (((uint32_t)si5351bx_rdiv) << 20);
		msxp2 = 128 * msb - 128 * msb / msc * msc; // msxp3 == msc;
		msxp3p2top = (((msc & 0x0F0000) << 4) | msxp2);     // 2 top nibbles
		uint8_t vals[8] = { BB1(msc), BB0(msc), BB2(msxp1), BB1(msxp1),
		                    BB0(msxp1), BB2(msxp3p2top), BB1(msxp2), BB0(msxp2)
		                  };
		si5351_outn(42 + (clknum * 8), vals, 8); // Write to 8 msynth regs
		si5351_out(16 + clknum, 0x0C | si5351bx_drive[clknum]); // use local msynth
		si5351bx_clken &= ~(1 << clknum);   // Clear bit to enable clock
	}
	si5351_out(3, si5351bx_clken);        // Enable/disable clock
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

// ----------------------------------------------------------------------------
//  i2c transmission array to si5351
void si5351_outn(uint8_t sireg, uint8_t *vals, uint8_t vcnt) {  // write array
	i2csw_start ();
	i2csw_byte (SI5351_SADDR);
	i2csw_byte (sireg);
	while (vcnt--) {
		i2csw_byte(*vals++);
	}
	i2csw_stop ();	
}


// ============================================================================
