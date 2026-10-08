/*
 *
 * ignoresig.c
 *
 */

#include <string.h>

#include "commdefs.h"

static struct sigaction saved_int;
static struct sigaction saved_quit;

/* ignoresig(): it is called at the start of the shell in order to avoid being blocked
   by other signals coming from the OS.
 */
void ignoresig(void)
{
  struct sigaction ign;
  static BOOLEAN first = TRUE;

  memset(&ign, 0, sizeof(ign));
  ign.sa_handler = SIG_IGN;
  sigemptyset(&ign.sa_mask);

  if(first)
   {
     first = FALSE;

     if(sigaction(SIGINT, &ign, &saved_int) == -1 ||
        sigaction(SIGQUIT, &ign, &saved_quit) == -1)
       shell_err("sigaction");
   }
  else
   {
     if(sigaction(SIGINT, &ign, NULL) == -1 ||
        sigaction(SIGQUIT, &ign, NULL) == -1)
       shell_err("sigaction");
   }
}

/* entrysig(): enable again the interrupts */
void entrysig(void)
{
  if(sigaction(SIGINT, &saved_int, NULL) == -1 ||
     sigaction(SIGQUIT, &saved_quit, NULL) == -1)
    shell_err("sigaction");
}
