/* RCOS by RCSoft(riadh.chtara@gmail.com)
 * Based on Skelix by Xiaoming Mo (xiaoming.mo@skelix.org)
 * Licence: GPLv2 */
#ifndef COM_H
#define COM_H

#include <kernel.h>
#include <task.h>
#include <libcc.h>
#define cmdn 11

struct COM_STRUCT {
	void (*fun)(void);
	char *command[BUFFER_SIZE];
};


struct COM_STRUCT cmd[cmdn];
void initcmd();
void exe(char * c);


void gettime();
void getdate();
#endif
