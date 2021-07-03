#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "binary_utils/libbin.h"



int main(int argc, char const *argv[])
{
	char buffer[255];
	char bufferout[1000];

	ERRBIN_T err =  bin_itoa(MASKS[63], buffer, sizeof(buffer));
	if(err) {
		printf("ERREUR");
		return -1;
	}

	bin_string_prettyspace(buffer, bufferout, sizeof(bufferout), 4);
	printf("%s\n", bin_getptr_skipleadingzeros(bufferout));

	return 0;
}

