/* ****************************************************************************
   * Name: Unified graphic library for monochromatic LCD displays - header    *
   * Author: saper_2                                                          *
   * Contact: nolinno11 gmail com                                             *
   * Date: 30.10.2013                                                         *
   * Version: 0.2                                                             *
   * License:                                                                 *
   *   You are free to use this library in any kind project, but at least     *
   *   send me a info that YOU are using it. I'll be happy for memory :)      *
   * About: :)                                                                *
   *   'Unified' sound nice :) , well with "unification" this might not have  *
   *   any commons but I'm going to rewrite all my lcd drivers so I can use   *
   *   one library with many displays (so far I have placed graphic functions *
   *   inside driver files and with every one lcd function names were         *
   *   different -_- ).                                                       *
   *                                                                          *
   * Bugs:                                                                    *
   * - v0.2  - Line function seems broken                                     *
   * - v0.2  - Fixed some declarations so this lib can work with Atmel        *
   *           AVR Toolchain (tested on version 3.4.2)                        *
   * - v0.1  - Filling circle is "unfinished" (there are left "unfilled"      *
   *           pixels inside circle)                                          *
   *                                                                          *
   **************************************************************************** */
#ifndef _LCD_MONO_GRAPHIC_ROUTINES_H_
#define _LCD_MONO_GRAPHIC_ROUTINES_H_

// basic configuration:
// setup lcd init routine (should be without parameters)

// enter name of lcd driver header file (with quotes)
#define gd_lcd_driver_header_file "st7588.h"
#include gd_lcd_driver_header_file

// lcd dimensions
#define GD_WIDTH ST_LCD_WIDTH
#define GD_HEIGHT ST_LCD_HEIGHT

// init can be defined with parameters
#define gd_init_lcd_routine st7588_init()

// set pixel can not have parameters , and also must have parameters in right order (uint8(16)_t x,uint8(16)_t y, uint8_t Pixel_mode)
#define gd_set_pixel_lcd_routine st_fb_setPix

// set position function assign, like befor, parameters must be in order (uint8(16)_t x, uint8(16)_t y), 
//   y take all range from lcd height so if lcd uses "pages" then it must be calculated inside driver
//#define gd_set_lcd_pos_routine sed_setPos - NOT USED
// filling display , also need a parameter with filling pattern (uint8_t pattern)
#define gd_fill_lcd_routine(x) st_fb_cls(x)
// pixel states (shoud be same as states in lcd header driver file)
#define GD_PX_ON ST_PX_ON
#define GD_PX_OFF ST_PX_OFF
#define GD_PX_XOR ST_PX_XOR
// alias names
	#define GD_PXON GD_PX_ON
	#define GD_ON GD_PX_ON
	#define PX_ON GD_PX_ON
	#define PIX_ON GD_PX_ON

	#define GD_PXOFF GD_PX_OFF
	#define GD_OFF GD_PX_OFF
	#define PX_OFF GD_PX_OFF
	#define PIX_OFF GD_PX_OFF

	#define GD_PXXOR GD_PX_XOR
	#define GD_XOR GD_PX_XOR
	#define PX_XOR GD_PX_XOR
	#define PIX_XOR GD_PX_XOR
// additional pixel states
#define GD_TXT_ON_BG_OFF 10
#define GD_TXT_OFF_BG_ON 11
// function aliases
#define gd_setPix gd_set_pixel_lcd_routine
#define gd_pix gd_set_pixel_lcd_routine
// function controls
#define GD_FUNC_LINE 0 // line function broken.
#define GD_FUNC_LINE_H 0
#define GD_FUNC_LINE_V 0
#define GD_FUNC_RECT 1
#define GD_FUNC_RECT_FILL 1
#define GD_FUNC_CIRCLE 1
#define GD_FUNC_CIRCLE_FILL 0 // not working well...
#define GD_FUNC_ELIPSE 0 // not working so well - have limitations
#define GD_FUNC_CHAR 0
#define GD_FUNC_STR 0
#define GD_FUNC_STR_P 1
#define GD_FUNC_DEC 0
#define GD_FUNC_HEX_BYTE 0
#define GD_FUNC_LOAD 1
// for text functions, you have to define font file name:
//#define gd_lcd_single_font_file_name "font6x7-hd44780-pl.h"
#define gd_lcd_single_font_file_name "font6x7-hd44780-pl.h"

// gd_lineH(x, y, width, px_mode);
// gd_lineV(x, y, height, px_mode);
// gd_line(x1, y1, x2, y2, px_mode);
// gd_rect(x1, y1, x2, y2, px_mode);
// gd_rect_fill(x1, y1, x2, y2, px_mode);
// gd_circle(xc, yc, radius, px_mode);
// gd_circle_fill(xc, yc, radius, px_mode); - this not working so well...
// gd_elipse(cx, cy, radius_x, radius_y, px_mode);
// uint8_t gd_char(x, y, char chr, chr_mode/px_mode) - returns char width
// uint8/16_t gd_str(x, y, char* str, txt_mode/px_mode) - returns x_pos of end of text
// uint8/16_t gd_strP(x, y, prog_char* str, txt_mode/px_mode) - returns x_pos of end of text
// uint8/16_t gd_dec(x, y, int val, txt_mode/px_mode); - returns x_pos of end of text
// uint8/16_t gd_hexByte(x, y, uint8_t val, txt_mode/px_mode); - returns x_pos of end of text
// gd_load(prog_uint8_t* pData, x, y, width, height, px_mode);

// those preporcessors definitions selects what kind variable should be used to address x and y position \->
//   (uin8_t can take up to 255 pixels so if lcd have 256px width then it have to be 16 bit variable)
// x:
#if GD_WIDTH > 255
	#define gd_axe_x_kind uint16_t
	#define gd_axe_x_kinds int16_t
#else
	#define gd_axe_x_kind uint8_t
	#define gd_axe_x_kinds int8_t
#endif
// y same:
#if GD_HEIGHT > 255
	#define gd_axe_y_kind uint16_t
	#define gd_axe_y_kinds int16_t
#else
	#define gd_axe_y_kind uint8_t
	#define gd_axe_y_kinds int8_t
#endif

void gd_init(void);
void gd_fill(uint8_t pattern);
#define gd_cls() gd_fill(0x00)

#if ( (GD_FUNC_LINE_H==1) || (GD_FUNC_RECT==1) || (GD_FUNC_LINE==1) )
void gd_lineH(gd_axe_x_kind x, gd_axe_y_kind y, gd_axe_x_kind w, uint8_t px_mode);
#endif

#if ( (GD_FUNC_LINE_V==1) || (GD_FUNC_RECT==1) || (GD_FUNC_LINE==1))
void gd_lineV(gd_axe_x_kind x, gd_axe_y_kind y, gd_axe_y_kind h, uint8_t px_mode);
#endif

#if GD_FUNC_LINE == 1
void gd_line(gd_axe_x_kind x1, gd_axe_y_kind y1, gd_axe_x_kind x2, gd_axe_y_kind y2, uint8_t px_mode);
#endif

#if GD_FUNC_RECT == 1
void gd_rect(gd_axe_x_kind x1, gd_axe_y_kind y1, gd_axe_x_kind x2, gd_axe_y_kind y2, uint8_t px_mode);
#endif

#if GD_FUNC_RECT_FILL == 1
void gd_rect_fill(gd_axe_x_kind x1, gd_axe_y_kind y1, gd_axe_x_kind x2, gd_axe_y_kind y2, uint8_t px_mode);
#endif

#if ((GD_FUNC_CIRCLE == 1) || (GD_FUNC_CIRCLE_FILL == 1))
void gd_circle(gd_axe_x_kind xc, gd_axe_x_kind yc, gd_axe_x_kind radius, uint8_t px_mode);
#endif

#if (GD_FUNC_CIRCLE_FILL == 1)
// not working correctly....
void gd_circle_fill(gd_axe_x_kind xc, gd_axe_x_kind yc, gd_axe_x_kind radius, uint8_t px_mode);
#endif

#if (GD_FUNC_ELIPSE == 1)
// A Fast Bresenham Type Algorithm For Drawing Ellipses by John Kennedy
// well fast on int32 signed numbers on avr... anyway it can take radius(es) up to 50px (or 45px) in sum 
// this function consume about 1,5k flash!
void gd_elipse(gd_axe_x_kind cx, gd_axe_y_kind cy, gd_axe_x_kind rx, gd_axe_y_kind ry, uint8_t px_mode);
#endif

#if ( (GD_FUNC_CHAR == 1) || (GD_FUNC_STR==1) || (GD_FUNC_STR_P==1) || (GD_FUNC_HEX_BYTE==1) )
uint8_t gd_char(gd_axe_x_kind x, gd_axe_x_kind y, char znak, uint8_t chr_mode);
#endif

#if ( (GD_FUNC_STR == 1) || (GD_FUNC_DEC==1) )
gd_axe_x_kind gd_str(gd_axe_x_kind x, gd_axe_y_kind y, char* str, uint8_t txt_mode);
#endif

#if GD_FUNC_STR_P == 1
gd_axe_x_kind gd_strP(gd_axe_x_kind x, gd_axe_y_kind y, const char* str, uint8_t txt_mode);
#endif

#if GD_FUNC_DEC == 1
gd_axe_x_kind gd_dec(gd_axe_x_kind x, gd_axe_y_kind y, int val, uint8_t txt_mode);
#endif

#if GD_FUNC_HEX_BYTE == 1
gd_axe_x_kind gd_hexByte(gd_axe_x_kind x, gd_axe_y_kind y, uint8_t val, uint8_t txt_mode);
#endif

#if GD_FUNC_LOAD == 1
void gd_load(const uint8_t* pData, gd_axe_x_kind x, gd_axe_y_kind y, gd_axe_x_kind w, gd_axe_y_kind h, uint8_t px_mode);
#endif


#endif
