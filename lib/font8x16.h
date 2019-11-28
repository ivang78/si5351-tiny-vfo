/**
 * Arial like font 8X16 with special symbols
 * SSD1306xLED - Library for the SSD1306 based OLED/PLED 128x64 displays
 */

// ============================================================================

#include <avr/pgmspace.h>

// ----------------------------------------------------------------------------

/* Standard ASCII 8x16 font */
const uint8_t ssd1306xled_font8x16data [] PROGMEM = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //    32 ' '
	0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1B,0x00,0x00,0x00,0x00, //    33 '!'
	0x00,0x00,0x78,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //    34 '"'
	0x00,0x40,0xF0,0x40,0x40,0xF0,0x40,0x00,0x00,0x02,0x0F,0x02,0x02,0x0F,0x02,0x00, //    35 '#'
	0x00,0xC0,0x20,0xF0,0x20,0x20,0x00,0x00,0x00,0x08,0x09,0x1F,0x09,0x06,0x00,0x00, //    36 '$'
	0x00,0x30,0x48,0x30,0xC0,0x20,0x18,0x00,0x00,0x18,0x04,0x03,0x0C,0x12,0x0C,0x00, //    37 '%'
	0x00,0x60,0x90,0x90,0x60,0x00,0x00,0x00,0x00,0x0E,0x11,0x11,0x12,0x0C,0x12,0x00, //    38 '&'
	0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //    39 '''
	0x00,0x00,0x00,0xC0,0x30,0x08,0x04,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00, //    40 '('
	0x00,0x04,0x08,0x30,0xC0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00, //    41 ')'
	0x00,0x00,0x40,0x80,0x80,0x40,0x00,0x00,0x00,0x01,0x05,0x03,0x03,0x05,0x01,0x00, //    42 '*'
	0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x0F,0x01,0x01,0x01, //    43 '+'
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x30,0x18,0x08,0x00,0x00,0x00, //    44 ','
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00, //    45 '-'
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x38,0x10,0x00,0x00,0x00, //    46 '.'
	0x00,0x00,0x00,0x00,0xC0,0x30,0x0C,0x00,0x00,0x30,0x0C,0x03,0x00,0x00,0x00,0x00, //    47 '/'
	0x00,0xE0,0x10,0x08,0x88,0x10,0xE0,0x00,0x00,0x07,0x08,0x11,0x10,0x08,0x07,0x00, //    48 '0'
	0x00,0x40,0x20,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x00, //    49 '1'
	0x00,0x30,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x18,0x14,0x12,0x11,0x10,0x10,0x00, //    50 '2'
	0x00,0x10,0x08,0x88,0x88,0x88,0x70,0x00,0x00,0x0C,0x10,0x10,0x10,0x10,0x0F,0x00, //    51 '3'
	0x00,0x00,0xC0,0x30,0x08,0xF8,0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x1F,0x02,0x00, //    52 '4'
	0x00,0xF8,0x48,0x48,0x48,0x48,0x88,0x00,0x00,0x0C,0x10,0x10,0x10,0x10,0x0F,0x00, //    53 '5'
	0x00,0xF0,0x08,0x88,0x88,0x88,0x10,0x00,0x00,0x0F,0x11,0x10,0x10,0x10,0x0F,0x00, //    54 '6'
	0x00,0x08,0x08,0x08,0x88,0x68,0x18,0x00,0x00,0x00,0x18,0x06,0x01,0x00,0x00,0x00, //    55 '7'
	0x00,0x70,0x88,0x88,0x88,0x88,0x70,0x00,0x00,0x0F,0x10,0x10,0x10,0x10,0x0F,0x00, //    56 '8'
	0x00,0xF0,0x08,0x08,0x08,0x88,0xF0,0x00,0x00,0x08,0x11,0x11,0x11,0x10,0x0F,0x00, //    57 '9'
	0x00,0x00,0x40,0xE0,0x40,0x00,0x00,0x00,0x00,0x00,0x10,0x38,0x10,0x00,0x00,0x00, //    58 ':'
	0x00,0x00,0x40,0xE0,0x40,0x00,0x00,0x00,0x00,0x40,0x30,0x18,0x08,0x00,0x00,0x00, //    59 ';'
	0x00,0x00,0x80,0x40,0x20,0x10,0x00,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x00,0x00, //    60 '<'
	0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x00, //    61 '='
	0x00,0x00,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x00,0x10,0x08,0x04,0x02,0x01,0x00, //    62 '>'
	0x00,0x08,0x08,0x88,0x48,0x30,0x00,0x00,0x00,0x00,0x1B,0x00,0x00,0x00,0x00,0x00, //    63 '?'
	0x00,0xE0,0x10,0x88,0x48,0x48,0xF0,0x00,0x00,0x07,0x08,0x13,0x14,0x14,0x07,0x00, //    64 '@'
	0x00,0xF0,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x1F,0x01,0x01,0x01,0x01,0x1F,0x00, //    65 'A'
	0x00,0xF8,0x88,0x88,0x88,0xF0,0x00,0x00,0x00,0x1F,0x10,0x10,0x10,0x10,0x0F,0x00, //    66 'B'
	0x00,0xF0,0x08,0x08,0x08,0x08,0x30,0x00,0x00,0x0F,0x10,0x10,0x10,0x10,0x0C,0x00, //    67 'C'
	0x00,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x00,0x1F,0x10,0x10,0x10,0x08,0x07,0x00, //    68 'D'
	0x00,0xF8,0x88,0x88,0x88,0x88,0x08,0x00,0x00,0x1F,0x10,0x10,0x10,0x10,0x10,0x00, //    69 'E'
	0x00,0xF8,0x88,0x88,0x88,0x88,0x08,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00, //    70 'F'
	0x00,0xF0,0x08,0x08,0x08,0x08,0x30,0x00,0x00,0x0F,0x10,0x10,0x11,0x11,0x0F,0x00, //    71 'G'
	0x00,0xF8,0x80,0x80,0x80,0x80,0xF8,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x1F,0x00, //    72 'H'
	0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x10,0x10,0x1F,0x10,0x10,0x00,0x00, //    73 'I'
	0x00,0x00,0x00,0x08,0x08,0x08,0xF8,0x00,0x00,0x0C,0x10,0x10,0x10,0x10,0x0F,0x00, //    74 'J'
	0x00,0xF8,0x80,0x40,0xA0,0x10,0x08,0x00,0x00,0x1F,0x00,0x00,0x01,0x06,0x18,0x00, //    75 'K'
	0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x10,0x10,0x10,0x10,0x10,0x00, //    76 'L'
	0x00,0xF8,0x30,0xC0,0x00,0xC0,0x30,0xF8,0x00,0x1F,0x00,0x00,0x03,0x00,0x00,0x1F, //    77 'M'
	0x00,0xF8,0x30,0xC0,0x00,0x00,0xF8,0x00,0x00,0x1F,0x00,0x00,0x03,0x0C,0x1F,0x00, //    78 'N'
	0x00,0xF0,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x0F,0x10,0x10,0x10,0x10,0x0F,0x00, //    79 'O'
	0x00,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x1F,0x01,0x01,0x01,0x01,0x00,0x00, //    80 'P'
	0x00,0xF0,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x0F,0x10,0x10,0x1C,0x30,0x2F,0x00, //    81 'Q'
	0x00,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x1F,0x01,0x03,0x05,0x09,0x10,0x00, //    82 'R'
	0x00,0x70,0x88,0x88,0x08,0x08,0x10,0x00,0x00,0x08,0x10,0x10,0x11,0x11,0x0E,0x00, //    83 'S'
	0x00,0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x00, //    84 'T'
	0x00,0xF8,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0x0F,0x10,0x10,0x10,0x10,0x0F,0x00, //    85 'U'
	0x00,0xF8,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0x01,0x06,0x18,0x18,0x06,0x01,0x00, //    86 'V'
	0x00,0xF8,0x00,0x00,0x80,0x00,0x00,0xF8,0x00,0x07,0x18,0x06,0x01,0x06,0x18,0x07, //    87 'W'
	0x00,0x18,0x60,0x80,0x80,0x60,0x18,0x00,0x00,0x18,0x06,0x01,0x01,0x06,0x18,0x00, //    88 'X'
	0x00,0x78,0x80,0x00,0x00,0x80,0x78,0x00,0x00,0x00,0x00,0x01,0x1F,0x00,0x00,0x00, //    89 'Y'
	0x00,0x08,0x08,0x08,0x88,0x68,0x18,0x00,0x00,0x18,0x14,0x13,0x10,0x10,0x10,0x00, //    90 'Z'
	0x00,0x00,0x00,0xFC,0x04,0x04,0x04,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00, //    91 '['
	0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0C,0x30,0x00, //    92 '\'
	0x00,0x04,0x04,0x04,0xFC,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00, //    93 ']'
	0x00,0x20,0x10,0x08,0x08,0x10,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //    94 '^'
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x00, //    95 '_'
	0x00,0x00,0x08,0x18,0x30,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //    96 '`'
	0x00,0x00,0x40,0x40,0x40,0x40,0x80,0x00,0x00,0x0E,0x11,0x11,0x11,0x09,0x1F,0x00, //    97 'a'
	0x00,0xF8,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x1F,0x08,0x10,0x10,0x10,0x0F,0x00, //    98 'b'
	0x00,0x80,0x40,0x40,0x40,0x40,0x80,0x00,0x00,0x0F,0x10,0x10,0x10,0x10,0x08,0x00, //    99 'c'
	0x00,0x80,0x40,0x40,0x40,0x80,0xF8,0x00,0x00,0x0F,0x10,0x10,0x10,0x08,0x1F,0x00, //   100 'd'
	0x00,0x80,0x40,0x40,0x40,0x40,0x80,0x00,0x00,0x0F,0x12,0x12,0x12,0x12,0x13,0x00, //   101 'e'
	0x00,0x00,0xF0,0x08,0x08,0x08,0x10,0x00,0x00,0x01,0x1F,0x01,0x01,0x01,0x00,0x00, //   102 'f'
	0x00,0x80,0x40,0x40,0x40,0x80,0xC0,0x00,0x00,0x47,0x88,0x88,0x88,0x84,0x7F,0x00, //   103 'g'
	0x00,0xF8,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x1F,0x00, //   104 'h'
	0x00,0x00,0x40,0x40,0xD8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x00, //   105 'i'
	0x00,0x00,0x00,0x40,0x40,0xD8,0x00,0x00,0x00,0x20,0x40,0x40,0x40,0x3F,0x00,0x00, //   106 'j'
	0x00,0xF8,0x00,0x00,0x80,0x40,0x00,0x00,0x00,0x1F,0x02,0x03,0x04,0x08,0x10,0x00, //   107 'k'
	0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x10,0x10,0x10,0x00,0x00, //   108 'l'
	0x00,0xC0,0x40,0x40,0x80,0x40,0x40,0x80,0x00,0x1F,0x00,0x00,0x07,0x00,0x00,0x1F, //   109 'm'
	0x00,0xC0,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x1F,0x00, //   110 'n'
	0x00,0x80,0x40,0x40,0x40,0x40,0x80,0x00,0x00,0x0F,0x10,0x10,0x10,0x10,0x0F,0x00, //   111 'o'
	0x00,0xC0,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0xFF,0x04,0x08,0x08,0x08,0x07,0x00, //   112 'p'
	0x00,0x80,0x40,0x40,0x40,0x80,0xC0,0x00,0x00,0x07,0x08,0x08,0x08,0x04,0xFF,0x00, //   113 'q'
	0x00,0xC0,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00, //   114 'r'
	0x00,0x80,0x40,0x40,0x40,0x40,0x80,0x00,0x00,0x09,0x12,0x12,0x12,0x12,0x0C,0x00, //   115 's'
	0x00,0x40,0xF0,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x0F,0x10,0x10,0x10,0x08,0x00, //   116 't'
	0x00,0xC0,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x0F,0x10,0x10,0x10,0x08,0x1F,0x00, //   117 'u'
	0x00,0xC0,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x01,0x06,0x18,0x18,0x06,0x01,0x00, //   118 'v'
	0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x0F,0x10,0x08,0x07,0x08,0x10,0x0F, //   119 'w'
	0x00,0x40,0x80,0x00,0x00,0x80,0x40,0x00,0x00,0x10,0x08,0x05,0x05,0x08,0x10,0x00, //   120 'x'
	0x00,0xC0,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x47,0x88,0x88,0x88,0x84,0x7F,0x00, //   121 'y'
	0x00,0x40,0x40,0x40,0x40,0x40,0xC0,0x00,0x00,0x10,0x18,0x14,0x12,0x11,0x10,0x00, //   122 'z'
	0xf0,0x0c,0x02,0xf1,0x08,0x04,0xe0,0x10,0x03,0x0c,0x10,0x23,0x04,0x08,0x01,0x02, //   123 '{' (antenna)
	0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00, //   124 '|'
	0xf8,0x08,0x08,0xf8,0x04,0x02,0x01,0xff,0x0f,0x08,0x08,0x0f,0x10,0x20,0x40,0x7f, //   125 '}' (speaker)
	0x00,0x60,0x10,0x10,0x20,0x40,0x40,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //   126 '~'
};

// ============================================================================
