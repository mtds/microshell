/*
 *
 * commdefs.h
 *
 */

/* Enums (TOKEN is used by the shell parser) */

typedef enum {FALSE, TRUE} BOOLEAN;
typedef enum {T_WORD, T_BAR, T_AMP, T_SEMI, T_GT, T_GTGT, T_LT, T_NL, T_EOF} TOKEN;

/* Headers section: */
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

/** Function declarations **/
BOOLEAN builtin(int argc, char *argv[], int srcfd, int dstfd);
void asg(int argc, char *argv[]);
void set(int argc, char *argv[]);
TOKEN command(pid_t *waitpid, BOOLEAN makepipe, int *pipefdp);
TOKEN gettoken(char *word, size_t max);
pid_t invoke(int argc, char *argv[], int srcfd, const char *srcfile, int dstfd, const char *dstfile, BOOLEAN append, BOOLEAN bckgrnd);
void ignoresig(void);
void entrysig(void);
void redirect(int srcfd, const char *srcfile, int dstfd, const char *dstfile, BOOLEAN append, BOOLEAN bckgrnd);
void shell_err(const char *msg);
void fatal(const char *msg);
void statusprt(pid_t pid, int status);
void waitfor(pid_t pid);
void closefds(int from);
