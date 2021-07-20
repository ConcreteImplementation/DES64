#ifndef _KEYSCHEDULE_INTERNAL_
#define _KEYSCHEDULE_INTERNAL_

#include "des64_keyschedule.h"



typedef	union {
	uint64_t block:56;

	struct {
		uint32_t C:28;
		uint32_t D:28;
	} blocks;
	
} keyblock_t;


PRIVATE
keyblock_t _keyschedule_permuted_choice_1(uint64_t key) ;

PRIVATE
uint64_t _keyschedule_permuted_choice_2(keyblock_t keyBlock) ;



#endif