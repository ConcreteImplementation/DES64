#ifndef _DES64_INTERNAL_HEADER_
#define _DES64_INTERNAL_HEADER_

#include <stdint.h>


uint64_t _initial_permutation(uint64_t source);
uint64_t _final_permutation(uint64_t source);


#endif