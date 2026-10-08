/*
 *
 * closefds.c
 *
 */

#include "commdefs.h"

/* closefds(): close every file descriptor from 'from' up to the process
   limit; errors are ignored on purpose (the descriptor may simply be closed).
 */
void closefds(int from)
{
  long max, fd;

  if((max = sysconf(_SC_OPEN_MAX)) < 0 || max > 4096)
    max = 4096; /* bound the loop on weird or failing limits */

  for(fd = from; fd < max; fd++)
    close((int)fd);
}
