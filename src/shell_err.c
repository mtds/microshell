/*
 *
 * shell_err.c
 *
 */

#include "commdefs.h"

/** shell_err(): prints the error message of a syscall **/

void shell_err(const char *msg)
{
  fprintf(stderr,"ERROR: %s (%d",msg, errno);

  if(errno > 0)
     fprintf(stderr,"; %s)\n",strerror(errno));
  else
     fprintf(stderr,")\n");

  exit(1);
}

/** fatal(): prints an error message then exit **/

void fatal(const char *msg)
{
  fprintf(stderr,"ERROR: %s\n",msg);
  exit(1);
}
