/**
 * I2C - Library for the SSD1306 based OLED/PLED 128x64 displays
 *
 */

// ============================================================================

#define I2C_SCL		PB2   		// 	-----> [SCL]	Pin 3 on the SSD1306 display board
#define I2C_SDA		PB1   		// 	-----> [SDA]	Pin 4 on the SSD1306 display board

void i2csw_start(void);
void i2csw_stop(void);
void i2csw_byte(uint8_t byte);
