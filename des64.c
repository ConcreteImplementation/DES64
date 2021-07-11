#include <stdint.h>

#include "des64_tables.h"
#include "binary_utility/binary_utility.h"


#ifndef DES64_NUMBER_OF_ROUNDS
#define DES64_NUMBER_OF_ROUNDS 16
#endif


#define DES_ISSET(source, table, index)  ( source  &  MASKS[ table[index] -1 ] )



uint64_t _permutation(uint64_t source, const short* table) {
	uint64_t destination = 0;

	for(int i = 0; i < 64; i++)
		if( DES_ISSET(source, table, i) )
			destination |= MASKS[i];

	return destination;
}

uint64_t _initial_permutation(uint64_t source) {
	return _permutation(source, IP);
}

uint64_t _final_permutation(uint64_t source) {
	return _permutation(source, FP);
}