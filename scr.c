/* RCOS by RCSoft(riadh.chtara@gmail.com)
 * Based on Skelix by Xiaoming Mo (xiaoming.mo@skelix.org)
 * Licence: GPLv2 */
#include <asm.h>
#include <scr.h>
#include <libcc.h>
#include <kprintf.h>

void settop(char t){
	(*crtscr).top=t;
}
static void 
scroll(int lines) {
	int x = MAX_COLUMNS-1, y = MAX_LINES*(lines-1)+MAX_LINES-1;
	short *p = (short *)(VIDEO_RAM+CHAR_OFF(x, y));
	int i = MAX_COLUMNS*(lines-1) + MAX_COLUMNS;
	memcpy((void *)(*crtscr).scr+(*crtscr).top*LINE_RAM, (void *)((*crtscr).scr+LINE_RAM*((*crtscr).top+lines)),
		   LINE_RAM*(MAX_LINES-lines-(*crtscr).top));
	for (; i>0; --i)
		*p-- = (short)((BLANK_ATTR<<8)|BLANK_CHAR);
}
void cls() {
	char *d;
	char i,j;
	for (j=(*crtscr).top-1; j<25;j++){
	for (i=0; i<80;i++){
		d=(*crtscr).scr+2*i+j*80*2;
		*d=0;
		*(d+1)=0;
}}
	(*current).x=0;
	(*current).y=(*crtscr).top-1;
}
void bg(char x1,char y1,char x2,char y2,COLOUR fg, COLOUR bg) {
	char *d;
	char i,j;
	for (j=y1; j<y2;j++){
	for (i=x1; i<x2;i++){
		d=(*crtscr).scr+2*i+j*80*2;
		*(d+1)=(char)(bg<<4|fg);
}}
	}

void 
set_cursor(char x, char y) {
	(*current).x=x;
	(*current).y=y;
	
}

void
get_cursor(char *x, char *y) {
	x=&(current->x);

	y=&(current->y);
}
void 
print_c(char c, COLOUR fg, COLOUR bg) {
	char *p; 
	char attr;
	p = (char *)(*crtscr).scr+CHAR_OFF((*current).x, (*current).y);
	attr = (char)(((bg<<4))|fg);
	switch (c) {
	case '\r':
		(*current).x = 0;
		break;
	case '\n':
		for (; (*current).x<MAX_COLUMNS; ++(*current).x) {
			*p++ = BLANK_CHAR;
			*p++ = attr;
		}
		break;
	case '\t':
		c = (*current).x+TAB_WIDTH-((*current).x&(TAB_WIDTH-1));
		c = c<MAX_COLUMNS?c:MAX_COLUMNS;
		for (; (*current).x<c; ++(*current).x) {
			*p++ = BLANK_CHAR;
			*p++ = attr;
		}
		break;
	case '\b':
		if ((! (*current).x) && (! (*current).y))
			return;
		if (! (*current).x) {
			(*current).x = MAX_COLUMNS - 1;
			--(*current).y;
		} else
			--(*current).x;
		((short *)p)[-1] = (short)((BLANK_ATTR<<8)|BLANK_CHAR);
		break;
	default:
		*p++ = c; 
		*p++ = attr;
		++(*current).x;
		break;
	}
	if ((*current).x >= MAX_COLUMNS) {
		(*current).x = 0;
		if ((*current).y < MAX_LINES-1)
			++(*current).y;
		else 
			scroll(1);
	}
	

}


void switchscreen(struct SCREEN_STRUCT *s){
	void *j;
	char *c;
	char i;
	live->scr=&(live->screen[0]);
	j=memcpy(&(live->screen[0]),VIDEO_RAM , 80*25*2);
	live=s;
	live->scr=VIDEO_RAM;
	j=memcpy(VIDEO_RAM, &(live->screen[0]), 80*25*2);
	if(live==&scr1) onscreen=&task3;
	else onscreen=&task4;
	
}

void put(const char *k,COLOUR fg, COLOUR bg){
	char j;
	for(j=0;*(k+j)!=0;j++){
	print_c(*(k+j),fg,bg);
	
	}
}
char * hex(unsigned char n){
	char c1, c2;
	char ret[4];
	char *tab = "0123456789ABCDEF";
	c1 = tab[(n & 0xF0)>>4];
	c2 = tab[n & 0x0F];
	ret[0]=c1;
	ret[1]=c2;
	ret[2]=0;
	return &ret;
}

char * put8(unsigned char n){

	char *ret="0x011";
	char *j;
	ret=ret+2;
	j=strcpy(ret,hex(n)) ;
	return ret-2;

}
char * put16(unsigned short n){
	unsigned char n1,n2;
	char *ret="0x01 01 ";
	char *j;
	n1=(unsigned char) n;
	n2=(unsigned char) ((n & 0xff00)>>8);
	ret=ret+2;
	j=strcpy(ret,hex(n2)) ;
	*(ret+2)=' ';
	j=strcpy(ret+3,hex(n1)) ;

	return ret-2;
}

char * put32(unsigned int n){
	unsigned char n1,n2,n3,n4;
	char *ret="0x01 01 01 01 01";
	char *j;
	n1=(unsigned char) n;
	n2=(unsigned char) ((n & 0xff00)>>8);
	n3=(unsigned char) ((n & 0xff0000)>>16);
	n4=(unsigned char) ((n & 0xff000000)>>24);
	ret=ret+2;
	j=strcpy(ret,hex(n4)) ;
	*(ret+2)=' ';
	j=strcpy(ret+3,hex(n3)) ;
	*(ret+5)=' ';
	j=strcpy(ret+6,hex(n2)) ;	
	*(ret+8)=' ';
	j=strcpy(ret+9,hex(n1)) ;
	return ret-2;
}
char * dec8(unsigned char n){
	
	char *ret="123";
	char *tab = "0123456789";
	char i;
	if(n/100==0) i++;
	if(n/10==0) i++;
	*ret=tab[n/100];
	*(ret+1)=tab[(n%100)/10];
	*(ret+2)=tab[n%10];
	return ret+i;
}
char * dec16(unsigned short n){
	
	char *ret="+++++";
	int i,j,k;
	
	char *tab = "0123456789";
	j=1;
	k=n;
	*(ret+6)=0;
	for (i=1; i<6; i++){
	if ((k/j)==0) {
	
	
	break;
	}
	
	else {
*(ret-i+6)=tab[(k/j)%10];
}
	j=j*10;
}
	*(ret+6)=0;
	return ret-i+7;
}
char * dec32(unsigned int n){
	
	char *ret="---------------";
	int i,j;
	char *k;
	char *tab = "0123456789";
	j=1;
	
	for (i=1; i<11; i++){
	if ((n/j)==0) {
	
	
	break;
	}
	
	else {
*(ret-i+10)=tab[(n/j)%10];
}
	j=j*10;
}
	*(ret+10)=0;
	return (ret-i+11);
}