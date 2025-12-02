#include <lpc21xx.h>
#include "delay.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "kpm_defines.h"
#include "kpm.h"
#include <string.h>

extern int year;           // RTC year variabes
#include "keypass_defines.h"

int k, n, i, j;             // Global temporary variables
char newpass[6];            // New password storage (5 digits + '\0')
char conformpass[6];        // Confirmation password storage
extern char str[];          // Stored password (original password)

// Default Login Time Values
int start_hour = 9;
int start_min  = 30;
int end_hour   = 17;
int end_min    = 30;



// FUNCTION: rtc_time()
// PURPOSE : Display RTC continuously until key is pressed

void rtc_time(void)
{
    while(colscan() == 0x0F)       // No key pressed
    {
        display_time_date();       // Keep showing time/date
    }
    while(colscan() != 0x0F); 		// Wait for key release
	}
// FUNCTION: re_password()
void re_password(char *newpass)
{
    int i = 0, key;

    cmd_lcd(0x01);
    cmd_lcd(0x80);
    str_lcd("CHANGE PSWD");

    cmd_lcd(0xC0);

    while(i < 5)              // Accept 5 characters
    {
        key = keyscan();
        while(colscan() != 0x0F); // Wait key release

        if(key == '#')        // BACKSPACE
        {
            if(i > 0)
            {
                i--;                      // Move back one position
                newpass[i] = '\0';        // Clear last character

                cmd_lcd(0xC0 + i);        // Move LCD cursor
                char_lcd(' ');            // Erase
                cmd_lcd(0xC0 + i);
            }
        }
        else
        {
            newpass[i] = key; // Store character
            char_lcd('*');    // Show "*" for security
            i++;
        }
    }

    newpass[5] = '\0';        // Null-terminate
}



// FUNCTION: confirmpw()
// PURPOSE : User re-enters password for confirmation

void confirmpw(char *conformpass)
{
    int i = 0, key;

    cmd_lcd(0x01);
    str_lcd("CONFIRM PW");
    cmd_lcd(0xC0);

    while(i < 5)
    {
        key = keyscan();
        while(colscan() != 0x0F);

        if(key == '#')
        {
            if(i > 0)
            {
                i--;
                conformpass[i] = '\0';

                cmd_lcd(0xC0 + i);
                char_lcd(' ');
                cmd_lcd(0xC0 + i);
            }
        }
        else
        {
            conformpass[i] = key;
            char_lcd('*');
            i++;
        }
    }

    conformpass[5] = '\0';
}



// FUNCTION: checkpw2()
// PURPOSE : Compare new password & confirm password

void checkpw2(char *newpass, char *conformpass)
{
    cmd_lcd(0x01);

    if(strcmp(newpass, conformpass) == 0)
    {
        strcpy(str, newpass);      // Update original password
        str_lcd("PASSWORD UPDATE");
        delay_ms(1000);
    }
    else
    {
        str_lcd("PW NOT MATCH");
        delay_ms(1000);
    }

    cmd_lcd(0x01);
}

void edit_login_time()
{
    int k, i;
    char hh[2];     // Hours input
    char mm[2];     // Minutes input

  
    // SET START TIME - HOURS
 
    cmd_lcd(0x01);  // Clear LCD
    str_lcd("HH:"); // Display HH: on first line
    cmd_lcd(0xC0);  // Move cursor to second line

    i = 0;
    while(i < 2)
    {
        k = keyscan();
        while(colscan() != 0x0F);

        if(k == '#')        // Backspace
        {
            if(i > 0)
            {
                i--;
                hh[i] = '\0';
                cmd_lcd(0xC0 + i);
                char_lcd(' ');
                cmd_lcd(0xC0 + i);
            }
        }
        else
        {
            hh[i] = k;
            char_lcd(k);
            i++;
        }
    }

    start_hour = (hh[0]-'0')*10 + (hh[1]-'0');

  
    // SET START TIME - MINUTES
  
    cmd_lcd(0x01);  // Clear LCD
    str_lcd("MM:"); // Display MM: on first line
    cmd_lcd(0xC0);  // Move cursor to second line

    i = 0;
    while(i < 2)
    {
        k = keyscan();
        while(colscan() != 0x0F);

        if(k == '#')
        {
            if(i > 0)
            {
                i--;
                mm[i] = '\0';
                cmd_lcd(0xC0 + i);
                char_lcd(' ');
                cmd_lcd(0xC0 + i);
            }
        }
        else
        {
            mm[i] = k;
            char_lcd(k);
            i++;
        }
    }

    start_min = (mm[0]-'0')*10 + (mm[1]-'0');

   
    // SET END TIME - HOURS
 
    delay_ms(500);
    cmd_lcd(0x01);  // Clear LCD
    str_lcd("HH:"); // Display HH: on first line
    cmd_lcd(0xC0);  // Move cursor to second line

    i = 0;
    while(i < 2)
    {
        k = keyscan();
        while(colscan() != 0x0F);

        if(k == '#')
        {
            if(i > 0)
            {
                i--;
                hh[i] = '\0';
                cmd_lcd(0xC0 + i);
                char_lcd(' ');
                cmd_lcd(0xC0 + i);
            }
        }
        else
        {
            hh[i] = k;
            char_lcd(k);
            i++;
        }
    }

    end_hour = (hh[0]-'0')*10 + (hh[1]-'0');

  
    // SET END TIME – MINUTES

    cmd_lcd(0x01);  // Clear LCD
    str_lcd("MM:"); // Display MM: on first line
    cmd_lcd(0xC0);  // Move cursor to second line

    i = 0;
    while(i < 2)
    {
        k = keyscan();
        while(colscan() != 0x0F);

        if(k == '#')
        {
            if(i > 0)
            {
                i--;
                mm[i] = '\0';
                cmd_lcd(0xC0 + i);
                char_lcd(' ');
                cmd_lcd(0xC0 + i);
            }
        }
        else
        {
            mm[i] = k;
            char_lcd(k);
            i++;
        }
    }

    end_min = (mm[0]-'0')*10 + (mm[1]-'0');

    // Final confirmation
    cmd_lcd(0x01);
    cmd_lcd(0x80);
    str_lcd("LOGIN TIME SET");
    delay_ms(500);
    cmd_lcd(0x01);
}




// MENU DISPLAY

void menu()
{
    cmd_lcd(0x01);
    cmd_lcd(0x80);
    str_lcd("1: TIME EDIT");

    cmd_lcd(0xC0);
    str_lcd("2: PA  3: LOG");
}



//-----------------------------------------------------
// USER EDIT MENU HANDLER
//-----------------------------------------------------
void user_edit()
{
    cmd_lcd(0x01);

    while(1)
    {
        menu();
        k = keyscan();
        while(colscan() != 0X0f);    // Wait for key release


       
        // OPTION 1 : RTC TIME EDIT

        if(k == '1')
        {
            int i;
            char temp[2];       // 2-digit storage for Min/Hr/... 
            char year_temp[4];  // 4-digit storage for year


            // MIN 
            cmd_lcd(0x01);
            cmd_lcd(0x80);
            str_lcd("MIN:");
            cmd_lcd(0xC0);

            i = 0;
            while(i < 2)
            {
                k = keyscan();
                while(colscan() != 0x0F);

                if(k == '#')
                {
                    if(i > 0)
                    {
                        i--;
                        temp[i] = '\0';
                        cmd_lcd(0xC0 + i);
                        char_lcd(' ');
                        cmd_lcd(0xC0 + i);
                    }
                }
                else
                {
                    temp[i] = k;
                    char_lcd(k);
                    i++;
                }
            }

            MIN = (temp[0]-'0')*10 + (temp[1]-'0');
            delay_ms(200);


            // HOUR
            cmd_lcd(0x01);
            cmd_lcd(0x80);
            str_lcd("HOUR:");
            cmd_lcd(0xC0);

            i = 0;
            while(i < 2)
            {
                k = keyscan();
                while(colscan() != 0x0F);

                if(k == '#')
                {
                    if(i > 0)
                    {
                        i--;
                        temp[i] = '\0';
                        cmd_lcd(0xC0 + i);
                        char_lcd(' ');
                        cmd_lcd(0xC0 + i);
                    }
                }
                else
                {
                    temp[i] = k;
                    char_lcd(k);
                    i++;
                }
            }

            HOUR = (temp[0]-'0')*10 + (temp[1]-'0');
            delay_ms(200);


            // DOW 
            cmd_lcd(0x01);
            cmd_lcd(0x80);
            str_lcd("DOW:");
            cmd_lcd(0xC0);

            i = 0;
            while(i < 2)
            {
                k = keyscan();
                while(colscan() != 0x0F);

                if(k == '#')
                {
                    if(i > 0)
                    {
                        i--;
                        temp[i] = '\0';
                        cmd_lcd(0xC0 + i);
                        char_lcd(' ');
                        cmd_lcd(0xC0 + i);
                    }
                }
                else
                {
                    temp[i] = k;
                    char_lcd(k);
                    i++;
                }
            }

            DOW = (temp[0]-'0')*10 + (temp[1]-'0');
            delay_ms(200);


            //MONTH
            cmd_lcd(0x01);
            cmd_lcd(0x80);
            str_lcd("MONTH:");
            cmd_lcd(0xC0);

            i = 0;
            while(i < 2)
            {
                k = keyscan();
                while(colscan() != 0x0F);

                if(k == '#')
                {
                    if(i > 0)
                    {
                        i--;
                        temp[i] = '\0';
                        cmd_lcd(0xC0 + i);
                        char_lcd(' ');
                        cmd_lcd(0xC0 + i);
                    }
                }
                else
                {
                    temp[i] = k;
                    char_lcd(k);
                    i++;
                }
            }

            MONTH = (temp[0]-'0')*10 + (temp[1]-'0');
            delay_ms(200);


            //YEAR
            cmd_lcd(0x01);
            cmd_lcd(0x80);
            str_lcd("YEAR:");
            cmd_lcd(0xC0);

            i = 0;
            while(i < 4)
            {
                k = keyscan();
                while(colscan() != 0x0F);

                if(k == '#')
                {
                    if(i > 0)
                    {
                        i--;
                        year_temp[i] = '\0';
                        cmd_lcd(0xC0 + i);
                        char_lcd(' ');
                        cmd_lcd(0xC0 + i);
                    }
                }
                else
                {
                    year_temp[i] = k;
                    char_lcd(k);
                    i++;
                }
            }

            year = (year_temp[0]-'0')*1000 +
                   (year_temp[1]-'0')*100 +
                   (year_temp[2]-'0')*10 +
                   (year_temp[3]-'0');

            delay_ms(300);
            cmd_lcd(0x01);
            break;
        }


       
        // OPTION 2 : PASSWORD CHANGE
        
        else if(k == '2')
        {
            re_password(newpass);
            confirmpw(conformpass);
            checkpw2(newpass, conformpass);
            break;
        }


        
        // OPTION 3 : LOGIN TIME SETTING
    
        else if(k == '3')
        {
            edit_login_time();
            break;
        }

        else
        {
            break;
				}
        break;
			}
		}


