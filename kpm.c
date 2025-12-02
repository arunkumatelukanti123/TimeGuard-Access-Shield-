#include "types.h"
#include <LPC21xx.h>
#include "kpm_defines.h"
#include "delay.h"
#include "kpm.h"

u32 kpmLUT[4][4]=
 {{'7','8','9','/'}, {'4','5','6','*'},
 {'1','2','3','-'}, {'A','0','=','+'} };

void Init_KPM(void)
{
                        IODIR1 |= (0x0F << ROWs_4);
 }
u32 colscan(void)
{
          return ((IOPIN1 >> COLs_4) & 0x0F);  
}

u32 RowCheck(void)
{
                u32 r;
                for(r=0; r<4; r++)
                {
                IOSET1 = (0x0F << ROWs_4);           // all rows high
                IOCLR1 = (1 << (ROWs_4 + r));       // drive one row low
                 if( ( (IOPIN1 >> COLs_4) & 0x0F ) != 0x0F )
                       break;
                 }
								  IOCLR1 = (0x0F << ROWs_4); // restore all rows low
                return r;
}
u32 ColCheck(void)
{
   u32 c;
   // data = (IOPIN1 >> COLs_4) & 0x0F;
   for(c=0; c<4; c++)
   {
     if (((IOPIN1 >> (COLs_4+c)) & 1) == 0 )
         break;
         }
         return c;
}
u32 keyscan(void)
{
  u32 r,c;
 while( colscan()==0x0f)
    delay_ms(20);    // debounce
     r = RowCheck();
     c = ColCheck();
  while( colscan() != 0x0F ); 
 delay_ms(50);

  return kpmLUT[r][c];
}
/*u32 ReadNum(void)
{
  u32 num;
  u8 key;
  while(1)
  {
     key=KeyScan();
     if(key >= '0' && key <= '9')
           num = (num * 10) + (key - '0');
         else
           break;
  }
  return num;
}*/
