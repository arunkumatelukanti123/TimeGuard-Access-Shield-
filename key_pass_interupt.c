#include <lpc21xx.h>
#include "lcd_defines.h"
#include "lcd.h"
#include <string.h>
#include <stdlib.h>
#include "delay.h"
#include "kpm_defines.h"
#include "kpm.h"
#include "keypass_defines.h"
void init_rtc(void);
int flag = 0;

char str[] = "12345";   // Stored password
char str1[6];           // Entered password buffer

// Login time variables
extern int start_hour;
extern int start_min;
extern int end_hour;
extern int end_min;





// PASSWORD CHECK FUNCTION
int checkpw(char *str, char *str1)
{
    if(strcmp(str, str1) == 0)
    {
			  
        str_lcd("correct");
        delay_ms(1000);
        flag = 1;
        cmd_lcd(0x01);
    }
    else
    {
        cmd_lcd(0x01);
        str_lcd("wrong");
        delay_ms(1000);
        flag = 0;
        cmd_lcd(0x01);
    }
    return flag;
}
	
	
//enter password function
void enterpw(char *str1)
{
    int i = 0;
    char key;

    cmd_lcd(0xC0);   // second line

    while(i < 5)
    {
        key = keyscan();
        while(colscan() != 0x0f); // wait release

        if(key == '+')   // BACKSPACE
        {
            if(i > 0)
            {
                i--;             // move back one position
                str1[i] = '\0';  // remove last character

                // Move LCD cursor back and erase
                cmd_lcd(0xC0 + i);  
                char_lcd(' ');     // erase the character
                cmd_lcd(0xC0 + i); // move cursor back again
            }
            
        }
        else
        {
            str1[i] = key;
            char_lcd('*');   // or charLCD(key) if you show actual character
            i++;
        }
    }

    str1[5] = '\0';
}



//interupt for useredit options
void EINT0_ISR() __irq
{
    
    cmd_lcd(0x01); 
    user_edit();	// Clear LCD
    EXTINT = 1 << 0;          // Clear interrupt flag
    VICVectAddr = 0;          // End ISR
}


void Init_Key(void)
{
    cmd_lcd(0x01);            // Clear LCD

    PINSEL0 |= 3 << 2;        // Configure P0.1 as EINT0

    VICIntEnable = 1 << 14;   // Enable EINT0 in VIC
    VICVectCntl0 = (1 << 5) | 14;
    VICVectAddr0 = (unsigned)EINT0_ISR;

    EXTMODE = 1 << 0;         // Edge triggered
    EXTPOLAR = 0 << 0;        // Falling edge

}


//password entry function
void pass()
{
    flag = 0;
    cmd_lcd(0x01);
    str_lcd("ENTER PW");

    while(flag == 0)
    {
        enterpw(str1);        // Get password input
        checkpw(str, str1);   // Validate password

        if(flag == 1)
        {
            cmd_lcd(0x01);

            if( (HOUR > start_hour || (HOUR == start_hour && MIN >= start_min)) &&
                (HOUR < end_hour   || (HOUR == end_hour   && MIN <= end_min)) )
            {
                str_lcd("DEVICE ON");
                delay_s(1);
            }
            else
            {
                str_lcd("OUT OF TIME");
                delay_s(1);
            }
            break;  // exit password loop
        }
        str1[0] = '\0';         
        cmd_lcd(0x01);
        str_lcd("RE-ENTER PW"); 
    }
}



