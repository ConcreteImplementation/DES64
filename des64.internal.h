#ifndef _DES64_INTERNAL_HEADER_
#define _DES64_INTERNAL_HEADER_

#include <stdio.h>
#include <stdint.h>

typedef struct {
	uint64_t right:48;
} block_t;

void _initial_permutation(uint64_t* source, size_t length);
void _final_permutation(uint64_t* source, size_t length);

uint64_t _expansion(uint64_t block);

#endif