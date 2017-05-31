#ifndef __pcd8544_h__
#define __pcd8544_h__

#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

/*
PORT A
PB0		=	SCLK
PB1		=	DN/MOSI
PB2		=	DC
PB3		=	RST
PB4		=	SCE
*/
#define LCD_SCE_HI			PORTB |= (1<<4)
#define LCD_SCE_LO			PORTB &= ~(1<<4)
#define LCD_RST_HI			PORTB |= (1<<3)
#define LCD_RST_LO			PORTB &= ~(1<<3)
#define LCD_DC_HI			PORTB |= (1<<2)
#define LCD_DC_LO			PORTB &= ~(1<<2)
#define LCD_DN_HI			PORTB |= (1<<1)
#define LCD_DN_LO			PORTB &= ~(1<<1)
#define LCD_SCLK_HI			PORTB |= (1<<0)
#define LCD_SCLK_LO			PORTB &= ~(1<<0)
//#define LCD_BACKLIGHT_HI	PORTA |= (1<<5)
//#define LCD_BACKLIGHT_LO	PORTA &= ~(1<<5)


#define LCD_C 0
#define LCD_D 1

#define LCD_WIDTH	84
#define LCD_HEIGHT	48


const uint8_t PROGMEM ascii_table[][5] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, // 20
	0x00, 0x00, 0x5f, 0x00, 0x00, // 21 !
	0x00, 0x07, 0x00, 0x07, 0x00, // 22 "
	0x14, 0x7f, 0x14, 0x7f, 0x14, // 23 #
	0x24, 0x2a, 0x7f, 0x2a, 0x12, // 24 $
	0x23, 0x13, 0x08, 0x64, 0x62, // 25 %
	0x36, 0x49, 0x55, 0x22, 0x50, // 26 &
	0x00, 0x05, 0x03, 0x00, 0x00, // 27 '
	0x00, 0x1c, 0x22, 0x41, 0x00, // 28 (
	0x00, 0x41, 0x22, 0x1c, 0x00, // 29 )
	0x14, 0x08, 0x3e, 0x08, 0x14, // 2a *
	0x08, 0x08, 0x3e, 0x08, 0x08, // 2b +
	0x00, 0x50, 0x30, 0x00, 0x00, // 2c ,
	0x08, 0x08, 0x08, 0x08, 0x08, // 2d -
	0x00, 0x60, 0x60, 0x00, 0x00, // 2e .
	0x20, 0x10, 0x08, 0x04, 0x02, // 2f /
	0x3e, 0x51, 0x49, 0x45, 0x3e, // 30 0
	0x00, 0x42, 0x7f, 0x40, 0x00, // 31 1
	0x42, 0x61, 0x51, 0x49, 0x46, // 32 2
	0x21, 0x41, 0x45, 0x4b, 0x31, // 33 3
	0x18, 0x14, 0x12, 0x7f, 0x10, // 34 4
	0x27, 0x45, 0x45, 0x45, 0x39, // 35 5
	0x3c, 0x4a, 0x49, 0x49, 0x30, // 36 6
	0x01, 0x71, 0x09, 0x05, 0x03, // 37 7
	0x36, 0x49, 0x49, 0x49, 0x36, // 38 8
	0x06, 0x49, 0x49, 0x29, 0x1e, // 39 9
	0x00, 0x36, 0x36, 0x00, 0x00, // 3a :
	0x00, 0x56, 0x36, 0x00, 0x00, // 3b ;
	0x08, 0x14, 0x22, 0x41, 0x00, // 3c <
	0x14, 0x14, 0x14, 0x14, 0x14, // 3d =
	0x00, 0x41, 0x22, 0x14, 0x08, // 3e >
	0x02, 0x01, 0x51, 0x09, 0x06, // 3f ?
	0x32, 0x49, 0x79, 0x41, 0x3e, // 40 @
	0x7e, 0x11, 0x11, 0x11, 0x7e, // 41 A
	0x7f, 0x49, 0x49, 0x49, 0x36, // 42 B
	0x3e, 0x41, 0x41, 0x41, 0x22, // 43 C
	0x7f, 0x41, 0x41, 0x22, 0x1c, // 44 D
	0x7f, 0x49, 0x49, 0x49, 0x41, // 45 E
	0x7f, 0x09, 0x09, 0x09, 0x01, // 46 F
	0x3e, 0x41, 0x49, 0x49, 0x7a, // 47 G
	0x7f, 0x08, 0x08, 0x08, 0x7f, // 48 H
	0x00, 0x41, 0x7f, 0x41, 0x00, // 49 I
	0x20, 0x40, 0x41, 0x3f, 0x01, // 4a J
	0x7f, 0x08, 0x14, 0x22, 0x41, // 4b K
	0x7f, 0x40, 0x40, 0x40, 0x40, // 4c L
	0x7f, 0x02, 0x0c, 0x02, 0x7f, // 4d M
	0x7f, 0x04, 0x08, 0x10, 0x7f, // 4e N
	0x3e, 0x41, 0x41, 0x41, 0x3e, // 4f O
	0x7f, 0x09, 0x09, 0x09, 0x06, // 50 P
	0x3e, 0x41, 0x51, 0x21, 0x5e, // 51 Q
	0x7f, 0x09, 0x19, 0x29, 0x46, // 52 R
	0x46, 0x49, 0x49, 0x49, 0x31, // 53 S
	0x01, 0x01, 0x7f, 0x01, 0x01, // 54 T
	0x3f, 0x40, 0x40, 0x40, 0x3f, // 55 U
	0x1f, 0x20, 0x40, 0x20, 0x1f, // 56 V
	0x3f, 0x40, 0x38, 0x40, 0x3f, // 57 W
	0x63, 0x14, 0x08, 0x14, 0x63, // 58 X
	0x07, 0x08, 0x70, 0x08, 0x07, // 59 Y
	0x61, 0x51, 0x49, 0x45, 0x43, // 5a Z
	0x00, 0x7f, 0x41, 0x41, 0x00, // 5b [
	0x02, 0x04, 0x08, 0x10, 0x20, // 5c ¥
	0x00, 0x41, 0x41, 0x7f, 0x00, // 5d ]
	0x04, 0x02, 0x01, 0x02, 0x04, // 5e ^
	0x40, 0x40, 0x40, 0x40, 0x40, // 5f _
	0x00, 0x01, 0x02, 0x04, 0x00, // 60 `
	0x20, 0x54, 0x54, 0x54, 0x78, // 61 a
	0x7f, 0x48, 0x44, 0x44, 0x38, // 62 b
	0x38, 0x44, 0x44, 0x44, 0x20, // 63 c
	0x38, 0x44, 0x44, 0x48, 0x7f, // 64 d
	0x38, 0x54, 0x54, 0x54, 0x18, // 65 e
	0x08, 0x7e, 0x09, 0x01, 0x02, // 66 f
	0x0c, 0x52, 0x52, 0x52, 0x3e, // 67 g
	0x7f, 0x08, 0x04, 0x04, 0x78, // 68 h
	0x00, 0x44, 0x7d, 0x40, 0x00, // 69 i
	0x20, 0x40, 0x44, 0x3d, 0x00, // 6a j
	0x7f, 0x10, 0x28, 0x44, 0x00, // 6b k
	0x00, 0x41, 0x7f, 0x40, 0x00, // 6c l
	0x7c, 0x04, 0x18, 0x04, 0x78, // 6d m
	0x7c, 0x08, 0x04, 0x04, 0x78, // 6e n
	0x38, 0x44, 0x44, 0x44, 0x38, // 6f o
	0x7c, 0x14, 0x14, 0x14, 0x08, // 70 p
	0x08, 0x14, 0x14, 0x18, 0x7c, // 71 q
	0x7c, 0x08, 0x04, 0x04, 0x08, // 72 r
	0x48, 0x54, 0x54, 0x54, 0x20, // 73 s
	0x04, 0x3f, 0x44, 0x40, 0x20, // 74 t
	0x3c, 0x40, 0x40, 0x20, 0x7c, // 75 u
	0x1c, 0x20, 0x40, 0x20, 0x1c, // 76 v
	0x3c, 0x40, 0x30, 0x40, 0x3c, // 77 w
	0x44, 0x28, 0x10, 0x28, 0x44, // 78 x
	0x0c, 0x50, 0x50, 0x50, 0x3c, // 79 y
	0x44, 0x64, 0x54, 0x4c, 0x44, // 7a z
	0x00, 0x08, 0x36, 0x41, 0x00, // 7b {
	0x00, 0x00, 0x7f, 0x00, 0x00, // 7c |
	0x00, 0x41, 0x36, 0x08, 0x00, // 7d }
};

void LCDWrite(uint8_t dc, uint8_t data);
void gotoXY(unsigned char x, unsigned char y); //
void LCDChar(unsigned char c);//
void LCDSprite(unsigned char* str);
void LCDStr(const char* str);

void LCDString(char *characters);

void LCDClear(void);
//void LCDBacklight(uint8_t enabled);
void LCDInit(void);
void LCDBitmap(const unsigned char myarray[]); //
void LCDWriteMap(unsigned char myarray[], unsigned short map_position);


const unsigned char Menu[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xC0, 0x40, 0x00, 0x40, 0xC0, 0x40, 0x00, 0x40, 0xC0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x00, 0x00, 0x0F, 0x30, 0x10, 0x07,
0x1C, 0x30, 0x04, 0x00, 0x1C, 0x2A, 0x2A, 0x2E, 0x00, 0x20, 0x3F, 0x20, 0x1C, 0x26, 0x22, 0x26,
0x00, 0x1C, 0x32, 0x22, 0x26, 0x1C, 0x22, 0x3E, 0x20, 0x22, 0x3E, 0x20, 0x22, 0x3E, 0x20, 0x18,
0x2A, 0x2A, 0x2E, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x08, 0xF8, 0x88, 0x88, 0xD8, 0x20, 0x08, 0xF8, 0x00, 0x80, 0x40, 0x40, 0xC0,
0x00, 0x00, 0x40, 0x40, 0xC0, 0x00, 0x80, 0x40, 0x40, 0x00, 0x00, 0xC0, 0x40, 0xC0, 0x80, 0x00,
0x00, 0x00, 0xC0, 0xF0, 0x18, 0x08, 0x08, 0x08, 0x10, 0x08, 0xF8, 0x00, 0x40, 0xC0, 0x00, 0x00,
0xC0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x40, 0xC0, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0xC0,
0x40, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0x04, 0x00, 0x80, 0x80, 0x04, 0x07, 0x04,
0x03, 0x07, 0x05, 0x05, 0x01, 0x02, 0x06, 0x05, 0x07, 0x00, 0x00, 0x04, 0x05, 0x06, 0x00, 0x07,
0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06, 0x04, 0x04, 0x04, 0x02, 0x04, 0x07, 0x04,
0x04, 0x07, 0x04, 0x01, 0x06, 0x04, 0x04, 0x03, 0x00, 0x03, 0x04, 0x04, 0x06, 0x01, 0x04, 0x04,
0x05, 0x86, 0x80, 0x07, 0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0xF8, 0xFC, 0xFE, 0x8F, 0x07,
0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0x2C, 0x23, 0x2E,
0xF0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x4F, 0x89, 0x91, 0xF2, 0x00, 0x00, 0x78, 0x88, 0x88, 0x70,
0x00, 0x70, 0x88, 0x88, 0xDB, 0xEB, 0x00, 0xC8, 0xA8, 0xF8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x8F, 0xFE, 0xFC, 0xF8, 0x70, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x03, 0x07, 0x0F, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char Coke [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC,
	0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x7C, 0x3C, 0x3C, 0x9C, 0x9C, 0x5C, 0x3C, 0xFC, 0xFC,
	0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC,
	0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x7C, 0x3C, 0x3C, 0x9C, 0x5C, 0x9C, 0x1C, 0x9C, 0x9C, 0x9C, 0x1C,
	0x3C, 0x3C, 0x7C, 0xFC, 0xFC, 0x7C, 0x3C, 0xBC, 0x1C, 0xBC, 0xFC, 0x7C, 0x3C, 0xDC, 0xFC, 0xFC,
	0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x0F, 0x07, 0x83, 0xE1, 0xF8, 0x7C, 0x1E, 0x0F, 0x87, 0xA4,
	0x30, 0x07, 0x3F, 0x1F, 0x8F, 0xC7, 0xF3, 0x83, 0x67, 0x1F, 0x0F, 0xC7, 0x27, 0x13, 0x87, 0xE7,
	0xFF, 0xE7, 0x67, 0x17, 0x0F, 0x87, 0xC1, 0xF0, 0xF8, 0xFC, 0xC6, 0xD9, 0xCC, 0xE7, 0xF1, 0xFC,
	0xFF, 0xFF, 0xFF, 0x7F, 0x1E, 0x0E, 0xC0, 0x70, 0xB8, 0xC8, 0xE1, 0xF9, 0xF8, 0xFC, 0xFC, 0xFE,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x70, 0xFE, 0xFF, 0xFF, 0xC1, 0xC0,
	0xE0, 0xE7, 0xF3, 0xFC, 0xF6, 0xC0, 0xC0, 0x4C, 0x6F, 0x77, 0x63, 0x40, 0x40, 0xE4, 0xC3, 0xC0,
	0xE0, 0xF2, 0xF9, 0xFC, 0x07, 0x01, 0x00, 0xF0, 0x8E, 0xC3, 0xE1, 0x78, 0x9E, 0x20, 0x0F, 0x07,
	0xE3, 0x71, 0x2C, 0xC6, 0x00, 0x07, 0x81, 0xF0, 0x38, 0x09, 0x04, 0xC3, 0x31, 0x0C, 0x86, 0x60,
	0x38, 0xDC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7E, 0x7C, 0x78, 0x79,
	0x79, 0x79, 0x79, 0x79, 0x7D, 0x7D, 0x7D, 0x7C, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7C, 0x78, 0x78,
	0x7C, 0x7C, 0x7C, 0x7D, 0x79, 0x7B, 0x7F, 0x7F, 0x7C, 0x78, 0x78, 0x79, 0x79, 0x7D, 0x7E, 0x7F,
	0x7F, 0x78, 0x78, 0x78, 0x7C, 0x7E, 0x7F, 0x7F, 0x78, 0x78, 0x7D, 0x7C, 0x78, 0x78, 0x7C, 0x78,
	0x78, 0x78, 0x7C, 0x7A, 0x71, 0x79, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
	0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char Sprite [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04,
	0x3E, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0,
	0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80,
	0x80, 0x80, 0x40, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x08, 0x04, 0x04, 0x02, 0x81, 0xC0, 0xE0,
	0xF8, 0xFC, 0x80, 0x80, 0xC0, 0x40, 0x01, 0x03, 0x82, 0x84, 0x84, 0x84, 0x84, 0x00, 0x00, 0x00,
	0x00, 0x04, 0x04, 0x84, 0x60, 0x10, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xFF, 0x7F, 0x02, 0x00, 0x00, 0x00, 0x80, 0xC1, 0xC1, 0xE1, 0x61, 0x61, 0x33, 0x33,
	0x73, 0x73, 0x73, 0x33, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0xC1,
	0xC1, 0xC1, 0x81, 0xC0, 0xE0, 0x70, 0x70, 0x70, 0x00, 0xF0, 0xF8, 0xF8, 0xFC, 0x1C, 0x00, 0x02,
	0xE3, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0xE0, 0xF8, 0xFC, 0xFE, 0xFF, 0x07, 0x11, 0x18, 0x0C, 0x8F,
	0x47, 0x21, 0x00, 0x00, 0x00, 0xE0, 0xFE, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xC0, 0x38, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x1F, 0x3F, 0x3F, 0x7F,
	0xFC, 0xFC, 0xF8, 0xF0, 0xE0, 0x00, 0xE4, 0xFE, 0xFE, 0xFE, 0x1F, 0x03, 0x01, 0xC3, 0xFF, 0xFF,
	0x7F, 0x1E, 0xC0, 0xFF, 0xFF, 0xFF, 0x7F, 0x03, 0x00, 0x00, 0x00, 0x20, 0x3F, 0x3F, 0x3F, 0x1F,
	0x03, 0x00, 0x00, 0x0C, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x80, 0x81, 0x83, 0x83, 0x87, 0x87, 0x83,
	0x83, 0x83, 0x81, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xDF, 0xFF, 0xF8, 0xE0, 0x80, 0x00, 0x00,
	0x00, 0xC0, 0xA0, 0x90, 0x0C, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x60, 0x78, 0x70, 0x70, 0x70,
	0x70, 0x70, 0x38, 0x3C, 0x1F, 0x1F, 0x0F, 0x07, 0xC1, 0xFC, 0xFF, 0x7F, 0x3F, 0x01, 0x04, 0x06,
	0x03, 0x03, 0x81, 0x80, 0x40, 0x40, 0x23, 0x21, 0x21, 0x11, 0x10, 0x00, 0x08, 0x08, 0x08, 0x04,
	0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x02, 0x02,
	0x00, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x40, 0x40, 0x40, 0x60, 0x21, 0x10, 0x10, 0x08,
	0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char DrPepper [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xC0, 0xC0,
	0xE0, 0xE0, 0xE0, 0x70, 0x70, 0x30, 0x30, 0x70, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0x80, 0x00, 0x00,
	0x80, 0x80, 0xC0, 0xC0, 0x80, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x04, 0x04, 0x08, 0x18, 0x30, 0x70, 0xE0, 0xC0, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xE0, 0xF0, 0xF0, 0x78,
	0x78, 0x3C, 0x3C, 0xBE, 0x1E, 0x1E, 0x1E, 0x1E, 0x3E, 0x3E, 0x7E, 0xFE, 0xFC, 0xFC, 0xF8, 0xF0,
	0xC0, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC7, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x03, 0x03, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xE0, 0xC0, 0x60, 0x70, 0xF0, 0xF0,
	0xE0, 0x00, 0x01, 0x07, 0x3F, 0xFE, 0xF8, 0xC0, 0x00, 0xE0, 0xF8, 0xFC, 0x7E, 0x1F, 0x0F, 0x07,
	0x03, 0x01, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xF1,
	0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x00, 0x00, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x30, 0x30, 0xB8, 0x9C,
	0x9E, 0x0F, 0x0F, 0x47, 0xE3, 0xE0, 0xE0, 0xE0, 0x60, 0x33, 0x7B, 0xFB, 0xF9, 0xF0, 0xC0, 0x00,
	0xF8, 0xFC, 0xFE, 0xC7, 0xC3, 0xE3, 0x7F, 0x7F, 0x3F, 0x1E, 0x80, 0xE3, 0xFF, 0xFF, 0xFF, 0x80,
	0x00, 0x00, 0x41, 0x01, 0x00, 0x00, 0x00, 0x80, 0xF8, 0xFF, 0xFF, 0x0F, 0x7E, 0xFF, 0xFF, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x1C, 0x0C, 0x0E,
	0x8E, 0xE7, 0xF7, 0x33, 0x1B, 0x19, 0xB8, 0xF8, 0xF0, 0xE0, 0x00, 0x04, 0xFE, 0xFE, 0xFE, 0x86,
	0x03, 0x03, 0x87, 0xFF, 0xFF, 0xFF, 0x3C, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xE0, 0x70, 0x7F,
	0x3F, 0x1F, 0x07, 0x00, 0x03, 0x07, 0x0F, 0x0F, 0x0E, 0x4E, 0x8E, 0x06, 0xA6, 0x43, 0xE1, 0x00,
	0xB1, 0x61, 0x01, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0x7C, 0x3E, 0x1F, 0x07, 0x03, 0x00, 0x00,
	0x00, 0x03, 0x0F, 0x38, 0x60, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00, 0x00, 0x1F, 0x3F, 0x7F, 0x7C, 0x76, 0x66, 0x67, 0x73, 0x33, 0x38, 0x1C, 0x0E,
	0xFF, 0xFF, 0xFF, 0xFF, 0x0C, 0x06, 0x07, 0x03, 0x03, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x3F, 0x3F,
	0x30, 0x00, 0x00, 0x1E, 0x15, 0x00, 0x0E, 0x04, 0x07, 0x00, 0x04, 0x00, 0x02, 0x01, 0x82, 0xC1,
	0xC0, 0xE1, 0x60, 0x70, 0x38, 0x18, 0x1C, 0x0E, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
	0x07, 0x07, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x87, 0x83, 0x83, 0x83, 0x80, 0x80, 0xC0, 0xC0, 0x40, 0x40, 0x40, 0x40,
	0x60, 0x60, 0x20, 0x20, 0x20, 0x30, 0x30, 0x10, 0x18, 0x18, 0x08, 0x0C, 0x0C, 0x06, 0x06, 0x07,
	0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	};
#endif