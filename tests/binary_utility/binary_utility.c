#include <stdio.h>
#include <stdint.h>
#include <string.h>


#include "binary_utility.h"



ERRBIN_T bin_itoa_typesize(uint64_t n, long typesize, char* buf, long bufsize) {
	int binsize = typesize * 8;
	if( bufsize-1 < binsize )
		return ERRBIN_BUFFER_TOO_SMALL;

	memset(buf, '0', bufsize);

	buf += bufsize - 1;
	*buf = '\0';

	while ( n && binsize ) {
		buf--;
		*buf = (n & 1) + '0';
	
		n >>= 1;
		binsize--;
	}

	return ERRBIN_SUCCESS;
}




char* bin_getptr_skipleadingzeros(char* buf) {
	char* ptr = buf;
	while( *ptr == '0' || *ptr == ' ')
		ptr++;
	return ptr;
}




ERRBIN_T bin_string_prettyspace(char* bufin, char* bufout, long bufoutsize, int space) {
	long len = strlen(bufin);

	long finalsize = len / space + len +1; 

	if(bufoutsize < finalsize)
		return ERRBIN_BUFFER_TOO_SMALL;

	int rem = len % space;
	rem = rem == 0 ? space : rem;
	
	while(rem--)
		*(bufout++) = *(bufin++);

	for (int i = 0; *bufin != '\0'; i++) {
		if( i % space == 0 )
			*(bufout++) = ' ';
		*(bufout++) = *(bufin++);
	}

	*(bufout++) = '\0';
	return ERRBIN_SUCCESS;
}



char* bin_itobin_pretty(uint64_t number, char* buffer, long bufferSize) {
	char bufferTemp[80];

	ERRBIN_T err = bin_itoa_typesize(number, sizeof(number), bufferTemp, sizeof(bufferTemp));
	if(err) {
		fprintf(stderr, "error: bin_itoa_typesize() %d\n", err);
		return NULL;
	}

	err = bin_string_prettyspace(bufferTemp, buffer, bufferSize, 4);
	if(err) {
		fprintf(stderr, "error: bin_string_prettyspace() %d\n", err);
		return NULL;
	}

	return bin_getptr_skipleadingzeros(buffer);
}