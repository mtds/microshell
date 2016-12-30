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
