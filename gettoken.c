/*
 *
 * gettoken.c
 *
 */

#include "commdefs.h"

/* gettoken(): the lexical analyzer is organized like a finite state machine. 
   The names defined in the enum 'state' are the status the analyzer will go
   through while dividing the string in multiple tokens.
*/
TOKEN gettoken(char *word)
{
  enum {NEUTRAL, GTGT, INQUOTE, INWORD} state = NEUTRAL; 	
  int c; /* read characters */
  char *w; 

   w = word; 

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
		   *w++ = c;
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
		        *w++ = getchar();
		        continue;
	    
	      case '"':
	                *w = '\0';
	                return (T_WORD);
	   
	      default:
	               *w++ = c;
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
		        *w = '\0';
		        return (T_WORD);
	      default:
		       *w++ = c;
		       continue;
		    
	     }	  
      } 
    }
  return (T_EOF);
} 
        
