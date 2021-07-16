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


void keyschedule_permuted_choice_2(void** state){
	keyblock_t keyBlock;
	keyBlock.blocks.C = 0xFFFFFFF;
	keyBlock.blocks.D = 0x0;


	keyschedule_t keySchedule = _keyschedule_permuted_choice_2(keyBlock);


	char buffer[99] = "";
	uint64_t keyScheduleBlock = keySchedule.key;
	
	assert_string_equal("1111 1111 1111 1111 1111 1111",
		bin_itoa_pretty( keyScheduleBlock, buffer, sizeof(buffer) )
	);
}

void keyschedule_permuted_choice_2_2(void** state){
	keyblock_t keyBlock;
	keyBlock.blocks.C = 0xFFFF;
	keyBlock.blocks.D = 0xFFFF;


	keyschedule_t keySchedule = _keyschedule_permuted_choice_2(keyBlock);


	char buffer[99] = "";
	uint64_t keyScheduleBlock = keySchedule.key;
	
	assert_string_equal("1110 1001 0101 0100 1100 1101 1100 1110 1100 1011 0111 0101",
		bin_itoa_pretty( keyScheduleBlock, buffer, sizeof(buffer) )
	);
}
