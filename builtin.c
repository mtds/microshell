/*
 *
 * builtin.c
 *
 */

#include "commdefs.h"

extern char **environ; /* it contains the environment variables */

/** Prototypes **/
void asg(int argc, char *argv[]);
void set(int argc, char *argv[]);

/* builtin(): it will return TRUE if the user uses a builtin shell command, FALSE otherwise. */ 
BOOLEAN builtin(int argc, char *argv[], int srcfd, int dstfd)
{
  char *path;
  pid_t pid;
  int kill_res; /* return value of kill() */
 
  if(strchr(argv[0], '=') != NULL)  /* assign a value to an environment variable */
     asg(argc, argv);
  else if(strcmp(argv[0],"printenv") == 0) /* print all the environment variables */
     set(argc, argv);
  else if(strcmp(argv[0],"cd") == 0) /* change directory */
  {
     if(argc > 1)
       path = argv[1];   
     else if((path = (char *)getenv("HOME")) == NULL)
       path = ".";
     if (chdir(path) == -1)
       fprintf(stderr, "%s: wrong directory\n",path);
  }
  else if(strcmp(argv[0],"kill") == 0)
    {
     if(argc > 1)
      {
       pid = atoi(argv[1]); /* convert a string into an integer */
       kill_res = kill(pid, SIGKILL);
       if(kill_res == -1)
         fprintf(stderr,"The process %d could not be stopped\n",pid);
       else
         fprintf(stdout,"Process %d killed\n",pid);
      } 
    else 
      fprintf(stderr,"It is necessary to specify the process PID\n");    
   }	 

  else if(strcmp(argv[0],"exit") == 0) /* the user wants to leave the shell */
    exit(0);

  else return (FALSE); /* none of the builtin commands were called */

  if(srcfd != 0 || dstfd != 1)
    fprintf(stderr, "Redirection or pipeline not permitted\n");

   return (TRUE);
}

/* asg(): assign/update a value for an environment variable */
void asg(int argc, char *argv[])
{
  char *name, *val, *token;
  char *append;
 
  if(argc != 1)
     printf("Too many arguments\n");
  else
  {
     token = strdup(argv[0]);
     name = strtok(argv[0], "=");   
     token = strchr(token, '$');
     if(token == NULL)          /* A new env. variable is created */
      {	   
        val = strtok(NULL, "\1");
        if(setenv(name, val, 1))
          printf("Assignment was impossible");
      }

     /* Update an environment variable */
     else
     {
       val = strtok(NULL,":");	  
       val = strtok(NULL,":");
       append = getenv(name);
       append = strcat(append,":");
       val = strcat(append,val);
       if(setenv(name, val, 1))
         printf("Update was not possible");
     }  
  }
}

/* set(): print the environment variables **/
void set(int argc, char *argv[])
{
   int i;
   if(argc != 1)
     printf("Too many arguments\n");
   else
     for(i=0; environ[i]!=NULL ; i++)
       fprintf(stdout,"%s\n",environ[i]);
}
