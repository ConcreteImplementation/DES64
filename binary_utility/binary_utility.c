#include <stdint.h>
#include <string.h>


#include <stdio.h> //	to take out ?

#include "binary_utility.h"


// Precomputed bitmasks
const uint64_t MASKS[64] = { 
	0x1,                0x2,                0x4,                0x8,
	0x10,               0x20,               0x40,               0x80,
	0x100,              0x200,              0x400,              0x800,
	0x1000,             0x2000,             0x4000,             0x8000,
	0x10000,            0x20000,            0x40000,            0x80000,
	0x100000,           0x200000,           0x400000,           0x800000, 
	0x1000000,          0x2000000,          0x4000000,          0x8000000, 
	0x10000000,         0x20000000,         0x40000000,         0x80000000, 
	0x100000000,        0x200000000,        0x400000000,        0x800000000, 
	0x1000000000,       0x2000000000,       0x4000000000,       0x8000000000, 
	0x10000000000,      0x20000000000,      0x40000000000,      0x80000000000,
	0x100000000000,     0x200000000000,     0x400000000000,     0x800000000000,
	0x1000000000000,    0x2000000000000,    0x4000000000000,    0x8000000000000,
	0x10000000000000,   0x20000000000000,   0x40000000000000,   0x80000000000000,
	0x100000000000000,  0x200000000000000,  0x400000000000000,  0x800000000000000,
	0x1000000000000000, 0x2000000000000000, 0x4000000000000000, 0x8000000000000000
};



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