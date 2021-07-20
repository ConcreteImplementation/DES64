
#include <stdio.h>
#include <stdlib.h>


void dopad(void** plainText, size_t* textSize) {
	if(*textSize % 8 == 0)
		return;

	int pad = 8 - *textSize % 8;
	*textSize += pad;

	*plainText = realloc(*plainText, *textSize);

	char* ptr = *plainText + *textSize -1;

	*ptr-- = pad--;
	while( pad-- ) 
		*ptr-- = 0;
}

void unpad(void** plainText, size_t* textSize) {
	char* ptr = *plainText + *textSize - 1;
	int pad = *ptr;

	if(pad < 1 || pad > 8)
		return;

	for(int i = 1; i < pad; i++ )
		if( *(ptr-i) != 0 )
			return;
	
	*textSize -= pad;
}

