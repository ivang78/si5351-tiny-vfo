/**
 * SI5351 - Simplest library for the SI5351
 */

#define SI5351_SADDR 0xC0				// I2C addess of SI5351
#define F_XTAL 25003870					// Frequency of Quartz-Oszillator
#define C_FACTOR 1048575				// "C Factor" part of Feedback-Multiplier from XTAL to PLL

void si5351_init ();
void si5351_setfrequency (uint32_t frequency, uint8_t clk);
void si5351_out (uint8_t sireg, uint8_t sidata);
