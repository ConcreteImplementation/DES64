#ifndef _DES64_HEADER_
#define _DES64_HEADER_


#include <stdio.h>
#include "des64_keyschedule.h"

void des64_encrypt(void* plainText, size_t textSize, keyschedule_t* keyschedule);
void des64_decrypt(void* plainText, size_t textSize, keyschedule_t* keyschedule);

#endif