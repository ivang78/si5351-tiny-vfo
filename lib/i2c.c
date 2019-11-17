/**
 * I2C - Library for the SSD1306 based OLED/PLED 128x64 displays
 *
 */

// ============================================================================
// ACKNOWLEDGEMENTS:
// - Some code and ideas initially based on "IIC_wtihout_ACK" 
//   by http://www.14blog.com/archives/1358 (defunct)
// - Init sequence used info from Adafruit_SSD1306.cpp init code.
// ============================================================================

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "i2c.h"

// ============================================================================

// NOTE: These functions are separate sub-library for handling I2C simplified output.
// NAME: I2CSW - I2C Simple Writer.
// Convenience definitions for manipulating PORTB pins
// NOTE: These definitions are used only internally by the I2CSW library
#define I2CSW_HIGH(PORT) PORTB |= (1 << PORT)
#define I2CSW_LOW(PORT) PORTB &= ~(1 << PORT)

// ----------------------------------------------------------------------------

void i2csw_start(void);
void i2csw_stop(void);
void i2csw_byte(uint8_t byte);

// ----------------------------------------------------------------------------

void i2csw_start(void) {
	DDRB |= (1 << I2C_SDA);	// Set port as output
	DDRB |= (1 << I2C_SCL);	// Set port as output
	I2CSW_HIGH(I2C_SCL);	// Set to HIGH
	I2CSW_HIGH(I2C_SDA);	// Set to HIGH
	I2CSW_LOW(I2C_SDA);		// Set to LOW
	I2CSW_LOW(I2C_SCL);		// Set to LOW
}

void i2csw_stop(void) {
	I2CSW_LOW(I2C_SCL);		// Set to LOW
	I2CSW_LOW(I2C_SDA);		// Set to LOW
	I2CSW_HIGH(I2C_SCL);	// Set to HIGH
	I2CSW_HIGH(I2C_SDA);	// Set to HIGH
	DDRB &= ~(1 << I2C_SDA);// Set port as input
}

void i2csw_byte(uint8_t byte) {
	uint8_t i;
	for (i = 0; i < 8; i++) {
		if ((byte << i) & 0x80) {
			I2CSW_HIGH(I2C_SDA);
		} else {
			I2CSW_LOW(I2C_SDA);
		}
		I2CSW_HIGH(I2C_SCL);
		I2CSW_LOW(I2C_SCL);
	}
	I2CSW_HIGH(I2C_SDA);
	I2CSW_HIGH(I2C_SCL);
	I2CSW_LOW(I2C_SCL);
}

// ============================================================================
