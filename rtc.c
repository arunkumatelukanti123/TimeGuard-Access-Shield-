#include "types.h"
#include <lpc21xx.h>
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm_defines.h"
#include "delay.h"
#include "kpm.h"
int year;
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define PREINT_VAL ((PCLK/32768)-1)
#define PREFRAC_VAL (PCLK-((PREINT_VAL+1)*32768))

s8 week[][4]= {"SUN","MON","TUE","WED","THU","FRI","SAT"};
char Month[][4]={"JAN","FEB","MAR","APL","MAY","JUN","JLY","AUG","SEP","OCT","NOV","DEC"};
void init_rtc(void);
void display_time_date(void)
{
    int h = HOUR;
    int m = MIN;
    int s = SEC;
    int d = DOM;

    cmd_lcd(goto_line1);
    str_lcd(week[DOW]);
    char_lcd(' ');
    str_lcd(Month[MONTH]);
    char_lcd(' ');
    int_lcd(year);

    cmd_lcd(goto_line2);
    char_lcd((h/10)+'0');
    char_lcd((h%10)+'0');
    char_lcd(':');

    char_lcd((m/10)+'0');
    char_lcd((m%10)+'0');
    char_lcd(':');

    char_lcd((s/10)+'0');
    char_lcd((s%10)+'0');
}


void init_rtc()
{
    Init_lcd();
    str_lcd("RTC CLOCK");
    delay_ms(1000);
    cmd_lcd(0x01);  

    CCR = 1<<1; //reset

    PREINT  = PREINT_VAL;
    PREFRAC = PREFRAC_VAL;
    CCR = (1<<0) | (1<<4);//rtc timer on
	YEAR=2025;
	year=YEAR; 
}

