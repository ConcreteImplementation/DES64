#ifndef _DES64_HEADER_
#define _DES64_HEADER_


#include <stdio.h>
#include <stdint.h>

void des_encrypt(uint64_t* plainText, size_t textSize, uint64_t key);


#endif