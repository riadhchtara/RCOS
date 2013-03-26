AS=as -Iinclude
LD=ld
CC=gcc
CPP=gcc -E -nostdinc -Iinclude
CFLAGS=-Wall -pedantic -W -nostdlib -nostdinc -Wno-long-long -I include -fomit-frame-pointer

KERNEL_OBJS= load.o init.o isr.o timer.o libcc.o scanf.o scr.o kb.o task.o kprintf.o exceptions.o com.o

#.c.s:
#	${CC} ${CFLAGS} -S -o $*.s $<

.s.o:
	${AS} -a $< -o $*.o >$*.map

all: floppy.flp

floppy.flp: bootsect kernel
	cat bootsect kernel RC.FLP | dd of=floppy bs=512 count=2880
	cat bootsect kernel > floppy.flp

	@wc -c floppy.flp
	bochs -q -f rcos.txt

bootsect: bootsect.o
	${LD} --oformat binary -N -e start -Ttext 0x7c00 -o bootsect $<

kernel: ${KERNEL_OBJS}
	${LD} --oformat binary -N -e pm_mode -Ttext 0x0000 -o $@ ${KERNEL_OBJS}
	@wc -c kernel

clean:
	rm -f *.flp kernel bootsect *.o *.map floppy
	

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in *.c;do ${CPP} -M $$i;done) >> tmp_make
	mv tmp_make Makefile

### Dependencies:
com.o:com.c include/com.h include/task.h include/kernel.h
exceptions.o: exceptions.c include/kprintf.h include/scr.h include/asm.h \
  include/task.h include/kernel.h
init.o: init.c include/scr.h include/isr.h include/asm.h include/kernel.h \
  include/task.h include/libcc.h include/timer.h include/kprintf.h \
  include/kb.h
scanf.o :scanf.c
kb.o: kb.c include/asm.h include/scr.h
kprintf.o: kprintf.c include/scr.h include/asm.h include/kprintf.h
libcc.o: libcc.c include/libcc.h
scr.o: scr.c include/asm.h include/scr.h include/libcc.h
task.o: task.c include/task.h include/kernel.h include/asm.h
timer.o: timer.c include/asm.h include/task.h include/kernel.h \
  include/scr.h include/kprintf.h
