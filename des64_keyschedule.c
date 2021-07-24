#include <stdlib.h>

#include "des64_keyschedule.internal.h"



#define ROTATE_LEFT_28_BITS(n, shift)  ( n =  n<<shift  |  n>>(28-shift) )

#define KEY_BLOCKS_LEFT_SHIFT(keyBlock, shift)         \
	ROTATE_LEFT_28_BITS(keyBlock.C, KEYSCHEDULE_LEFT_SHIFT_TABLE[shift]);  \
	ROTATE_LEFT_28_BITS(keyBlock.D, KEYSCHEDULE_LEFT_SHIFT_TABLE[shift]);






PUBLIC
keyschedule_t build_keyschedule(uint64_t key) {
	keyschedule_t keyschedule;

	keyblock_t keyBlock = _permuted_choice_1(key);

	for (int i = 0; i < DES64_NUMBER_OF_ROUNDS; i++) {
		KEY_BLOCKS_LEFT_SHIFT(keyBlock, i);
		keyschedule.key[i] = _permuted_choice_2(keyBlock);
	}
	
	return keyschedule;
}

PUBLIC
keyschedule_t invert_keyschedule(keyschedule_t keyschedule) {
	keyschedule_t invertedKeyschedule;

	for(int i = 0; i < DES64_NUMBER_OF_ROUNDS ; i++)
		invertedKeyschedule.key[DES64_NUMBER_OF_ROUNDS - 1 - i] = keyschedule.key[i];

	return invertedKeyschedule;
}






PRIVATE
keyblock_t _permuted_choice_1(uint64_t key) {
	uint64_t block = 0;

	DES64_DO_PERMUTATION(key, block, PERMUTED_CHOICE_1_TABLE, 56);

	keyblock_t keyBlock = {0};
	keyBlock.C = block >> 28;
	keyBlock.D = block & 0xFFFFFFF;

	return keyBlock;
}

PRIVATE
uint64_t _permuted_choice_2(keyblock_t keyBlock) {
	uint64_t key = 0;

	uint64_t block = (uint64_t)keyBlock.C << 28 | keyBlock.D;
	
	DES64_DO_PERMUTATION(block, key, PERMUTED_CHOICE_2_TABLE, 48);

	return key;
}






#undef ROTATE_LEFT_28_BITS
#undef KEY_BLOCKS_LEFT_SHIFT