/**
 * SSD1306xLED - Library for the SSD1306 based OLED/PLED 128x64 displays
 *
 * @author Neven Boyanov
 *
 * This is part of the Tinusaur/SSD1306xLED project.
 *
 * Copyright (c) 2018 Neven Boyanov, The Tinusaur Team. All Rights Reserved.
 * Distributed as open source software under MIT License, see LICENSE.txt file.
 * Retain in your source code the link http://tinusaur.org to the Tinusaur project.
 *
 * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled
 *
 */

// ============================================================================

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <string.h>

#include "ssd1306xled.h"
#include "ssd1306xledtxm.h"

// ----------------------------------------------------------------------------

extern void ssd1306_start_data(void);	// Initiate transmission of data
extern void ssd1306_data_byte(uint8_t);	// Transmission 1 byte of data
extern void ssd1306_stop(void);			// Finish transmission

// ----------------------------------------------------------------------------

void ssd1306tx_stringxy(const uint8_t *font_src, uint8_t font_w, uint8_t x, uint8_t y, const char s[]) {
	uint16_t j = 0, k = 0;
	while (s[k] != '\0') {
		// Convert ASCII code to font data index for different font sizes
		if (font_w == 6) { // Font width 6
			j = s[k] * 6 - 192;
		} else if (font_w == 8) { // Font width 8
			j = (s[k] << 4) - 512; 
		} else if (font_w == 16) {
			j = (s[k] << 6) - 2816; 
		}
		if (x > 120) {
			x = 0;    // Go to the next line.
			y++;
		}
		ssd1306_setpos(x, y);
		if (font_w == 6 || font_w == 8) { // Font width 6 or 8 pixels
			ssd1306_start_data();
			for (uint8_t i = 0; i < font_w; i++) {
				ssd1306_data_byte(pgm_read_byte(&font_src[j + i]));
			}
			ssd1306_stop();
			if (font_w == 8) {
				ssd1306_setpos(x, y + 1);
				ssd1306_start_data();
				for (uint8_t i = 0; i < font_w; i++) {
					ssd1306_data_byte(pgm_read_byte(&font_src[j + i + 8]));
				}
			}
			ssd1306_stop();
		} else if (font_w == 16) { // font width 16 pixels
			for (uint8_t k = 3; k > 1 ; k--) { 				// Send from top to bottom 2*16 bytes
				ssd1306_start_data();
				for (uint8_t i = 0; i < 16; i++) { 			// Send from top to bottom 16 vertical bytes
					ssd1306_data_byte(pgm_read_byte(&font_src[j + 4 * i + k]));
				}
				ssd1306_stop();
				ssd1306_setpos(x, y + 4 - k);   			// Prepare position of next row of 16 bytes
			}
			ssd1306_setpos(x, y + 2);   					// Return a row higher
			for (uint8_t k = 3; k > 1 ; k--) { 				// Send from the lower half 2*16 bytes
				ssd1306_start_data();
				for (uint8_t i = 0; i < 16; i++) { 			// Send from top to bottom 2*16 bytes
					ssd1306_data_byte(pgm_read_byte(&font_src[j + 4 * i + k - 2]));
				}
				ssd1306_stop();
				ssd1306_setpos(x, y + 6 - k);   			// Prepare position of last row of 16 bytes
			}
		}
		x += font_w;
		k++;
	}
}

// ============================================================================

void utoa_cycle_sub (uint32_t n, char s[]) {
	uint8_t i = 0;
	do { 
		s[i++] = n % 10 + '0'; 
	} 
	while ((n /= 10) > 0);
	s[i] = '\0';
	// Reversing
	uint8_t j;
	char c;
	for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
	return;
}

// ============================================================================
