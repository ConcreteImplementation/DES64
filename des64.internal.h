#ifndef _DES64_INTERNAL_HEADER_
#define _DES64_INTERNAL_HEADER_

#include <stdio.h>
#include <stdint.h>

uint64_t _initial_permutation(uint64_t* source, size_t length);
uint64_t _final_permutation(uint64_t* source, size_t length);



#endif