#include "../des64_keyschedule.internal.h"


void keyschedule_permuted_choice_1(void** state){
	uint64_t key =  0xFFFFFFFF;
	

	keyblock_t keyBlock = _keyschedule_permuted_choice_1(key);


	char buffer[99] = "";

	uint32_t blockD = keyBlock.blocks.D;
	assert_string_equal("1111 1111 0000 1111 0000 1111 0000",
		bin_itoa_pretty( blockD, buffer, sizeof(buffer) )
	);
	
	uint32_t blockC = keyBlock.blocks.C;
	assert_string_equal("1111 0000 1111 0000 1111 0000",
		bin_itoa_pretty( blockC, buffer, sizeof(buffer) )
	);
}