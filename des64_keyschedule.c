#include "des64_defines.h"

#include "des64_keyschedule_tables.h"
#include "des64_keyschedule_types.h"

#include "binary_utility/binary_utility.h"


#define LEFT_SHIFT (keyBlock, shift) \
	keyblock.blocks.C << LS[shift];  \
	keyblock.blocks.D << LS[shift];



key_block_t _keyschedule_permuted_choice_1(uint64_t key) {
	key_block_t keyBlock;
	keyBlock.block = 0;

	for(int i = 0; i < 56; i++)
		if( DES64_IS_BIT_SET(key, PC1, i) )
			keyBlock.block |= MASKS[i];

	keyBlock.blocks.D = keyBlock.block >> 28;

	return keyBlock;
}



key_schedule_t* _make_key_scedule(uint64_t key) {

	key_block_t keyBlock = _keyschedule_permuted_choice_1(key);

	key_schedule_t* keySchedule[DES64_NUMBER_OF_ROUNDS];
	


	return keySchedule;
}
