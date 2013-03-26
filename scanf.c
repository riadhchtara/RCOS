/* RCOS by RCSoft(riadh.chtara@gmail.com)
 * Based on Skelix by Xiaoming Mo (xiaoming.mo@skelix.org)
 * Licence: GPLv2 */
#include <asm.h>
#include <scr.h>
#include <task.h>
#include <scanf.h>
#include <kprintf.h>
void scanf(char* text,COLOUR fg, COLOUR bg){
	char j;
	char i,x,y;
	
	for(i=0;i< BUFFER_SIZE;++i){
		
		(*crtscr).kbbuffer[i]=0;
		
	}
	i=0;
	
	x=(current->x);
	y=(current->y);
	(*crtscr).getkey=1;
	(*crtscr).enter=0;
	(*crtscr).buf=0;
	(*crtscr).del=0;
	while((*crtscr).enter==0){
	if(crtscr==live){
	
	set_cursor(x,y);
	if ((*crtscr).del>0){
	for(i=0;i<=(*crtscr).buf;i++){
		print_c(' ',fg,bg);
		
	}
}
	(*crtscr).del=0;
	
		
	
	set_cursor(x,y);

	put(&(*crtscr).kbbuffer,fg,bg);
	if(i<(*crtscr).buf)
	i++;

}	
}
	(*crtscr).getkey=0;
	(*crtscr).enter=0;
	j=memcpy(text, &((*crtscr).kbbuffer),BUFFER_SIZE);
	
}

void waitkey(){
	char i,x,y;
	
	for(i=0;i< BUFFER_SIZE;++i){
		
		(*crtscr).kbbuffer[i]=0;
		
	}
	i=0;
	x=(current->x);
	y=(current->y);
	(*crtscr).getkey=1;
	(*crtscr).enter=0;
	(*crtscr).buf=0;
	(*crtscr).rm=0;

	while(((*crtscr).enter==0)&&((*crtscr).rm==0)&&((*crtscr).buf==0)){

	i++;
	
}	
	(*crtscr).rm=0;
	(*crtscr).getkey=0;
	(*crtscr).enter=0;
	
}
	