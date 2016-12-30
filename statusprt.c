/*
 *
 * statusprt.c
 *
 */

#include "commdefs.h"
#define MAXSIG 19

/* statusprt(): check the status code of a process */
void statusprt(pid_t pid, int status)
{
  int code;

  static char *sigmsg[]= {
    "",
    "Hangup",
    "Interrupt",
    "Quit",
    "Illegal instruction",
    "Trace trap",
    "IOT instruction",
    "EMT instruction",
    "Floating point exception",
    "Kill",
    "Bus error",
    "Segmentation violation",
    "Bad arg to sys call",
    "Write on pipe",
    "Alarm clock",
    "Terminate signal",
    "User signal 1",
    "User signal 2",
    "Death of child",
    "Power fail"
  };

  if(status != 0 && pid != 0)
    printf("Process %d: ",pid);

   if(lowbyte(status) == 0)
   {
    if((code = highbyte(status)) != 0)
      printf("Exit code %d\n", code);
   } 
   else 
   {
     if((code = status & 0177) <= MAXSIG)
       printf("%s",sigmsg[code]);
     else
       printf("Signal #%d", code);

     if((status & 0200) == 0200)
       printf("- core dumped");
     printf("\n");
   }
}	
