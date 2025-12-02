#include <lpc21xx.h>
#include "delay.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "kpm_defines.h"
#include "kpm.h"
#include <string.h>
int extern year;
#include "keypass_defines.h"
int k, n,i,j;
char newpass[6];
char conformpass[6];
extern char str[];   // Stored password

int start_hour = 9;
int start_min  = 30;
int end_hour   = 17;
int end_min    = 30;

void rtc_time(void)
{
while(colscan()==0x0f)
{
	display_time_date();
	

}
	while(colscan()!=0x0f);
}

//PASSWORD CHANGE PART

void re_password(char *newpass)
{
    int i, key;

    cmd_lcd(0x01);
    cmd_lcd(0x80);
    str_lcd("CHANGE PSWD");

    cmd_lcd(0xC0);
    for(i = 0; i < 5; i++)
    {
        key = keyscan();
        char_lcd('*');
        newpass[i] = key;

        while(colscan() == 0);
    }
    newpass[5] = '\0';
}


void confirmpw(char *conformpass)
{
    int i, key;

    cmd_lcd(0x01);
    str_lcd("CONFIRM PW");

    cmd_lcd(0xC0);
    for(i = 0; i < 5; i++)
    {
        key = keyscan();
        conformpass[i] = key;
        char_lcd('*');

        while(colscan() == 0);
    }
    conformpass[5] = '\0';
}


void checkpw2(char *newpass, char *conformpass)
{
    cmd_lcd(0x01);

    if(strcmp(newpass, conformpass) == 0)
    {
        strcpy(str, newpass);
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



//LOGIN TIME EDIT PART

void edit_login_time()
{
    int k, n;

 //  START TIME 
    cmd_lcd(0x01);
    str_lcd("SET LOGIN START");

    cmd_lcd(0xC0);
    str_lcd("HH:");
    k = keyscan();
	  char_lcd('*');
	   while(colscan() == 0);
    n = keyscan();
    char_lcd('*');	
	     while(colscan() == 0);
    start_hour = (k - '0') * 10 + (n - '0');
	  cmd_lcd(0x01);

    cmd_lcd(0xC0);
    str_lcd("MM:");
    k = keyscan();
    char_lcd('*');	
	     while(colscan() == 0);
    n = keyscan();
		char_lcd('*');
		  while(colscan() == 0);
    start_min = (k - '0') * 10 + (n - '0');

    cmd_lcd(0x01);
		delay_ms(500);

    // END TIME 
    cmd_lcd(0x01);
    str_lcd("SET LOGIN END");

    cmd_lcd(0xC0);
    str_lcd("HH:");
    k = keyscan();
		char_lcd('*');
  		while(colscan() == 0);
    n = keyscan();
		char_lcd('*');
		   while(colscan() == 0);
    end_hour = (k - '0') * 10 + (n - '0');
		cmd_lcd(0x01);

    cmd_lcd(0xC0);
    str_lcd("MM:");
    k = keyscan();
		char_lcd('*');
		  while(colscan() == 0);
    n = keyscan();
		char_lcd('*');
		   while(colscan() == 0);
    end_min = (k - '0') * 10 + (n - '0');
		cmd_lcd(0x01);

    cmd_lcd(0x80);
    str_lcd("LOGIN TIME SET");
    delay_ms(500);
   cmd_lcd(0x01);
}



// MENU AND EDIT PART 

void menu()
{
    cmd_lcd(0x01);
    cmd_lcd(0x80);
    str_lcd("1: TIME EDIT");

    cmd_lcd(0xC0);
    str_lcd("2: PA  3: LOG");
}


void user_edit()
{
    cmd_lcd(0x01);

    while(1)
    {
        menu();
        k = keyscan();
        while(colscan() == 0);

        // TIME EDIT 
        if(k == '1')
        {
            cmd_lcd(0x01);

            str_lcd("MIN:");
            k = keyscan();
					  char_lcd('*');
					          while(colscan() != 0x0f);
            n = keyscan();
					  char_lcd('*');
					       while(colscan() != 0x0f);
            MIN = ((k - '0') * 10) + (n - '0');
					delay_ms(100);

            cmd_lcd(0x01);

            str_lcd("HOUR:");
            k = keyscan();
			   		char_lcd('*');
					       while(colscan() != 0x0f);
            n = keyscan();
					  char_lcd('*');
             	while(colscan() != 0x0f);
            HOUR = ((k - '0') * 10) + (n - '0');
						delay_ms(100);

            cmd_lcd(0x01);
		
						
						str_lcd("DOW:");
            k = keyscan();
						char_lcd('*');
       						while(colscan() != 0x0f);
            n = keyscan();
						char_lcd('*');
       						while(colscan() != 0x0f);
            DOW = ((k - '0') * 10) + (n - '0');
						delay_ms(100);
						cmd_lcd(0x01);
						
						str_lcd("MONTH:");
            k = keyscan();
						char_lcd('*');
      						while(colscan() != 0x0f);
            n = keyscan();
						char_lcd('*');
    				  		while(colscan() != 0x0f);
            MONTH = ((k - '0') * 10) + (n - '0');
						delay_ms(100);
						
						cmd_lcd(0x01);
						
						str_lcd("YEAR:");
            k = keyscan();
						char_lcd('*'); 
					      	while(colscan() == 0);
            n = keyscan();
  						char_lcd('*');
						  	 while(colscan() == 0);
						i = keyscan();
						char_lcd('*');
					   	   while(colscan() == 0);
            j = keyscan();
						char_lcd('*'); 
						      while(colscan() == 0);
            year = (k - '0') * 1000 +(n - '0')*100+(i - '0') * 10 +(j - '0'); 
						delay_ms(100);
						cmd_lcd(0x01);
            break;
        }

        //  PASSWORD EDIT
        else if(k == '2')
        {
					
            re_password(newpass);
            confirmpw(conformpass);
            checkpw2(newpass, conformpass);
            break;
        }

        // LOGIN TIME EDIT 
        else if(k == '3')
        {
            edit_login_time();
            break;
        }

        else
        {
            break;
        }
    }
}
