#ifndef _DES64_DEFINES_HEADER_
#define _DES64_DEFINES_HEADER_

#include <stdint.h>



#define PUBLIC

#ifdef TESTING
	#define PRIVATE
#else
	#define PRIVATE inline static
#endif



#define DES64_NUMBER_OF_ROUNDS 16
#define DES64_BLOCK_SIZE 8




const uint64_t BITMASKS[64];

#define DES64_IS_BIT_SET(source, table, index) \
	( source  &  BITMASKS[ table[index] ] )

#define DES64_DO_PERMUTATION(source, destination, table, tableSize) \
	for(int i = 0; i < tableSize; i++) \
		if( DES64_IS_BIT_SET(source, table, i) ) \
			destination |= BITMASKS[i]; 
			


const char INITIAL_PERMUTATION_TABLE[64];
const char FINAL_PERMUTATION_TABLE[64];
const char EXPANSION_TABLE[48];
const char SUBSTITUTION_BOXES_TABLE[8][64];
const char PRIMITIVE_TABLE[32];
const char PERMUTED_CHOICE_1_TABLE[56];
const char PERMUTED_CHOICE_2_TABLE[48];
const char KEYSCHEDULE_LEFT_SHIFT_TABLE[16];



#endif