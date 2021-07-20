#include <stdlib.h>

#include "des64_keyschedule.internal.h"
#include "des64_keyschedule.tables.h"

#define ROTATE_LEFT_28_BITS(n, shift)  ( n =  n<<shift  |  n>>(28-shift) )

#define KEYSCHEDULE_LEFT_SHIFT(keyBlock, shift)         \
	ROTATE_LEFT_28_BITS(keyBlock.blocks.C, LS[shift]);  \
	ROTATE_LEFT_28_BITS(keyBlock.blocks.D, LS[shift]);




PRIVATE
keyblock_t _keyschedule_permuted_choice_1(uint64_t key) {
	keyblock_t keyBlock;
	keyBlock.block = 0;

	DES64_DO_PERMUTATION(key, keyBlock.block, PC1, 56);

	keyBlock.blocks.D = keyBlock.block >> 28;

	return keyBlock;
}

PRIVATE
uint64_t _keyschedule_permuted_choice_2(keyblock_t keyBlock) {
	uint64_t key = 0;

	uint64_t block = (uint64_t)keyBlock.blocks.D << 28 | keyBlock.blocks.C;
	
	DES64_DO_PERMUTATION(block, key, PC2, 48);

	return key;
}




PUBLIC
keyschedule_t invert_keyschedule(keyschedule_t keyschedule) {
	keyschedule_t invertedKeyschedule;

	for(int i = 0; i < DES64_NUMBER_OF_ROUNDS ; i++)
		invertedKeyschedule.key[DES64_NUMBER_OF_ROUNDS - 1 - i] = keyschedule.key[i];

	return invertedKeyschedule;
}


PUBLIC
keyschedule_t build_keyschedule(uint64_t key) {
	keyschedule_t keyschedule;

	keyblock_t keyBlock = _keyschedule_permuted_choice_1(key);

	for (int i = 0; i < DES64_NUMBER_OF_ROUNDS; i++) {
		KEYSCHEDULE_LEFT_SHIFT(keyBlock, i);
		keyschedule.key[i] = _keyschedule_permuted_choice_2(keyBlock);
	}
	
	return keyschedule;
}



#undef ROTATE_LEFT_28_BITS
#undef KEYSCHEDULE_LEFT_SHIFT