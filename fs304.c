
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <stddef.h>
#include "fs304.h"


int parseCommand(char input[], char *args[])
{
    int length,		/* # of characters in the command line */
      i,			/* loop index for accessing inputBuffer array */
      start,		/* index where beginning of next command parameter is */
      ct,	        	/* index of where to place the next parameter into args[] */
      command_number;	/* index of requested command number */

    ct = 0;

    /* read what the user enters on the command line */
    do {
	  printPrompt();
	  fflush(stdout);
	  length = read(STDIN_FILENO,input,50);
    }
    while (input[0] == '\n'); /* swallow newline characters */


    start = -1;
    if (length == 0)
      exit(0);            /* ^d was entered, end of user command stream */

  

    /**
     * Parse the contents of input[]
     */

    for (i=0;i<length;i++) 
    {
      /* examine every character in the inputBuffer */

      switch (input[i]){
      case ' ':
      case '\t' :               	/* argument separators */
	if(start != -1){
	  args[ct] = &input[start];    /* set up pointer */
	  ct++;
	}
	input[i] = '\0'; 		/* add a null char; make a C string */
	start = -1;
	break;

      case '\n':                 	/* should be the final char examined */
	if (start != -1){
	  args[ct] = &input[start];
	  ct++;
	}
	input[i] = '\0';
	args[ct] = NULL; /* no more arguments to this command */
	break;

      default :             /* some other character */
	if (start == -1)
	  start = i;
      } /* end of switch */
    }    /* end of for */

    return 1;

}


int main(void)
{
    	char input[50]; 
    	char *args[50];	        /* buffer to hold the command entered */
	int running = 1;
	mountFS304();     	/* Initial mount command for FS304 to process the disk emulator. */

	while(running)
	{
		running = parseCommand(input, args);
		if (strncmp(input, "exit", 4) == 0)
		{
			printf("Application terminating goodbye!\n");
      		running = 0;     /* Exiting from FS304*/
		}
		else if (strncmp(input, "ls", 2) == 0){
			ls();
		}
		else if (strncmp(input, "md", 2) == 0){
			md(args[1]);
		}
		else if (strncmp(input, "cd", 2) == 0){
			cd(args[1]);
		}
		else if (strncmp(input, "stats", 5) == 0){
			stats();
		}
		else if (strncmp(input, "rd", 2) == 0){
			rd();
		}
		else if (strncmp(input, "compare", 7) == 0){
			compare(args[1], args[2]);
		}
		else if (strncmp(input, "copy", 4) == 0){
			copy(args[1], args[2]);
		}
		else if (strncmp(input, "rename", 6) == 0){
			rename_(args[1], args[2]);
		}else {
			printf("Unknown command!\n");
		}
	}
	return 0;
}
