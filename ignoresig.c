/*
 *
 * ignoresig.c
 *
 */

#include "commdefs.h"

static int (*entryint)() ,(*entryquit)();
#define BADSIG (int (*)()) -1 

/* ignoresig(): it is called at the start of the shell in order to avoid being blocked
   by other signals coming from the OS.
 */
void ignoresig()
{
  static BOOLEAN first = TRUE;

  if(first)
   {
     first = FALSE;

     entryint = signal(SIGINT, SIG_IGN);
     entryquit = signal(SIGQUIT, SIG_IGN);

     if(entryint == BADSIG || entryquit == BADSIG)
      shell_err("signal");   
   }
  else if (signal(SIGINT, SIG_IGN) == BADSIG || signal(SIGQUIT, SIG_IGN) == BADSIG)
    shell_err("signal");
}

/* entrysig(): enable again the interrupts */
void entrysig()
{
  if(signal(SIGINT, entryint) == BADSIG || signal(SIGQUIT, entryquit) == BADSIG)
    shell_err("signal");
}

