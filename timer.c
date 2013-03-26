/* RCOS by RCSoft(riadh.chtara@gmail.com)
 * Based on Skelix by Xiaoming Mo (xiaoming.mo@skelix.org)
 * Licence: GPLv2 */
#include <asm.h>
#include <task.h>
#include <scr.h>
#include <kprintf.h>

void timer_install(int hz) {
	unsigned int divisor = 1193180/hz;
	outb(0x36, 0x43);
	outb(divisor&0xff, 0x40);
	outb(divisor>>8, 0x40);
	outb(inb(0x21)&0xfe, 0x21);
}

volatile unsigned int timer_ticks = 0;

void do_timer(void) {
	struct TASK_STRUCT *v = &TASK0;
	int x, y;
	cli();
	++timer_ticks;
	
	
	
	for (; v; v=v->next) {
		if (v->state == TS_RUNNING) {
			if ((v->priority+=30) <= 0)
				v->priority = 0xffffffff;
		} else
			v->priority -= 10;
	}
	outb(0x20, 0x20);
	sti();
	if (! (timer_ticks%1))
		scheduler();
	
}
