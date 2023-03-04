/*
 * st7588.h
 *
 * Created: 2016-10-29 23:14:19
 *  Author: saper
 */ 


#ifndef ST7588_H_
#define ST7588_H_

// ---------- HARDWARE
#define ST_IF_SPI4A 0
#define ST_IF_SPI4B 1
#define ST_IF_SPI3A 2
#define ST_IF_SPI3B 3
#define ST_IF_SPI3_9b 4
#define ST_IF_I2C 5
#define ST_IF_6800 6
#define ST_IF_8080 7

#define ST_LCD_WIDTH 132
#define ST_LCD_HEIGHT 32

// set to 1 to enable RAM framebuffer (for displays "write-only")
#define ST_USE_FRAMEBUFFER 1
#define ST_FB_SIZE ((ST_LCD_WIDTH*ST_LCD_HEIGHT)/8)

#define ST_INTERFACE ST_IF_SPI4A

#if ST_INTERFACE == ST_IF_SPI4A || ST_INTERFACE == ST_IF_SPI4B
	// SI
	#define ST_SDA_PORT PORTC
	#define ST_SDA_PN 5
	#define ST_SDA_DDR DDRC
	// SCL
	#define ST_SCL_PORT PORTC
	#define ST_SCL_PN 3
	#define ST_SCL_DDR DDRC
	// A0
	#define ST_A0_PORT PORTC
	#define ST_A0_PN 4
	#define ST_A0_DDR DDRC
	// RES
	#define ST_RES_PORT PORTC
	#define ST_RES_PN 2
	#define ST_RES_DDR DDRC
	// CS
	#define ST_CSB_PORT PORTC
	#define ST_CSB_PN 1
	#define ST_CSB_DDR DDRC
	
	#define ST_CLK_HDELAY 2 // [us]
	#define ST_CLK_HDELAY_CS 0 // [us] - 0=off
	
	// macros
	// "/CSB"
	#define st_cs_on  ST_CSB_PORT &= ~(1<<ST_CSB_PN)
	#define st_cs_off ST_CSB_PORT |=  (1<<ST_CSB_PN)
	// A0
	#define st_a0_hi ST_A0_PORT |=  (1<<ST_A0_PN)
	#define st_a0_lo ST_A0_PORT &= ~(1<<ST_A0_PN)
	// SDA
	#define st_sda_hi ST_SDA_PORT |=  (1<<ST_SDA_PN)
	#define st_sda_lo ST_SDA_PORT &= ~(1<<ST_SDA_PN)
	// CLK
	#define st_scl_hi ST_SCL_PORT |=  (1<<ST_SCL_PN)
	#define st_scl_lo ST_SCL_PORT &= ~(1<<ST_SCL_PN)
	// RES
	#define st_res_hi ST_RES_PORT |=  (1<<ST_RES_PN)
	#define st_res_lo ST_RES_PORT &= ~(1<<ST_RES_PN)
	
#else
	#error "ST7565 Interface mode not supported by driver"
#endif


#if ST_USE_FRAMEBUFFER==1
	extern uint8_t st_fbuff[];
#endif

void st7588_data(uint8_t dta);
void st7588_init(void);
void st7588_fill(uint8_t pattern);
void st7588_addr(uint8_t x, uint8_t y);
//void st7588_ev_set(uint8_t vol);

#define ST_PX_OFF 0
#define ST_PX_ON 1
#define ST_PX_XOR 2

void st_fb_push(void); // push framebuffer from RAM to LCD
void st_fb_setPix(uint8_t x, uint8_t y, uint8_t pxmode); // set pixel in framebuffer
void st_fb_cls(uint8_t pattern); // fill framebuffer with pattern.

#endif /* ST7565_H_ */