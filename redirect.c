/*
 *
 * redirect.c
 *
 */

#include "commdefs.h"

/* redirect(): implements I/O redirection */
void redirect(int srcfd, char *srcfile, int dstfd, char *dstfile, BOOLEAN append, BOOLEAN bckgrnd)
{
  int flags, fd;

  if(srcfd == 0 && bckgrnd)
   {
    strcpy(srcfile,"/dev/null");
    srcfd = -2;
   }	  

  if(srcfd != 0)
   {
    if(close(0) == -1)
      shell_err("close");
    if(srcfd > 0)
     {
      if(dup(srcfd) != 0)
        fatal("dup");	      
     }	    
   
    else if (open(srcfile, O_RDONLY, 0) == -1)
     {
      fprintf(stderr, "It is not possible to open %s\n", srcfile);
      exit(0);
     }
   }

  if(dstfd != 1)
   {
    if(close(1) == -1)
     shell_err("close");	    
    if(dstfd > 1)
     {
      if(dup(dstfd) != 1)
       fatal("dup");	      
     }	    
    else
     {
      flags = O_WRONLY | O_CREAT;
      if(!append)
       flags |= O_TRUNC;
      if(open(dstfile, flags, 0666) == -1)
       {
        fprintf(stderr,"It is not possible to create %s\n",dstfile);
	exit(0);
       }
      if(append)
        if(lseek(1, 0L, 2) == -1)
	 shell_err("lseek");	
     }
   }
  for(fd = 3; fd < 20; fd ++)
   close(fd);	  
}	
