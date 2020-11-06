#include <stdio.h>
#include <stdlib.h>

void exit_message(const char *message)
{
	fprintf(stderr, message);
	exit(1);
}
