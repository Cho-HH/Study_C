#include <stdio.h>
#include "translate.h"

int translate(int argc, const char** argv)
{	
	while(1) {
		int c;
		c = getchar();
		if (c == EOF) {
			perror("c is EOF");
			break;
		}
		putchar(c);
	}
		
		return 0;
}
