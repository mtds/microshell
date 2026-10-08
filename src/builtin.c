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
  char *end;
  long pid;
  int kill_res; /* return value of kill() */

  if(strchr(argv[0], '=') != NULL)  /* assign a value to an environment variable */
     asg(argc, argv);
  else if(strcmp(argv[0],"printenv") == 0) /* print all the environment variables */
     set(argc, argv);
  else if(strcmp(argv[0],"cd") == 0) /* change directory */
  {
     if(argc > 1)
       path = argv[1];
     else if((path = getenv("HOME")) == NULL)
       path = ".";
     if (chdir(path) == -1)
       fprintf(stderr, "%s: wrong directory\n",path);
  }
  else if(strcmp(argv[0],"kill") == 0)
    {
     if(argc > 1)
      {
       errno = 0;
       pid = strtol(argv[1], &end, 10);
       if(errno != 0 || end == argv[1] || *end != '\0' || pid <= 0)
         fprintf(stderr,"Invalid process PID: %s\n", argv[1]);
       else if((kill_res = kill((pid_t)pid, SIGKILL)) == -1)
         fprintf(stderr,"The process %ld could not be stopped\n", pid);
       else
         fprintf(stdout,"Process %ld killed\n", pid);
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

/* asg(): assign/update a value for an environment variable.
   Syntax:
     NAME=value          -> create/replace the variable NAME
     NAME=prefix$NAME:v  -> append ":v" to the current value of NAME
 */
void asg(int argc, char *argv[])
{
  char *name, *val, *old;
  char *buf;
  size_t len;

  if(argc != 1)
     fprintf(stderr, "Too many arguments\n");
  else if(strchr(argv[0], '$') == NULL)
   {
     /* A new env. variable is created */
     name = strtok(argv[0], "=");
     val = strtok(NULL, "=");
     if(name == NULL || *name == '\0' || val == NULL)
       fprintf(stderr, "Invalid assignment: %s\n", argv[0]);
     else if(setenv(name, val, 1) != 0)
       fprintf(stderr, "Assignment was impossible\n");
   }
  else
   {
     /* Update (append to) an environment variable */
     name = strtok(argv[0], "=");
     if(name == NULL || *name == '\0')
       fprintf(stderr, "Invalid assignment: %s\n", argv[0]);
     else if(strtok(NULL, ":") == NULL || (val = strtok(NULL, ":")) == NULL)
       fprintf(stderr, "Invalid assignment: %s\n", argv[0]);
     else
      {
       old = getenv(name);
       if(old == NULL)
         old = "";
       len = strlen(old) + strlen(val) + 2;
       if((buf = malloc(len)) == NULL)
         fprintf(stderr, "Not enough memory\n");
       else
        {
          if(*old != '\0')
            snprintf(buf, len, "%s:%s", old, val);
          else
            snprintf(buf, len, "%s", val);
          if(setenv(name, buf, 1) != 0)
            fprintf(stderr, "Update was not possible\n");
          free(buf);
        }
      }
   }
}

/* set(): print the environment variables **/
void set(int argc, char *argv[])
{
   int i;
   (void)argv;
   if(argc != 1)
     printf("Too many arguments\n");
   else
     for(i=0; environ[i]!=NULL ; i++)
       fprintf(stdout,"%s\n",environ[i]);
}
