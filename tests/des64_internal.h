#ifndef _DES64_INTERNAL_HEADER_
#define _DES64_INTERNAL_HEADER_

#include <stdint.h>

//#include "des64_tables.h"
//#include "../des64_types.h"
#include "../des64_keyschedule_types.h"

uint64_t _initial_permutation(uint64_t* source, size_t length);
uint64_t _final_permutation(uint64_t* source, size_t length);

key_block_t _keyschedule_permuted_choice_1(uint64_t key);

#endif