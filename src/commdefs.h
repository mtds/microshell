/*
 *
 * commdefs.h
 *
 */

/* Enums (TOKEN is used by the shell parser) */

typedef enum {FALSE, TRUE} BOOLEAN;
typedef enum {T_WORD, T_BAR, T_AMP, T_SEMI, T_GT, T_GTGT, T_LT, T_NL, T_EOF} TOKEN;

/* The following macros will extract the most or the least 8 significant bits from a 16 bit word */
#define lowbyte(w) ((w) & 0377)
#define highbyte(w) lowbyte((w)>>8)

/* Headers section: */
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
TOKEN command(int *waitpid, BOOLEAN makepipe,int *pipefdp);
TOKEN gettoken(char *word);
pid_t invoke(int argc, char *argv[], int srcfd, char *srcfile, int dstfd, char *dstfile, BOOLEAN append, BOOLEAN bckgrnd);
void ignoresig();
void entrysig();
void redirect(int srcfd, char *srcfile, int dstfd, char *dstfile, BOOLEAN append, BOOLEAN bckgrnd);
void shell_err(char *msg);
void fatal(char *msg);
void statusprt(pid_t pid, int status);
void waitfor(pid_t pid);

