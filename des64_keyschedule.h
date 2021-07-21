#ifndef _KEYSCHEDULE_HEADER_
#define _KEYSCHEDULE_HEADER_



#include <stdint.h>

#include "des64_global_definitions.h"



typedef struct keyschedule_t {
	uint64_t key[DES64_NUMBER_OF_ROUNDS];
} keyschedule_t;


keyschedule_t build_keyschedule(uint64_t key);
keyschedule_t invert_keyschedule(keyschedule_t keyschedule);



#endif