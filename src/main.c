/*
 *
 * main.c
 *
 */

/* Include common definitions */
#include "commdefs.h"

/* currentUserName(): best-effort user name, since getlogin() may return NULL
   (e.g. no controlling terminal).
 */
static const char *currentUserName(void)
{
  const char *user;

  if((user = getlogin()) != NULL)
    return user;
  if((user = getenv("USER")) != NULL)
    return user;
  return "user";
}

/* main(): entry point for the shell, whenever a command is executed and terminated
           the shell will be back here.
*/

int main(void)
{
  char buffer[1024];
  const char *prompt, *curr_dir, *curr_user;
  pid_t pid; /* process PID */
  TOKEN term;

  ignoresig();

  curr_user = currentUserName();
  curr_dir = (getcwd(buffer, sizeof(buffer)) != NULL) ? buffer : "?";

  /* If no 'PS2' environment variable is defined the shell prompt will be based
     on the curr_user and curr_dir values.
   */
  if((prompt = getenv("PS2")) == NULL)
    {
      prompt = "> ";
      printf("%s@%s %s",curr_user, curr_dir, prompt);
    }
  else
    printf("%s ", prompt);
  fflush(stdout);

  /* Main cycle for the shell */
  while(1)
   {
     term = command(&pid, FALSE, NULL);
     if(term != T_AMP && pid != 0)
       waitfor(pid);
     if(term == T_NL)
       {
         curr_dir = (getcwd(buffer, sizeof(buffer)) != NULL) ? buffer : "?";
         if(getenv("PS2") == NULL)
           printf("%s@%s %s",curr_user, curr_dir, prompt);
         else
           printf("%s ", prompt);
         fflush(stdout);
       }
     closefds(3);
   }
}
