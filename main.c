/*
 *
 * main.c
 *
 */

/* Include common definitions */
#include "commdefs.h"

/* main(): entry point for the shell, whenever a command is executed and terminated
           the shell will be back here.
*/

main()
{
  char *prompt;
  char *curr_dir, *curr_user;
  pid_t pid; /* process PID */
  int fd; /* process file descriptors */
  TOKEN term;

  ignoresig();

  curr_user = getlogin();
  curr_dir = (char *)get_current_dir_name();

  /* If no 'PS2' environment variable is defined the shell prompt will be based
     on the curr_user and curr_dir values.
   */
  if((prompt = (char *)getenv("PS2")) == NULL)
    {  
      prompt = "> ";
      printf("%s@%s %s",curr_user, curr_dir, prompt);
    }
  else 
    printf("%s ", prompt);

  /* Main cycle for the shell */
  while(1)
   {
     term = command(&pid, FALSE, NULL);
     if(term != T_AMP && pid != 0)
       waitfor(pid);
     if(term == T_NL)
       printf("%s@%s %s",curr_user, get_current_dir_name(), prompt);
     for(fd = 3; fd < 20; fd++)
       close(fd); /* ignore errors while closing */
   }
}
