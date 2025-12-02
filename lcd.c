#include "types.h"
#include<lpc21xx.h>
#include "delay.h"
#include "lcd_defines.h"
void write_lcd(char byte)
{
	IOCLR0=1<<lcd_rw;
	IOPIN0=((IOPIN0&~(255<<lcd_data))|(byte<<lcd_data));
	IOSET0=1<<lcd_en;
	delay_us(1);
	IOCLR0=1<<lcd_en;
	delay_ms(2);
}
void cmd_lcd(char cmdbyte)
{
	IOCLR0=1<<lcd_rs;
	write_lcd(cmdbyte);
}
void char_lcd(char asciival)
{
   IOSET0=1<<lcd_rs;
	 write_lcd(asciival);
}
void str_lcd(char* s)
{
	while(*s)
		char_lcd(*s++);
}
void int_lcd(int num)
{
	char arr[20];
	int i=0,j;
	while(num)
	{
		arr[i++]=num%10+48;
		num=num/10;
	}
	for(j=i-1;j>=0;j--)
	{
		char_lcd(arr[j]);
	}
}
void Init_lcd()
{
	IODIR0|=2047<<lcd_data;
	delay_ms(15);
	cmd_lcd(mode_8bit_line1);
	delay_ms(4100);
	cmd_lcd(mode_8bit_line1);
	delay_us(100);
	cmd_lcd(mode_8bit_line1);
	cmd_lcd(mode_8bit_line2);
	cmd_lcd(lcd_on_cur_off);
	cmd_lcd(clear_lcd);
	cmd_lcd(shift_cur_right);
}
