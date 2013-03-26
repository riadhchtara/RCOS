/* RCOS by RCSoft(riadh.chtara@gmail.com)
 * Based on Skelix by Xiaoming Mo (xiaoming.mo@skelix.org)
 * Licence: GPLv2 */
#ifndef SCR_H
#define SCR_H

#define MAX_LINES	25
#define MAX_COLUMNS	80
#define TAB_WIDTH	8			/* must be power of 2 */

/* color text mode, the video ram starts from 0xb8000,
   we all have color text mode, right? :) */
#define VIDEO_RAM	0xb8000

#define LINE_RAM	(MAX_COLUMNS*2)

#define PAGE_RAM	(MAX_LINE*MAX_COLUMNS)

#define BLANK_CHAR	(' ')
#define BLANK_ATTR	(0x07)		/* white fg, black bg */

#define CHAR_OFF(x,y)	(LINE_RAM*(y)+2*(x))
#include <task.h>
typedef enum COLOUR_TAG {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, WHITE,
	GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, 
	LIGHT_RED, LIGHT_MAGENTA, YELLOW, BRIGHT_WHITE
} COLOUR;

void switchscreen(struct SCREEN_STRUCT *s);
void set_cursor(char, char);
void get_cursor(char *, char *);
void print_c(char, COLOUR, COLOUR);
char * put8(unsigned char n);
char * put16(unsigned short n);
char * dec8(unsigned char n);
char * dec16(unsigned short n);
char * dec32(unsigned int n);
char * put32(unsigned int n);
void put(const char *k,COLOUR fg, COLOUR bg);
void settop(char t);
void cls();
void bg(char x1,char y1,char x2,char y2,COLOUR fg, COLOUR bg) ;
#endif
