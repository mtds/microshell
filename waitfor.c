/*
 *
 * waitfor.c
 *
 */

#include "commdefs.h"

/* waitfor(): wait till the execution of a child process and call the statusprt
   function to check its status at the end */
void waitfor(pid_t pid)
{
  pid_t wpid; 
  int status;

  while((wpid = wait(&status)) != pid && wpid != -1)
    statusprt(wpid, status);

  if(wpid == pid)
    statusprt(0, status);                	  
}
