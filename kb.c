/* RCOS by RCSoft(riadh.chtara@gmail.com)
 * Based on Skelix by Xiaoming Mo (xiaoming.mo@skelix.org)
 * Licence: GPLv2 */
#include <asm.h>
#include <scr.h>
#include <task.h>
#include <kprintf.h>
static unsigned char shf_p = 0;
static unsigned char ctl_p = 0;
static unsigned char alt_p = 0;


/* printable char */
static void
pln(void) {
	
	
	static const char key_map[0x3a][2] = {
		/*00*/{0x0, 0x0}, {0x0, 0x0}, {'1', '!'}, {'2', '@'}, 
		/*04*/{'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, 
		/*08*/{'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'},
		/*0c*/{'-', '_'}, {'=', '+'}, {'\b','\b'},{'\t','\t'},
		/*10*/{'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'},
		/*14*/{'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'},
		/*18*/{'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'},
		/*1c*/{'\n','\n'},{0x0, 0x0}, {'a', 'A'}, {'s', 'S'},
		/*20*/{'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'},
		/*24*/{'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'},
		/*28*/{'\'','\"'},{'`', '~'}, {0x0, 0x0}, {'\\','|'}, 
		/*2c*/{'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, 
		/*30*/{'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'},
		/*34*/{'.', '>'}, {'/', '?'}, {0x0, 0x0}, {'*', '*'},
		/*38*/{0x0, 0x0}, {' ', ' '} };
		struct TASK_STRUCT *tmp;
	tmp=current;
	current=onscreen;
	if((*live).getkey==1){
	if (!((*live).scan_code & 0x80)){	
	
		switch(key_map[(*live).scan_code&0x7f][shf_p]){
			case '\n':
				(*live).enter=1;
				break;
			case '\b':
				if((*live).buf>0){	
				(*live).buf--;
				(*live).del++;
				(*live).kbbuffer[(*live).buf]=0;
				}
				
				(*live).rm++;
				break;
			default:
				
				(*live).kbbuffer[(*live).buf]=key_map[(*live).scan_code&0x7f][shf_p];
				(*live).buf++;
				
				break;
}

	}
	
	}
	current=tmp;
}

/* Ctrl */
static void
ctl(void) {
	ctl_p ^= 0x1;
		
}

/* Alt */
static void
alt(void) {
	
	alt_p ^= 0x1;
}

/* Shift */
static void
shf(void) {
	
	shf_p ^= 0x1;
}

/* F1, F2 ~ F12 */
static void
fu1(void) {
if(crtscr==task2.scr)
switchscreen(task1.scr);
}
static void
fu2(void) {

if(live==task1.scr)
switchscreen(task2.scr);
}

static void
fun(void) {

}
/* not implementated */
static void
unp(void) {(*live).enter=1;
}

void
do_kb(void) {
	
	int com,i;
	void (*key_way[0x80])(void) = {
		/*00*/unp, unp, pln, pln, pln, pln, pln, pln,
		/*08*/pln, pln, pln, pln, pln, pln, pln, pln,
		/*10*/pln, pln, pln, pln, pln, pln, pln, pln,
		/*18*/pln, pln, pln, pln, pln, ctl, pln, pln,
		/*20*/pln, pln, pln, pln, pln, pln, pln, pln,
		/*28*/pln, pln, shf, pln, pln, pln, pln, pln,
		/*30*/pln, pln, pln, pln, pln, pln, shf, pln,
		/*38*/alt, fun, fun, fu1, fu2, fun, fun, fun,
		/*40*/fun, fun, fun, fun, fun, unp, unp, unp,
		/*48*/unp, unp, unp, unp, unp, unp, unp, unp,
		/*50*/unp, unp, unp, unp, unp, unp, unp, fun,
		/*58*/fun, unp, unp, unp, unp, unp, unp, unp,
		/*60*/unp, unp, unp, unp, unp, unp, unp, unp,
		/*68*/unp, unp, unp, unp, unp, unp, unp, unp,
		/*70*/unp, unp, unp, unp, unp, unp, unp, unp,
		/*78*/unp, unp, unp, unp, unp, unp, unp, unp,
	};

	com = 0;

	(*live).scan_code = inb(0x60);
	(*key_way[(*live).scan_code&0x7f])();

	/* key stroke has been handled */
	outb((com=inb(0x61))|0x80, 0x61);
	outb(com&0x7f, 0x61);

	outb(0x20, 0x20);
	
}

void
kb_install(void) {
	outb(inb(0x21)&0xfd, 0x21);
}

