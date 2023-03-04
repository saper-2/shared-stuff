/*
 * st7565.c
 *
 * Created: 2016-10-29 23:14:06
 *  Author: saper
 */ 

#include <avr/io.h>
#include <inttypes.h>

#include "st7588.h"
#include "delay.h"

#if ST_USE_FRAMEBUFFER==1
	uint8_t st_fbuff[ST_FB_SIZE];
#endif

void st_send(uint8_t data) {
	// send byte, from MSB to LSB bit
	#if ST_INTERFACE == ST_IF_SPI4A
		for(uint8_t i=0;i<8;i++) {
			if (data & 0x80) st_sda_hi; else st_sda_lo;
			st_scl_lo;
			delay1us(ST_CLK_HDELAY);
			st_scl_hi; // data latched on rising edge
			delay1us(ST_CLK_HDELAY);
			data <<= 1;
		}
	#elif ST_INTERFACE == ST_IF_SPI4B
		for(uint8_t i=0;i<8;i++) {
			if (data & 0x01) st_sda_hi; else st_sda_lo;
			st_scl_lo;
			delay1us(ST_CLK_HDELAY);
			st_scl_hi; // data latched on rising edge
			delay1us(ST_CLK_HDELAY);
			data >>= 1;
		}
	#else
		#error "Interface mode not supported (yet)."
	#endif
	
	st_scl_hi; //make sure that scl is high
}

void st7588_data(uint8_t dta) {
	#if ST_INTERFACE == ST_IF_SPI4A || ST_INTERFACE == ST_IF_SPI4B
		st_a0_hi;
		st_cs_on;
		#if ST_CLK_HDELAY_CS > 0
			delay1us(ST_CLK_HDELAY_CS);
		#endif
		st_send(dta);
		#if ST_CLK_HDELAY_CS > 0
			delay1us(ST_CLK_HDELAY_CS);
		#endif
		st_cs_off;
	#else
		#error "Interface mode not supported (yet)"
	#endif
}

void st7588_cmd(uint8_t cmd) {
	#if ST_INTERFACE == ST_IF_SPI4A || ST_INTERFACE == ST_IF_SPI4B
		st_a0_lo;
		st_cs_on;
		#if ST_CLK_HDELAY_CS > 0
			delay1us(ST_CLK_HDELAY_CS);
		#endif
		st_send(cmd);
	
		#if ST_CLK_HDELAY_CS > 0
			delay1us(ST_CLK_HDELAY_CS);
		#endif
	#else
		#error "Interface mode not supported (yet)"
	#endif
	st_cs_off;
}

void st7588_cmd2(uint8_t cmd1, uint8_t cmd2) {
	#if ST_INTERFACE == ST_IF_SPI4A || ST_INTERFACE == ST_IF_SPI4B
		st_a0_lo;
		st_cs_on;
		#if ST_CLK_HDELAY_CS > 0
			delay1us(ST_CLK_HDELAY_CS);
		#endif
		st_send(cmd1);
		st_send(cmd2);
	
		#if ST_CLK_HDELAY_CS > 0
			delay1us(ST_CLK_HDELAY_CS);
		#endif
	
		st_cs_off;
	#else
		#error "interface mode not supported (yet)."
	#endif
}

void st7588_addr(uint8_t x, uint8_t y) {
	
	if (x>=ST_LCD_WIDTH) x=ST_LCD_WIDTH-1;
	if (y>=ST_LCD_HEIGHT) y=ST_LCD_HEIGHT-1;
	
	y /= 8; // get page
	y++; // WD0020 - display area starts from PAGE1 .
	if (y>9) y=9; // ST7588 have 10 pages (0..9)
	if (x>131) x=131; // ST7588 have 132 cols (0..131)
	
	st7588_cmd(0x40|(0x0f & y));
	st7588_cmd(0xE0|(0x0f & x));
	st7588_cmd(0xF0|(0x0f & (x>>4)));
}

void st7588_fill(uint8_t pattern) {
	for(uint8_t pg=0;pg<(ST_LCD_HEIGHT/8);pg++) {
		st7588_addr(0, pg*8);
		for(uint8_t x=0;x<ST_LCD_WIDTH;x++) {
			st7588_data(pattern);
		}
	}
}

void st7588_init(void) {
	st_cs_off;
	st_sda_lo;
	st_scl_hi;
	st_res_hi;
	st_a0_hi;
	ST_CSB_DDR |= 1<<ST_CSB_PN;
	ST_SDA_DDR |= 1<<ST_SDA_PN;
	ST_SCL_DDR |= 1<<ST_SCL_PN;
	ST_RES_DDR	|= 1<<ST_RES_PN;
	ST_A0_DDR |= 1<<ST_A0_PN;
	// hardware reset
	st_res_lo;
	delay1ms(50);
	st_res_hi;
	delay1ms(20);
	// setup
	// Function set: 
	//		MX-SEG dir. selection (0-normal[SEG0->131], 1-reverse[SEG131->0])
	//		MY-COM dir. selection (0-normal, 1-reverse)
	//		PD-Power down (0-chip active, 1-chip is in power down mode)
	//		H1:H0 - Extended command set selection
	st7588_cmd(0x20|0x00|0x00|0x00|0x00|0x01); // Function Set: MX=0,MY=0,PD=0,H1=0,H0=1
	// EXT. COMMAND SET H[1:0]=01 :
	st7588_cmd(0x10|0x02); // Bias system: BS[2:0]=010 (1/65 , 1/68)
	st7588_cmd(0x08|0x00|0x00); // Display configuration: DO=0 (MSB on top), V=0 (horizontal addressing)
	st7588_cmd(0x80|(0x7F & 8)); // Set VOP
	st7588_cmd(0x20|0x00|0x00|0x00|0x00|0x00); // Function Set: MX=0,MY=0,PD=0,H1=0,H0=0
	// EXT. COMMAND SET H[1:0]=00 :
	st7588_cmd(0x04|0x01); // Set V_LCD range: PRS[0]=1 (V_LCD range HIGH)
	
	//st7588_cmd(0x20|0x00|0x00|0x00|0x02|0x00); // Function Set: MX=0,MY=0,PD=0,H1=0,H0=0
	// EXT. COMMAND SET H[1:0]=10 :
	//st7588_cmd(0x80|8); // shift by 8 lines
	
	st7588_cmd(0x20|0x00|0x00|0x00|0x00|0x00); // Function Set: MX=0,MY=0,PD=0,H1=0,H0=0
	// EXT. COMMAND SET H[1:0]=00 :
	st7588_cmd(0x08|0x04); // Display control: D:E[2,0]= 0x00-Disp. off, 0x04-Normal, 0x01-All segm. ON, 0x05-Negative mode  
	st7588_cmd(0x40|0); // Set Y=0
	st7588_cmd(0xE0|0);// Set X[LSB_NIBBLE]=0
	st7588_cmd(0xF0|0);// Set X[MSB_NIBBLE]=0
	
	// reset ram
	st7588_fill(0x00);
}


void st_fb_push(void) {
	uint16_t pos=0;
	for(uint8_t pg=0;pg<(ST_LCD_HEIGHT/8);pg++) {
		st7588_addr(0, pg*8);
		for(uint8_t x=0;x<ST_LCD_WIDTH;x++) {
			st7588_data(st_fbuff[pos++]);
		}
	}
}

void st_fb_setPix(uint8_t x, uint8_t y, uint8_t pxmode) {
	uint16_t fbp = 0;
	uint8_t b, mask;
	
	fbp = ((y/8)*ST_LCD_WIDTH) + x;
	b = st_fbuff[fbp];
	
	mask = 0x01;
	mask <<= (y%8);
	
	if (pxmode == ST_PX_OFF) {
		b &= (~mask);
	} else if (pxmode == ST_PX_ON) {
		b |= mask;
	} else if (pxmode == ST_PX_XOR) {
		if ((b&mask) != 0x00) {
			b &= (~mask);	
		} else {
			b |= mask;
		}
	}
	
	st_fbuff[fbp] = b;
}

void st_fb_cls(uint8_t pattern) {
	for (uint16_t i=0;i<ST_FB_SIZE;i++) st_fbuff[i]=pattern;
}

