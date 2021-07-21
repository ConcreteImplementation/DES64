#ifndef _DES64_HEADER_
#define _DES64_HEADER_



#include <stdio.h>
#include <stdint.h>


typedef struct des64_context des64_context;

des64_context* des64_new_context(uint64_t key);
void des64_set_to_encipher(des64_context* context);
void des64_set_to_decipher(des64_context* context);
int des64_enciphering_computation(void* plainText, size_t textSize, des64_context* context);



#endif