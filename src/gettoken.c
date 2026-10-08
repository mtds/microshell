/*
 *
 * gettoken.c
 *
 */

#include <stddef.h>

#include "commdefs.h"

/* gettoken(): the lexical analyzer is organized like a finite state machine.
   The names defined in the enum 'state' are the status the analyzer will go
   through while dividing the string in multiple tokens.
   Tokens are stored in 'word', whose total capacity is 'max' bytes; any
   excess characters are read and discarded so parsing continues safely.
*/
TOKEN gettoken(char *word, size_t max)
{
  enum {NEUTRAL, GTGT, INQUOTE, INWORD} state = NEUTRAL;
  int c; /* read characters */
  char *w, *end;

  if(max == 0)
    max = 1; /* keep 'end' valid; token will always be empty */
  w = word;
  end = word + max - 1;

#define PUTCH(ch) do { if(w < end) *w++ = (char)(ch); } while(0)
#define ENDWORD() do { *w = '\0'; } while(0)

  while((c = getchar()) != EOF)
   {
     switch(state)
      {
        case NEUTRAL:
          switch(c)
           {
            case ';': return (T_SEMI);

            case '&': return (T_AMP);

            case '|': return (T_BAR);

            case '<': return (T_LT);

            case '\n': return (T_NL);

            case ' ':

            case '\t': continue;

            case '>': state = GTGT;
                      continue;

            case '"': state = INQUOTE;
                      continue;

            default: state = INWORD;
                     PUTCH(c);
                     continue;
           }

        case GTGT:
             if(c == '>')
               return(T_GTGT);
             ungetc(c, stdin);
             return (T_GT);

        case INQUOTE:
             switch(c)
              {
               case '\\':
                         if((c = getchar()) == EOF)
                          {
                            ENDWORD();
                            return (T_WORD);
                          }
                         PUTCH(c);
                         continue;

               case '"':
                         ENDWORD();
                         return (T_WORD);

               default:
                        PUTCH(c);
                        continue;
              }

        case INWORD:
             switch(c)
              {
               case ';':
               case '&':
               case '|':
               case '<':
               case '>':
               case '\n':
               case ' ':
               case '\t':
                         ungetc(c, stdin);
                         ENDWORD();
                         return (T_WORD);
               default:
                        PUTCH(c);
                        continue;

              }
      }
    }
  ENDWORD();
  return (T_EOF);
}
