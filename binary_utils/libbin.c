#include <stdint.h>
#include <string.h>


#include <stdio.h> //	to take out ?

#include "libbin.h"


ERRBIN_T bin_itoa_typesize(uint64_t n, long typesize, char* buf, long bufsize){
	
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




char* bin_getptr_skipleadingzeros(char* buf)
{
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



// return error code
int bin2dec(char* ptr, void* ret, long typesize)
{

}