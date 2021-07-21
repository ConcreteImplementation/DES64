#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../des64.h"



void print_mem(void* ptr, size_t size);
void dopad(void** plainText, size_t* textSize);
void unpad(void** plainText, size_t* textSize);



int main(int argc, char const *argv[])
{
	printf("\n\nSetting context...\n\n");

	char* originalSource = "Hello world!";
	size_t length = strlen(originalSource);

	char* source = malloc( length+1 );
	memcpy( source, originalSource, length+1 );

	des64_context* context = des64_new_context(999);

	printf("Original source: \n");
	print_mem(source, length);

	printf("Padded source: \n");
	dopad((void**) &source, &length);
	print_mem(source, length);

	printf("Enciphering...\n");
	des64_enciphering_computation(source, length, context);
	print_mem(source, length);

	printf("Deciphering...\n");
	des64_set_to_decipher(context);
	des64_enciphering_computation(source, length, context);
	print_mem(source, length);

	printf("Unpadded result: \n");
	unpad((void**) &source, &length);
	print_mem(source, length);

	printf("Cleaning...\n");
	free(context);
	free(source);

	printf("Done.\n\n");
	return 0;
}






void print_as_hex(void* ptr, size_t size) {
	while(size--) {
		printf("%02x ", * (unsigned char*)ptr);
		ptr++;
	}
}
void print_as_char(void* ptr, size_t size) {
	while(size--) {
		printf("%c", * (unsigned char*)ptr);
		ptr++;
	}
}
void print_mem(void* ptr, size_t size) {
	print_as_hex(ptr, size);
	printf("\n");
	print_as_char(ptr, size);
	printf("\n");
	printf("Length: %lu\n", size);

	printf("\n\n");
}



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