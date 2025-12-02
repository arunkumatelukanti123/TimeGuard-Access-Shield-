#include <lpc21xx.h>
#include "lcd_defines.h"
#include "lcd.h"
#include <string.h>
#include <stdlib.h>
#include "delay.h"
#include "kpm_defines.h"
#include "kpm.h"
extern int ent1_flag;
void display_time_date(void);
void pass(void);
void user_edit(void);
void init_rtc(void);
void Init_Key(void);
void rtc_time(void);

char key;

int main()
{ 
    Init_KPM();
	  Init_Key();
    init_rtc();
	  

    while(1)
    {
			rtc_time();
		pass();

  	//}
	}
}

		
