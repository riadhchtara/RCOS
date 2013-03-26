/* RCOS by RCSoft(riadh.chtara@gmail.com)
 * Based on Skelix by Xiaoming Mo (xiaoming.mo@skelix.org)
 * Licence: GPLv2 */
#ifndef TASK_H
#define TASK_H

#include <kernel.h>

#define TS_RUNNING	0
#define TS_RUNABLE	1
#define TS_STOPPED	2
#define BUFFER_SIZE	100
struct TSS_STRUCT {
	unsigned int back_link;
	unsigned int esp0, ss0;
	unsigned int esp1, ss1;
	unsigned int esp2, ss2;
	unsigned int cr3;
	unsigned int eip;
	unsigned int eflags;
	unsigned int eax,ecx,edx,ebx;
	unsigned int esp, ebp;
	unsigned int esi, edi;
	unsigned int es, cs, ss, ds, fs, gs;
	unsigned int ldt;
	unsigned int trace_bitmap;
};
struct SCREEN_STRUCT {
	unsigned char screen[25*80*2];
	unsigned char x,y;
	void *scr;
	char enter,getkey;
	char kbbuffer[BUFFER_SIZE];
	char buf;
	char scan_code;
	char del;
	char rm;
	char top;
};
struct TASK_STRUCT {
	struct TSS_STRUCT tss;
	unsigned long long tss_entry;
	unsigned long long ldt[2];
	unsigned long long ldt_entry;
	int state;
	int priority;
	struct SCREEN_STRUCT *scr;
	struct TASK_STRUCT *next;
	char x,y;
};

#define DEFAULT_LDT_CODE	0x00cffa000000ffffULL
#define DEFAULT_LDT_DATA	0x00cff2000000ffffULL

#define INITIAL_PRIO		200

extern struct TASK_STRUCT TASK0;
extern struct TASK_STRUCT *current;
struct SCREEN_STRUCT scr0,scr1,scr2;
struct SCREEN_STRUCT *live,*crtscr;
struct TASK_STRUCT *onscreen;
struct TASK_STRUCT task1;
struct TASK_STRUCT task2;
struct TASK_STRUCT task3;
struct TASK_STRUCT task4;
unsigned long long set_tss(unsigned long long tss);
unsigned long long set_ldt(unsigned long long ldt);
unsigned long long get_tss(void);
unsigned long long get_ldt(void);

void scheduler(void);

#endif
