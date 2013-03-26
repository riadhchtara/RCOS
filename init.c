/* RCOS by RCSoft(riadh.chtara@gmail.com)
 * Based on Skelix by Xiaoming Mo (xiaoming.mo@skelix.org)
 * Licence: GPLv2 */
#include <scr.h>
#include <isr.h>
#include <asm.h>
#include <kernel.h>
#include <task.h>
#include <libcc.h>
#include <timer.h>
#include <kprintf.h>
#include <kb.h>
#include <com.h>
unsigned long long *idt = ((unsigned long long *)IDT_ADDR);
unsigned long long *gdt = ((unsigned long long *)GDT_ADDR);
char w1,w2;
static void 
isr_entry(int index, unsigned long long offset) {
	unsigned long long idt_entry = 0x00008e0000000000ULL |
			((unsigned long long)CODE_SEL<<16);
	idt_entry |= (offset<<32) & 0xffff000000000000ULL;
	idt_entry |= (offset) & 0xffff;
	idt[index] = idt_entry;
}

static void 
idt_install(void) {
	unsigned int i = 0;
	struct DESCR {
		unsigned short length;
		unsigned long address;
	} __attribute__((packed)) idt_descr = {256*8-1, IDT_ADDR};
	for (i=0; i<VALID_ISR; ++i)
		isr_entry(i, (unsigned int)(isr[(i<<1)+1]));
	for (++i; i<256; ++i)
		isr_entry(i, (unsigned int)default_isr);
	__asm__ ("lidt	%0\n\t"::"m"(idt_descr));
}

static void 
pic_install(void) {
	outb(0x11, 0x20);
	outb(0x11, 0xa0);
	outb(0x20, 0x21);
	outb(0x28, 0xa1);
	outb(0x04, 0x21);
	outb(0x02, 0xa1);
	outb(0x01, 0x21);
	outb(0x01, 0xa1);
	outb(0xff, 0x21);
	outb(0xff, 0xa1);
}

extern void task1_run(void);
extern void task2_run(void);
extern void task3_run(void);
extern void task4_run(void);

static long task1_stack0[1024] = {0xf, };
static long task1_stack3[1024] = {0xf, };
static long task2_stack0[1024] = {0xf, };
static long task2_stack3[1024] = {0xf, };
static long task3_stack0[1024] = {0xf, };
static long task3_stack3[1024] = {0xf, };
static long task4_stack0[1024] = {0xf, };
static long task4_stack3[1024] = {0xf, };
static void
new_task(struct TASK_STRUCT *task, unsigned int eip, 
				unsigned int stack0, unsigned int stack3,struct SCREEN_STRUCT *taskscreen) {
	memcpy(task, &TASK0, sizeof(struct TASK_STRUCT));
	task->tss.esp0 = stack0;
	task->tss.eip = eip;
	task->tss.eflags = 0x3202;
	task->tss.esp = stack3;
	taskscreen->scr=&(taskscreen->screen[0]);
	task->scr=taskscreen;
	
	task->priority = INITIAL_PRIO;

	task->state = TS_STOPPED;
	task->next = current->next;
	current->next = task;
	task->state = TS_RUNABLE;
	
}


void
do_task1(void) {
	unsigned int i=0;
	char x,y;
	
	w1=0;
	bg(0,0,80,4,BRIGHT_WHITE,BLACK) ;
	bg(0,4,80,25,WHITE,BLUE) ;
	set_cursor(5,3);
	w1=1;
	put("[TASK1]",WHITE,BLUE) ;
	set_cursor(13,3);	
	put("[TASK2]",BLACK,WHITE) ;
	settop(5);
	set_cursor(30,0);
	put("Welcome to RCOS!",BRIGHT_WHITE,BLACK);
	set_cursor(0,1);
	put("This is task 1",BRIGHT_WHITE,BLACK);
	while(1){
	get_cursor(&x,&y);
	set_cursor(67,1);
	put(put32(i),BRIGHT_WHITE,BLACK);
	set_cursor(x,y);
	i++;

	}
	
}
void
do_task2(void) {
		unsigned int i=0;
	char x,y;
	
	w1=0;
	bg(0,0,80,4,BRIGHT_WHITE,BLACK) ;
	bg(0,4,80,25,WHITE,BLUE) ;
	set_cursor(5,3);
	w2=1;
	put("[TASK1]",BLACK,WHITE) ;
	set_cursor(13,3);	
	put("[TASK2]",WHITE,BLUE) ;
	settop(5);
	set_cursor(30,0);
	put("Welcome to RCOS!",BRIGHT_WHITE,BLACK);
	set_cursor(0,1);
	put("This is task 2",BRIGHT_WHITE,BLACK);
	while(1){
	get_cursor(&x,&y);
	set_cursor(67,1);
	put(put32(i),BRIGHT_WHITE,BLACK);
	set_cursor(x,y);
	i++;

	}
}
void
do_task3(void) {
	char *c[BUFFER_SIZE];
	char j;
	set_cursor(0,2);

	kprintf(KPL_PANIC,"This is task 3");
	set_cursor(0,4);
	while(1){
	if(w2==1){
	bg(0,(*current).y,80,(*current).y+1,WHITE,BLUE);
	put("cmd:$>",BRIGHT_WHITE,BLUE);
	
	scanf(c,WHITE,BLUE);
	put("\n",WHITE,BLUE);
	exe(c);
	
	
}
	}
}
void
do_task4(void) {
	char *c[BUFFER_SIZE];
	char j;
	set_cursor(0,2);

	kprintf(KPL_PANIC,"This is task 4");
	set_cursor(0,4);
	while(1){
	if(w2==1){
	bg(0,(*current).y,80,(*current).y+1,WHITE,BLUE);
	put("cmd:$>",BRIGHT_WHITE,BLUE);
	
	scanf(c,WHITE,BLUE);
	put("\n",WHITE,BLUE);
	exe(c);
	
	
}
}}

void 
init(void) {
	char wheel[] = {'\\', '|', '/', '-'};
	int i = 0;
	char *c,K;
	void *j;
	
	
	j=memset(VIDEO_RAM, 0,80*25*2);
	
	
	
	idt_install();
	pic_install();
	kb_install();
	timer_install(100);
	set_tss((unsigned long long)&TASK0.tss);
	set_ldt((unsigned long long)&TASK0.ldt);
	__asm__ ("ltrw	%%ax\n\t"::"a"(TSS_SEL));
	__asm__ ("lldt	%%ax\n\t"::"a"(LDT_SEL));
	sti();
	
	new_task(&task1,
			(unsigned int)task1_run, 
			(unsigned int)task1_stack0+sizeof task1_stack0,
			(unsigned int)task1_stack3+sizeof task1_stack3,&scr1);
	new_task(&task2,
			(unsigned int)task2_run,
			(unsigned int)task2_stack0+sizeof task2_stack0,
			(unsigned int)task2_stack3+sizeof task2_stack3,&scr2);
	new_task(&task3,
			(unsigned int)task3_run, 
			(unsigned int)task3_stack0+sizeof task3_stack0,
			(unsigned int)task3_stack3+sizeof task3_stack3,&scr1);
	new_task(&task4,
			(unsigned int)task4_run,
			(unsigned int)task4_stack0+sizeof task4_stack0,
			(unsigned int)task4_stack3+sizeof task4_stack3,&scr2);
	TASK0.scr=&scr0;
	scr0.scr=VIDEO_RAM;
	live=TASK0.scr;
	initcmd();
	onscreen=&TASK0;
	switchscreen(task1.scr);
	__asm__ ("movl %%esp,%%eax\n\t" \
			 "pushl %%ecx\n\t" \
			 "pushl %%eax\n\t" \
			 "pushfl\n\t" \
			 "pushl %%ebx\n\t" \
			 "pushl $1f\n\t" \
			 "iret\n" \
			 "1:\tmovw %%cx,%%ds\n\t" \
			 "movw %%cx,%%es\n\t" \
			 "movw %%cx,%%fs\n\t" \
			 "movw %%cx,%%gs" \
			 ::"b"(USER_CODE_SEL),"c"(USER_DATA_SEL));
	for (;;) {
		
	}
}
