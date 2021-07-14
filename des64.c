#include <stdio.h>
#include <stdint.h>


#include "des64_tables.h"
#include "des64_types.h"

#include "binary_utility/binary_utility.h"


#ifndef DES64_NUMBER_OF_ROUNDS
#define DES64_NUMBER_OF_ROUNDS 16
#endif




#define DES_ISSET(source, table, index)  ( source  &  MASKS[ table[index] -1 ] )



void _permutation(uint64_t* source, size_t length, const short* table) {
	while(length--) {
		uint64_t destination = 0;

		for(int i = 0; i < 64; i++)
			if( DES_ISSET(*source, table, i) )
				destination |= MASKS[i];
		
		*source = destination;
		source++;
	}
}

void _initial_permutation(uint64_t* source, size_t length) {
	_permutation(source, length, IP);
}

void _final_permutation(uint64_t* source, size_t length) {
	_permutation(source, length, FP);
}





key_block_t _keyschedule_permuted_choice_1(uint64_t key) {
	key_block_t keyBlock;
	keyBlock.block = 0;

	for(int i = 0; i < 56; i++)
		if( DES_ISSET(key, PC1, i) )
			keyBlock.block |= MASKS[i];

	keyBlock.blocks.D = keyBlock.block >> 28;
	keyBlock.blocks.C = keyBlock.block & 0xFFFFFFF;

	return keyBlock;
}

// key_schedule_t* _make_key_scedule(uint64_t key) {
// 	key_schedule_t* keySchedule[DES64_NUMBER_OF_ROUNDS];

// 	key_blocks_t keyBlock = _key_permuted_choice_1(key);
	
// 	return keySchedule;


// }


void des_encrypt(uint64_t* plainText, size_t textSize, uint64_t key) {

	

}