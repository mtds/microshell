/*
 *
 * invoke.c
 *
 */

#include "commdefs.h"

/* invoke(): launch a command */
pid_t invoke(int argc, char *argv[], int srcfd, char *srcfile, int dstfd, char *dstfile, BOOLEAN append, BOOLEAN bckgrnd)
{
  pid_t pid;

  if(argc == 0 || builtin(argc, argv, srcfd, dstfd))
     return (0);

  switch (pid = fork())
   {
    case -1:
	    fprintf(stderr,"New process cannot be created\n");
	    return (0);

    case 0:
	    if(!bckgrnd)
	     entrysig(); /* re-enable signals */
	    redirect(srcfd, srcfile, dstfd, dstfile, append, bckgrnd);
	    execvp(argv[0], argv);
	    fprintf(stderr,"Execution of %s was not possible\n", argv[0]);
	    exit(0);

     default:
	     if(srcfd > 0 && close(srcfd) == -1)
	       shell_err("close src");
	     if(dstfd > 1 && close(dstfd) == -1)
	       shell_err("close dst");
	     if(bckgrnd)
	       printf("%d\n",pid);	     
	     return (pid);
   }
}	
