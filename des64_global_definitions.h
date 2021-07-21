#ifndef _DES64_DEFINES_HEADER_
#define _DES64_DEFINES_HEADER_

#include <stdint.h>



#define PUBLIC

#ifdef TESTING
	#define PRIVATE
#else
	#define PRIVATE static
#endif



#define DES64_NUMBER_OF_ROUNDS 16
#define DES64_BLOCK_SIZE 8




const uint64_t BITMASKS[64];

#define DES64_IS_BIT_SET(source, table, index) \
	( source  &  BITMASKS[ table[index] -1 ] )

#define DES64_DO_PERMUTATION(source, destination, table, tableSize) \
	for(int i = 0; i < tableSize; i++) \
		if( DES64_IS_BIT_SET(source, table, i) ) \
			destination |= BITMASKS[i]; 
			


const short INITIAL_PERMUTATION_TABLE[64];
const short FINAL_PERMUTATION_TABLE[64];
const short EXPANSION_TABLE[48];
const short SUBSTITUTION_BOXES_TABLE[8][4][16];
const short PRIMITIVE_TABLE[32];
const short PERMUTED_CHOICE_1_TABLE[56];
const short PERMUTED_CHOICE_2_TABLE[48];
const short KEYSCHEDULE_LEFT_SHIFT_TABLE[16];



#endif