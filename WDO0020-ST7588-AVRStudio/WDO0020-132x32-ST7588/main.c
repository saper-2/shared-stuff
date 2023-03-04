/*
 * ST7588.c
 *
 * Created: 2016-10-30 21:18:50
 * Author : saper
 */ 

#include <avr/io.h>
#include <inttypes.h>
#include <avr/pgmspace.h>

#include "delay.h"
#include "st7588.h"
#include "lcd-graphic.h"
#include "KeyThrow40x32.h"
#include "wd0020.h"

#define led_on PORTB |= 1<<0
#define led_off PORTB &= ~(1<<0)

int main(void)
{
	led_off;
	DDRB |= 1<<0;
	
	st7588_init();
	led_on;
	delay1ms(500);
	st7588_fill(0xFF);
	delay1ms(500);
	
	st_fb_cls(0x00);
	st_fb_push();
	delay1ms(500);
	for(int i=0;i<32;i++) {
		st_fb_setPix(i,i,ST_PX_ON);
		st_fb_setPix(32-i,i,ST_PX_ON);
		st_fb_setPix(i+32,i,ST_PX_ON);
		st_fb_setPix(64-i,i,ST_PX_ON);
		st_fb_setPix(i+64,i,ST_PX_ON);
		st_fb_setPix(96-i,i,ST_PX_ON);
		st_fb_setPix(i+96,i,ST_PX_ON);
		st_fb_setPix(128-i,i,ST_PX_ON);
		st_fb_setPix(129,31-i,ST_PX_ON);
		st_fb_setPix((i%2?131:130),i,ST_PX_ON);
		st_fb_push();
		delay1ms(5);
	}
	delay1ms(2000);
	st_fb_cls(0x00);
	st_fb_push();
	
	gd_load(&key_throw[0], 0, 0, 40, 32, GD_PX_ON);
	gd_strP(48,2,PSTR("WDO0020-TML"), GD_PX_ON);
	gd_lineH(42, 12, (130-42), GD_PX_ON);// gd_line(41, 15, 129, 15, GD_PX_ON);
	gd_strP(54,15,PSTR("by Winstar"), GD_PX_ON);
	st_fb_push();
	
	delay1ms(4000);
	st_fb_cls(0x00);
	
	gd_strP(0, 0, PSTR("WDO0020:"), GD_PX_ON);
	gd_strP(0, 8, PSTR("132x64px, blue BL"), GD_PX_ON);
	gd_strP(0,16, PSTR("IC: ST7588, IF: SPI4A"), GD_PX_ON);
	gd_strP(0,24, PSTR("...>"), GD_PX_ON);
	st_fb_push();
	
	delay1ms(4000);
	st_fb_cls(0x00);
	gd_strP(0, 0, PSTR("WDO0020:"), GD_PX_ON);
	gd_strP(0, 8, PSTR(">..."), GD_PX_ON);
	gd_strP(0,16, PSTR("Page-start: 0x01"), GD_PX_ON);
	gd_strP(0,24, PSTR("PRS=1, BSx=0x02, VOP=8"), GD_PX_ON);
	st_fb_push();
	delay1ms(4000);
	
	for(uint8_t i=0;i<ST_LCD_HEIGHT;i++) {
		gd_lineH(0, i, ST_LCD_WIDTH, GD_PX_ON);
		st_fb_push();
		delay1ms(25);
	}
	for(uint8_t i=0;i<ST_LCD_HEIGHT;i++) {
		gd_lineH(0, i, ST_LCD_WIDTH, GD_PX_OFF);
		st_fb_push();
		delay1ms(25);
	}
	
	gd_strP(28,  0, PSTR("Driver ST7588"), GD_PX_ON);
	gd_strP(36,  8, PSTR("with UGLib"), GD_PX_ON);
	gd_strP( 9, 16, PSTR("and RAM framebuffer"), GD_PX_ON);
	gd_strP(36, 24, PSTR("by saper_2"), GD_PX_ON);
	st_fb_push();
	delay1ms(4000);
	st_fb_cls(0x00);
	gd_strP(0,  4, PSTR("MCU: ATMega32 16MHz"), GD_PX_ON);
	gd_strP(0, 12, PSTR("AVR-GCC: 4.9.2"), GD_PX_ON);
	gd_strP(0, 20, PSTR("IDE: Atmel Studio 7"), GD_PX_ON);
	st_fb_push();
	
	delay1ms(4000);
	
	gd_cls();
	gd_rect(10,10, 40, 22, GD_PX_ON);
	gd_rect_fill(45,5, 62, 30, GD_PX_ON);
	gd_circle(92, 16, 8, GD_PX_ON);
	//gd_line(42, 6, 120, 29, GD_PX_XOR);
	//gd_line(45, 30, 125, 2, GD_PX_XOR);
	
	st_fb_push();
	delay1ms(4000);
	
	gd_cls();
	
	gd_strP(0, 0, PSTR("Flash: 3958 bytes"), GD_PX_ON);
	gd_strP(0, 8, PSTR("FB RAM: 528 bytes"), GD_PX_ON);
	gd_strP(0, 16, PSTR("Total RAM: ~600 bytes"), GD_PX_ON);
	gd_strP(0, 24, PSTR("--- DEMO END :) ---"), GD_PX_ON);
	st_fb_push();
	
	
	while (1)
	{
		
		led_on;
		delay1ms(150);
		led_off;
		delay1ms(150);
		
	}
}

