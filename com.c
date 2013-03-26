/* RCOS by RCSoft(riadh.chtara@gmail.com)
 * Based on Skelix by Xiaoming Mo (xiaoming.mo@skelix.org)
 * Licence: GPLv2 */
#include <asm.h>
#include <scr.h>
#include <com.h>
#include <kprintf.h>
 unsigned read_cmos(int reg)
{
	outb( reg,0x70);
        return inb(0x71);
}

void date()
{
	char y,m,d;
	y=read_cmos(9);
	m=read_cmos(8);
	d=read_cmos(7);
	put("The date is       ",BLUE,WHITE);
	put(dec8(y>>4),BLUE,WHITE);put(dec8(y&0x0f),BLUE,WHITE);put("/",BLUE,WHITE);
	put(dec8(m>>4),BLUE,WHITE);put(dec8(m&0x0f),BLUE,WHITE);put("/",BLUE,WHITE);
	put(dec8(d>>4),BLUE,WHITE);put(dec8(d&0x0f),BLUE,WHITE);put("\n",BLUE,WHITE);

}
static void reboot(void)
{
	unsigned temp;

	do
	{
		temp = inb(0x64);
		if((temp & 0x01) != 0)
		{
			(void)inb(0x60);
			continue;
		}
	} while((temp & 0x02) != 0);
/* pulse the CPU reset line */
	outb(0xFE,0x64);
/* ...and if that didn't work, just halt */
	while(1)
		/* nothing */;
}
void time()
{
	char h,m,s;
	h=read_cmos(4);
	m=read_cmos(2);
	s=read_cmos(0);
	put("The time is       ",BLUE,WHITE);

	put(dec8(h>>4),BLUE,WHITE);put(dec8(h&0x0f),BLUE,WHITE);put(":",BLUE,WHITE);
	put(dec8(m>>4),BLUE,WHITE);put(dec8(m&0x0f),BLUE,WHITE);put(":",BLUE,WHITE);
	put(dec8(s>>4),BLUE,WHITE);put(dec8(s&0x0f),BLUE,WHITE);put("\n",BLUE,WHITE);
            
	
        
}
void hello()
{
	put("Hello World!",BLUE,WHITE);	put("\n",BLUE,WHITE);
	put("Press any key to continue!",BLUE,BRIGHT_WHITE);
bg(0,(*current).y,80,(*current).y+1,BLUE,BRIGHT_WHITE);
	 waitkey();
		put("\n",BLUE,BRIGHT_WHITE);

}
void test()
{
	char n[BUFFER_SIZE];
	put("What is your name? ",BLUE,WHITE);
	bg(0,(*current).y,80,(*current).y+1,BLUE,WHITE);
	scanf(&n,BLUE,WHITE);
	put("\nYou are :",BLUE,WHITE);
	put(&n,BLUE,WHITE);put("\n",BLUE,WHITE);
	put("Press any key to continue!",BLUE,BRIGHT_WHITE);
	bg(0,(*current).y,80,(*current).y+1,BLUE,BRIGHT_WHITE);
	 waitkey();
	put("\n",BLUE,BRIGHT_WHITE);
}
static void help(void) {
	put("This is the help of RCOS\n\tPRESS F1 F2 TO SWITCH SCREEN\n\tAVAILBLE COMMANDS\n\t\thelp\n\t\tinfo\n\t\ttime\n\t\tdate\n\t\thello",BLUE,WHITE);
	put("\n\t\ttest\n\t\treboot\n",BLUE,WHITE);
	
}

static void info(void) {
	put("This is RCOS by RCSOFT(RIADH CHTARA) based on Skelix by Xiaoming\nTHANK YOU\n",BLUE,WHITE);
	
	
}

static void clsc(void) {
	cls();
	bg(0,(*crtscr).top-1,80,25,WHITE,BLUE);
	
}

static void com3(void) {

	
}
void wrong(char * c){
	kprintf(KPL_PANIC,"unknown command %s\n",c);
}
char cmp(const char *s1, const char *s2) {
	while (*s1 && *s2) {
		int r = *s1++ - *s2++;
		if(!(r==0)) return 0;
		
	}
	if (*s1!=*s2) return 0;
	return 1;
}
void initcmd() {
	
	char i;
	char *j;
	void (*all[cmdn])(void) = {
		help,info,time,date,clsc,reboot,hello,test
	};
	char *name[cmdn][BUFFER_SIZE]={"help","info","time","date","cls","reboot","hello","test"};
	for(i=0;i<cmdn;i++){
	j=strcpy(cmd[i].command,&((*name)[i])) ;
	cmd[i].fun=&*all[i];
	
	
	
}

}

void exe(char * c){
	char i,s;
	s=0;
	for(i=0;i<cmdn;i++){
	
	if(cmp(c,*cmd[i].command)) {
	(*cmd[i].fun)();
	s=1;
}
	
	

}
	if(s==0) wrong(c);
}

