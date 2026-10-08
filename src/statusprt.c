/*
 *
 * statusprt.c
 *
 */

#include "commdefs.h"

/* statusprt(): check the status code of a process */
void statusprt(pid_t pid, int status)
{
  int code;

  if(status != 0 && pid != 0)
    printf("Process %d: ",(int)pid);

   if(WIFEXITED(status))
   {
    if((code = WEXITSTATUS(status)) != 0)
      printf("Exit code %d\n", code);
   }
   else if(WIFSIGNALED(status))
   {
     printf("%s", strsignal(WTERMSIG(status)));

     if(WCOREDUMP(status))
       printf("- core dumped");
     printf("\n");
   }
}
