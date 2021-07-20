#include <stdlib.h>

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


	uint64_t key = _keyschedule_permuted_choice_2(keyBlock);


	char buffer[99] = "";
	uint64_t keyScheduleBlock = key;
	
	assert_string_equal("1111 1111 1111 1111 1111 1111",
		bin_itoa_pretty( keyScheduleBlock, buffer, sizeof(buffer) )
	);
}

void keyschedule_permuted_choice_2_2(void** state){
	keyblock_t keyBlock;
	keyBlock.blocks.C = 0xFFFF;
	keyBlock.blocks.D = 0xFFFF;


	uint64_t key  = _keyschedule_permuted_choice_2(keyBlock);


	char buffer[99] = "";
	
	assert_string_equal("1110 1001 0101 0100 1100 1101 1100 1110 1100 1011 0111 0101",
		bin_itoa_pretty( key, buffer, sizeof(buffer) )
	);
}



void keyschedule_build_keyschedule(void** state){
	uint64_t key = 0xFFFFFFFF;

	keyschedule_t keySchedule = build_keyschedule(key);


	char buffer[99] = "";
	
	assert_string_equal("111 1011 1001 0011 0010 1010 0000 1110 0001 0011 0000 1011",
		bin_itoa_pretty( keySchedule.key[0], buffer, sizeof(buffer) )
	);
}

/*

D: 1111 1111 0000 1111 0000 1111 0000
C: 0000 1111 0000 1111 0000 1111 0000


LS
D: 1111 1110 0001 1110 0001 1110 0001
C: 0001 1110 0001 1110 0001 1110 0000

DC
1111 1110 0001 1110 0001 1110 0001    0001 1110 0001 1110 0001 1110 0000
        11111110000111100001111000010001111000011110000111100000
6666655555555554444444444333333333322222222221111111111000000000
4321098765432109876543210987654321098765432109876543210987654321

PC2
011110111001001100101010000011100001001100001011

*/