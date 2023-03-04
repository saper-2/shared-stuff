/* ****************************************************************************
   * Name: Unified graphic library for monochromatic LCD displays - header    *
   * Author: saper_2 / nolin11                                                *
   * Contact: nolinno11@gmail.com                                             *
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
   * - v0.2  - Fixed some declarations so this lib can work with Atmel        *
   *           AVR Toolchain (tested on version 3.4.2)                        *
   * - v0.1  - Filling circle is "unfinished" (there are left "unfilled"      *
   *           pixels inside circle)                                          *
   *                                                                          *
   **************************************************************************** */
#include <avr/io.h>
#include <inttypes.h>
#include <avr/pgmspace.h>

#include "lcd-graphic.h"
// iclude lcd driver header
#include gd_lcd_driver_header_file

#if ( (GD_FUNC_CHAR == 1) || (GD_FUNC_STR==1) || (GD_FUNC_STR_P==1) || (GD_FUNC_HEX_BYTE==1) )
	// include font
	#include gd_lcd_single_font_file_name
#endif

void gd_init(void) {
	gd_init_lcd_routine;
}

void gd_fill(uint8_t pattern) {
	gd_fill_lcd_routine(pattern);
}



#if ( (GD_FUNC_LINE_H==1) || (GD_FUNC_RECT==1) || (GD_FUNC_LINE==1) )
void gd_lineH(gd_axe_x_kind x, gd_axe_y_kind y, gd_axe_x_kind w, uint8_t px_mode) {
	if (x >= GD_WIDTH) x = GD_WIDTH-1;
	if (y >= GD_HEIGHT) y = GD_HEIGHT-1;
	w = w+x;
	if (w>= GD_WIDTH) w = GD_WIDTH-1;
	
	for (;x<=w;x++) gd_set_pixel_lcd_routine(x,y,px_mode);
}
#endif

#if ( (GD_FUNC_LINE_V==1) || (GD_FUNC_RECT==1) || (GD_FUNC_LINE==1))
void gd_lineV(gd_axe_x_kind x, gd_axe_y_kind y, gd_axe_y_kind h, uint8_t px_mode) {
	if (x >= GD_WIDTH) x = GD_WIDTH-1;
	if (y >= GD_HEIGHT) y = GD_HEIGHT-1;
	h = h+y;
	if (h>= GD_HEIGHT) h = GD_HEIGHT-1;
	
	for (;y<=h;y++) gd_set_pixel_lcd_routine(x,y,px_mode);
}
#endif

#if GD_FUNC_LINE == 1

#define XCHG(a, b, var_type) \
{\
	var_type temp##a##b; \
	temp##a##b = b; \
	b = a; \
	a = temp##a##b;	\
}

void gd_line(gd_axe_x_kind x1, gd_axe_y_kind y1, gd_axe_x_kind x2, gd_axe_y_kind y2, uint8_t px_mode) {
	volatile gd_axe_x_kinds dx,sx,f;
	volatile gd_axe_y_kinds dy,sy;
	uint8_t i;
	
	if (x1 > x2) {
		XCHG(x1,x2,gd_axe_x_kind);
		XCHG(y1,y2,gd_axe_y_kind);
	}
	
	if (y1 > y2) {
		XCHG(x1,x2,gd_axe_x_kind);
		XCHG(y1,y2,gd_axe_y_kind);
	}
	
	if (x1 == x2) {
		gd_lineV(x1,y1,(y2-y1),px_mode);
		return;
	}
	
	if (y1 == y2) {
		gd_lineH(x1,x1,(x2-x1),px_mode);
		return;
	}
	
	dx = x2 - x1;
	dy = y2 - y1;
	
	if (dx < 0) {
		dx = -dx;
		sx = -1;
	} else {
		sx = 1;
	}
	
	if (dy < 0) {
		dy = -dy;
		sy = -1;
	} else {
		sy = 1;
	}

	dx <<= 1; // Shift Dx , Left , 1  '-2
	dy <<= 1; // Shift Dy , Left , 1  '-2
	
	gd_set_pixel_lcd_routine(x1,y1,px_mode); // Call Lcdpixel(x1 , Y1 , Pixelmode)

	if (dx > dy) {
		i = dx;
		i >>= 1;
		f = dy-i;
		while (x1!=x2) {
			if (f >= 0) {
				y1 += sy; //Y1 = Y1 + Stepy
				f -= dx; //Fraction = Fraction - Dx
			}
         x1 += sx;
			f += dy;
			gd_set_pixel_lcd_routine(x1,y1,px_mode);
		}
	} else {
      i = dy;
		i >>= 1;
		f = dx-i;
		while (y1!=y2) {
			if (f >= 0) {
				x1 += sx;
				f -= dy; //Fraction = Fraction - Dy
			}
			y1 += sy;
			f += dx;
			gd_set_pixel_lcd_routine(x1,y1,px_mode);
		}
	}
}
#endif

#if GD_FUNC_RECT == 1
void gd_rect(gd_axe_x_kind x1, gd_axe_y_kind y1, gd_axe_x_kind x2, gd_axe_y_kind y2, uint8_t px_mode) {
	gd_axe_x_kind w;
	gd_axe_y_kind h;
	if (x1 >= GD_WIDTH) x1 = GD_WIDTH-1;
	if (y1 >= GD_HEIGHT) y1 = GD_HEIGHT-1;
	if (x2 >= GD_WIDTH) x2 = GD_WIDTH-1;
	if (y2 >= GD_HEIGHT) y2 = GD_HEIGHT-1;
	if (x1 > x2) { w = x1; x1 = x2; x2 = w; }
	if (y1 > y2) { h = y1; y1 = y2; y2 = h; }
	w = x2-x1;
	h = y2-y1;
	if (w>= GD_WIDTH) w = GD_WIDTH-1;
	if (h>= GD_HEIGHT) h = GD_HEIGHT-1;
	
	gd_lineH(x1,y1,w,px_mode);
	gd_lineH(x1,y2,w,px_mode);
	gd_lineV(x1,y1+1,h-2,px_mode);
	gd_lineV(x2,y1+1,h-2,px_mode);

}
#endif

#if GD_FUNC_RECT_FILL == 1
void gd_rect_fill(gd_axe_x_kind x1, gd_axe_y_kind y1, gd_axe_x_kind x2, gd_axe_y_kind y2, uint8_t px_mode) {
	gd_axe_y_kind y;
	if (x1 >= GD_WIDTH) x1 = GD_WIDTH-1;
	if (y1 >= GD_HEIGHT) y1 = GD_HEIGHT-1;
	if (x2 >= GD_WIDTH) x2 = GD_WIDTH-1;
	if (y2 >= GD_HEIGHT) y2 = GD_HEIGHT-1;
	if (x1 > x2) { y = x1; x1 = x2; x2 = y; }
	if (y1 > y2) { y = y1; y1 = y2; y2 = y; }
	for (;x1<=x2;x1++) {
		for (y=y1;y<=y2;y++) {
			gd_set_pixel_lcd_routine(x1,y,px_mode);
		}
	}
}
#endif

#if ( (GD_FUNC_CIRCLE == 1 ) || (GD_FUNC_CIRCLE_FILL == 1) )
void gd_circle(gd_axe_x_kind xc, gd_axe_x_kind yc, gd_axe_x_kind radius, uint8_t px_mode) {
	// Bresenham Algorithm - from wiki
	int16_t f = 1 - radius, ddfx = 1, ddfy = -2 * radius;
	gd_axe_x_kind x=0;
	gd_axe_y_kind y=radius;
	
	gd_setPix(xc, yc+radius, px_mode);
	gd_setPix(xc, yc-radius, px_mode);
	gd_setPix(xc+radius, yc, px_mode);
	gd_setPix(xc-radius, yc, px_mode);
	
	while (x<y) {
		// ddF_x == 2 * x + 1;
		// ddF_y == -2 * y;
		// f == x*x + y*y - radius*radius + 2*x - y + 1;
		if(f >= 0) 
		{
		  y--;
		  ddfy += 2;
		  f += ddfy;
		}
		x++;
		ddfx += 2;
		f += ddfx;
		gd_setPix(xc + x, yc + y, px_mode);
		gd_setPix(xc - x, yc + y, px_mode);
		gd_setPix(xc + x, yc - y, px_mode);
		gd_setPix(xc - x, yc - y, px_mode);
		gd_setPix(xc + y, yc + x, px_mode);
		gd_setPix(xc - y, yc + x, px_mode);
		gd_setPix(xc + y, yc - x, px_mode);
		gd_setPix(xc - y, yc - x, px_mode);
	}
}
#endif

#if ( (GD_FUNC_CIRCLE_FILL == 1 ) )
void gd_circle_fill(gd_axe_x_kind xc, gd_axe_x_kind yc, gd_axe_x_kind radius, uint8_t px_mode) {
	// draw circles decreasing radius with each draw :) - savage and not working well :/ 
	// There is idea :) , but it requre reading pixel state... :
	/*
		// first draw circle
		uint8_t setpx=0;
		gd_circle(xc,yc,radius,px_mode);
		for (y=yc-radius;y<(y+radius);y++) {
			setpx=0; // reset
			for (x=(xc-radius);x<(xc+radius);x++) {
				// search for first pixel on/off
				if (gd_getPix(x,y) == px_mode) { // first/last pixel found
					if (setpx==1) break; // leave loop "x"
					setpx=1; // enable drawing mode
				} else { // if pixel is different from px_mode,
					// and allow for filling is enabled: setpx == 1,then start coloring pixels with px_mode
					if (setpx==1) gd_setPix(x,y,px_mode);
				}
			}
		}
	*/
	while (radius > 0) {
		gd_circle(xc, yc, radius, px_mode);
		radius--;
	}
}
#endif

#if ( GD_FUNC_ELIPSE == 1)
void gd_elipse_4point(gd_axe_x_kind x, gd_axe_y_kind y, gd_axe_x_kind cx, gd_axe_y_kind cy, uint8_t px_mode) {
	gd_setPix(cx+x, cy+y, px_mode);
	gd_setPix(cx-x, cy+y, px_mode);
	gd_setPix(cx-x, cy-y, px_mode);
	gd_setPix(cx+x, cy-y, px_mode);
}
// A Fast Bresenham Type Algorithm For Drawing Ellipses by John Kennedy
// well fast on int32 signed numbers on avr... anyway it can take radius(es) up to 50px (or 45px) in sum 
void gd_elipse(gd_axe_x_kind cx, gd_axe_y_kind cy, gd_axe_x_kind rx, gd_axe_y_kind ry, uint8_t px_mode) {
	gd_axe_x_kind x; 
	gd_axe_y_kind y;
	int32_t xch, ych, elerr, twoas, twobs, stpx, stpy; // this is no joke \->
	//	if you want draw elipse with radius 256px then you'll get in twoas/twobs number over 100'000 !!
	twoas = 2*rx*rx;
	twobs = 2*ry*ry;
	x = rx;
	y = 0;
	xch = ry*ry * (1 - 2*rx);
	ych = rx*rx;
	elerr = 0;
	stpx = twobs*rx;
	stpy = 0;
	// 1st set of points
	while ( stpx >= stpy ) {
		gd_elipse_4point(x,y, cx, cy, px_mode);
		y++;
		stpy += twoas;
		elerr += ych;
		ych += twoas;
		if ((2*elerr+xch) > 0) {
			x--;
			stpx -= twobs;
			elerr += xch;
			xch += twobs;
		}
	}
	// 2nd set of points
	x=0;
	y=ry;
	xch=ry*ry;
	ych=rx*rx * (1 - 2*ry);
	elerr=0;
	stpx=0;
	stpy=twoas*ry;
	while (stpx <= stpy) {
		gd_elipse_4point(x,y, cx, cy, px_mode);
		x++;
		stpx += twobs;
		elerr += xch;
		xch += twobs;
		if ((2*elerr+ych) > 0) {
			y--;
			stpy -= twoas;
			elerr += ych;
			ych += twoas;
		}
	}
}
#endif

#if ( (GD_FUNC_CHAR == 1) || (GD_FUNC_STR==1) || (GD_FUNC_STR_P==1) || (GD_FUNC_HEX_BYTE==1) )
uint8_t gd_char(gd_axe_x_kind x, gd_axe_x_kind y, char znak, uint8_t chr_mode) {
	// check...
	if ((znak > (GPH_CHAR_COUNT+GPH_CHAR_START)) || (znak < GPH_CHAR_START)) znak = GPH_CHAR_START;
	// calculate char location in array
	uint16_t t=(znak-GPH_CHAR_START)*GPH_CHAR_WIDTH;
	// depending on character height, choose var type
	#if GPH_CHAR_HEIGHT <= 8
		uint8_t b; // 8bit chars
	#elif ((GPH_CHAR_HEIGHT <= 16) && (GPH_CHAR_HEIGHT > 8))
		uint16_t b; // 16bit chars
	#elif GPH_CHAR_HEIGHT > 16
		uint32_t b; // 32bit chars
	#endif
	// draw columns of character
	for (gd_axe_x_kind i=x;i<(GPH_CHAR_WIDTH+x);i++) {
		// draw x bytes of char - char byte data orientation vertically
		// get column byte of char
		
		#if GPH_CHAR_HEIGHT <= 8
			b = pgm_read_byte(&GPH_FONT_NAME[t++]);
		#elif ((GPH_CHAR_HEIGHT <= 16) && (GPH_CHAR_HEIGHT > 8))
			b = pgm_read_word(&GPH_FONT_NAME[t++]);
		#elif GPH_CHAR_HEIGHT > 16
			b = pgm_read_dword(&GPH_FONT_NAME[t++]);
		#endif
		
		// vertical draw byte... (draw rows of column)
		for (gd_axe_y_kind j=y;j<(y+GPH_CHAR_HEIGHT);j++) {
			// flipped ?
			#if (GPH_FONT_COLUMN_UP_DOWN == 1)
				#if GPH_CHAR_HEIGHT <= 8
					if (b & 0x80) { // up to 8bit font height
				#elif ((GPH_CHAR_HEIGHT <= 16) && (GPH_CHAR_HEIGHT > 8))
					if (b & 0x8000) { // up to 16bit font height
				#elif GPH_CHAR_HEIGHT > 16
					if (b & 0x80000000) { // up to 32bit font height
				#endif
			#else // no flip...
				#if GPH_CHAR_HEIGHT <= 8
					if (b & 0x01) { // up to 8bit font height
				#elif ((GPH_CHAR_HEIGHT <= 16) && (GPH_CHAR_HEIGHT > 8))
					if (b & 0x0001) { // up to 16bit font height
				#elif GPH_CHAR_HEIGHT > 16
					if (b & 0x00000001) { // up to 32bit font height
				#endif
			#endif
				if ((chr_mode == GD_PX_ON) || (chr_mode == GD_TXT_ON_BG_OFF)) {
					gd_set_pixel_lcd_routine(i,j,GD_PX_ON);
				} else if ((chr_mode == GD_PX_OFF) || (chr_mode == GD_TXT_OFF_BG_ON)) {
					gd_set_pixel_lcd_routine(i,j,GD_PX_OFF);
				} else if (chr_mode == GD_PX_XOR) {
					gd_set_pixel_lcd_routine(i,j,GD_PX_XOR);
				}
			} else { // draw background (if needed...)??
				if (chr_mode == GD_TXT_ON_BG_OFF) { // black char on white bg
					gd_set_pixel_lcd_routine(i,j,GD_PX_OFF);
				} else if (chr_mode == GD_TXT_OFF_BG_ON) { // white char on black bg
					gd_set_pixel_lcd_routine(i,j,GD_PX_ON);
				}
			}
			// flipped ?
			#if (GPH_FONT_COLUMN_UP_DOWN == 1)
				b <<= 1;
			#else 
				// no...
				b >>= 1;
			#endif
		}
	}
	return GPH_CHAR_WIDTH;
}
#endif

#if ( (GD_FUNC_STR == 1) || (GD_FUNC_DEC==1) )
gd_axe_x_kind gd_str(gd_axe_x_kind x, gd_axe_y_kind y, char* str, uint8_t txt_mode) {
	while(*str != 0) {
		gd_char(x, y, *str++, txt_mode);
		x += GPH_CHAR_WIDTH;
	}
	return x;
}	
#endif

#if GD_FUNC_STR_P == 1
gd_axe_x_kind gd_strP(gd_axe_x_kind x, gd_axe_y_kind y,const char* str, uint8_t txt_mode) {
	char znak;
	while (0 != (znak = pgm_read_byte(str++))) {
		gd_char(x, y, znak, txt_mode);
		x += GPH_CHAR_WIDTH;
	}
	return x;
}		
#endif

#if GD_FUNC_DEC == 1
	#include <stdlib.h>
gd_axe_x_kind gd_dec(gd_axe_x_kind x, gd_axe_y_kind y, int val, uint8_t txt_mode) {
	char bufor[5];
	return gd_str(x,y,itoa(val, bufor, 10),txt_mode);
}	
#endif

#if GD_FUNC_HEX_BYTE == 1
gd_axe_x_kind gd_hexByte(gd_axe_x_kind x, gd_axe_y_kind y, uint8_t val, uint8_t txt_mode) {
	if (((val >> 4) & 0x0f) > 0x09) {
		gd_char(x,y,'7'+((val >> 4) & 0x0f), txt_mode);
	} else {
		gd_char(x,y,'0'+((val >> 4) & 0x0f), txt_mode);
	}
	x += GPH_CHAR_WIDTH;
	if ((val & 0x0f) > 0x09) {
		gd_char(x,y,'7'+(val & 0x0f), txt_mode);
	} else {
		gd_char(x,y,'0'+(val & 0x0f), txt_mode);
	}
	return x+=GPH_CHAR_WIDTH;
}	
#endif

#if GD_FUNC_LOAD == 1
void gd_load(const uint8_t* pData, gd_axe_x_kind x, gd_axe_y_kind y, gd_axe_x_kind w, gd_axe_y_kind h, uint8_t px_mode) {
	uint8_t b;
	gd_axe_x_kind x2;
	gd_axe_y_kind y2;
	uint8_t t=0;
	//h--;
	w+= x;// = (w-1) + x;
	h+= y;// = (h-1) + y;
	
	if ((w > GD_WIDTH) || (h > GD_HEIGHT)) {
		#if GD_FUNC_STR_P == 1
			gd_strP(x,y,                   PSTR("|Image goes out|"),GD_TXT_ON_BG_OFF);
			gd_strP(x,y+GPH_CHAR_HEIGHT+1, PSTR("|of screen.|"),GD_TXT_ON_BG_OFF);
		#endif
		return;
	}
	
	for (y2=y;y2<h;y2++) {
		x2=x;
		while (x2<w) {
			b = pgm_read_byte(pData++);
			for (t=0;t<8;t++) {
				if (b & 0x80) {
					gd_set_pixel_lcd_routine((x2+t),y2,px_mode);
				} else {
					gd_set_pixel_lcd_routine((x2+t),y2,(px_mode == GD_PX_ON ? GD_PX_OFF : GD_PX_ON));
				}
				b <<= 1;
			}
			x2+=8;
		}
	}
}
#endif
