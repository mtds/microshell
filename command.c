/*
 * 
 * command.c
 *
 */


#define MAXARG 20
#define MAXFNAME 45
#define MAXWORD 20

#include "commdefs.h"

/* command(): execute commands from the shell. */
TOKEN command(int *waitpid, BOOLEAN makepipe,int *pipefdp)
{
 TOKEN token, term;
 int argc, srcfd, dstfd, pfd[2];
 pid_t pid;

 char *argv[MAXARG+1], srcfile[MAXFNAME], dstfile[MAXFNAME];
 char word[MAXWORD];
 BOOLEAN append;

 argc = 0;
 srcfd = 0;
 dstfd = 1;

 while(1)
   {
     switch(token = gettoken(word))
       {
         case T_WORD:
		     if(argc == MAXARG)
		      {
		       fprintf(stderr,"Too many arguments\n");
		       break;
		      }     
		     if((argv[argc] = malloc(strlen(word)+1)) == NULL)
		      {
		       fprintf(stderr,"Not enough memory for the arguments\n");
		       break;
		      } 
		     strcpy(argv[argc], word);
		     argc++;
		     continue;
	 case T_LT:
		     if(makepipe)
		      {
		       fprintf(stderr,"Extra <\n");
		       break;
		      }	     
		     if(gettoken(srcfile) != T_WORD)
		      {
		       fprintf(stderr,"< not permitted\n");
		       break;
		      }
		     srcfd = -2;
		     continue;
         case T_GT:
         case T_GTGT:
		     if(dstfd != 1)
		      {
		       fprintf(stderr, "Extra > or >>\n");
		       break;
		      }	     
		     if(gettoken(dstfile) != T_WORD)
		      {
		       fprintf(stderr, "> or >> not permitted\n");
		       break;
		      }
		     dstfd = -2;
		     append = token == T_GTGT;
		     continue;
	 case T_BAR:
         case T_AMP:
         case T_SEMI:
         case T_NL:
		    argv[argc] = NULL;
		    if(token == T_BAR)
		     {
		      if(dstfd != 1)
		       {
		        fprintf(stderr,"> or >> in conflict with |\n");
			break;
		       }    
		      term = command(waitpid, TRUE, &dstfd);
		     }	    
		    else term = token;
		    if(makepipe)
		     {
		      if(pipe(pfd) == -1)
			 shell_err("pipe");
		      *pipefdp = pfd[1];
		      srcfd = pfd[0];
		     }  
		    pid = invoke(argc, argv, srcfd, srcfile, dstfd, dstfile, append, term == T_AMP);
		    if(token != T_BAR)
		      *waitpid = pid;
		    if(argc == 0 && (token != T_NL || srcfd > 1))
		      fprintf(stderr,"Missing command\n");
		    while(--argc >= 0)
		      free(argv[argc]);
		    return (term);
	 
         case T_EOF:
		     exit(0);
       }	    
     
   }	 
}	
