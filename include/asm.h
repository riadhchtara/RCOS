/* RCOS by RCSoft(riadh.chtara@gmail.com)
 * Based on Skelix by Xiaoming Mo (xiaoming.mo@skelix.org)
 * Licence: GPLv2 */
#ifndef _ASM_H_
#define _ASM_H_

#define cli() __asm__ ("cli\n\t")
#define sti() __asm__ ("sti\n\t")

#define halt() __asm__ ("cli;hlt\n\t");
#define idle() __asm__ ("jmp .\n\t");




#define insl(port, buf, nr) \
__asm__ ("cld;rep;insl\n\t"	\
::"d"(port), "D"(buf), "c"(nr))

#define outsl(buf, nr, port) \
__asm__ ("cld;rep;outsl\n\t"	\
::"d"(port), "S" (buf), "c" (nr))
#define outb(value,port) \
	asm volatile ("outb %%al,%%dx"::"d" (port), "a" (value));



#define inb(port) ({	\
	unsigned char _v;	\
	asm volatile ("inb %%dx,%%al" : "=a" (_v) : "d" (port)); \
	_v;	\
})

#endif
