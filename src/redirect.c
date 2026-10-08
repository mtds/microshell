/*
 *
 * redirect.c
 *
 */

#include "commdefs.h"

/* redirect(): implements I/O redirection; it runs in the child process. */
void redirect(int srcfd, const char *srcfile, int dstfd, const char *dstfile, BOOLEAN append, BOOLEAN bckgrnd)
{
  int flags, fd;

  if(srcfd == 0 && bckgrnd)
   {
    if((srcfd = open("/dev/null", O_RDONLY)) == -1)
      shell_err("open /dev/null");
   }

  if(srcfd != 0)
   {
    if(srcfd > 0)
      fd = srcfd;

    else if((fd = open(srcfile, O_RDONLY)) == -1)
     {
      fprintf(stderr, "It is not possible to open %s\n", srcfile);
      _exit(1);
     }

    if(dup2(fd, 0) == -1)
      fatal("dup2");
    if(fd > 0)
      close(fd);
   }

  if(dstfd != 1)
   {
    if(dstfd > 1)
      fd = dstfd;

    else
     {
      flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
      if((fd = open(dstfile, flags, 0644)) == -1)
       {
        fprintf(stderr,"It is not possible to create %s\n",dstfile);
        _exit(1);
       }
     }

    if(dup2(fd, 1) == -1)
      fatal("dup2");
    if(fd > 1)
      close(fd);
   }
  closefds(3);
}
