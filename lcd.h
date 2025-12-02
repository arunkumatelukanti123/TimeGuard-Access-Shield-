#include "types.h"

void Init_lcd(void);
void cmd_lcd(u8 cmdbyte);
void char_lcd(u8 asciival);
void write_lcd(u8 byte);
void str_lcd(s8 *str);
void int_lcd(u32);
