/**
 * SI5351 - Simplest library for the SI5351
 */

#define BB0(x) ((uint8_t)x)             // Bust int32 into Bytes
#define BB1(x) ((uint8_t)(x>>8))
#define BB2(x) ((uint8_t)(x>>16))

#define SI5351_SADDR	0xC0				// I2C addess of SI5351
#define SI5351BX_XTAL 	25003200			// Frequency of Quartz-Oszillator
#define SI5351BX_MSA  	35					// VCOA is at 25mhz*35 = 875mhz
#define SI5351BX_XTALPF 3					// 1:6pf  2:8pf  3:10pf

void si5351_init ();
void si5351_setfrequency (uint32_t fout, uint8_t clknum);
void si5351_out (uint8_t sireg, uint8_t sidata);
void si5351_outn (uint8_t sireg, uint8_t *vals, uint8_t vcnt);