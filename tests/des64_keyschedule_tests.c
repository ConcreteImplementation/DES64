#include "../des64_keyschedule.internal.h"



void permuted_choice_1(void** state){
	uint64_t key =  0xFFFFFFFF;
	

	keyblock_t keyBlock = _permuted_choice_1(key);


	char buffer[99] = "";
	
	uint32_t blockC = keyBlock.C;
	assert_string_equal("1111 1111 0000 1111 0000 1111 0000",
		bin_itobin_pretty( blockC, buffer, sizeof(buffer) )
	);

	uint32_t blockD = keyBlock.D;
	assert_string_equal("1111 0000 1111 0000 1111 0000",
		bin_itobin_pretty( blockD, buffer, sizeof(buffer) )
	);
}



void permuted_choice_2_A(void** state){
	keyblock_t keyBlock;
	keyBlock.C = 0x0;
	keyBlock.D = 0xFFFFFFF;


	uint64_t key = _permuted_choice_2(keyBlock);


	char buffer[99] = "";
	uint64_t keyScheduleBlock = key;
	
	assert_string_equal("1111 1111 1111 1111 1111 1111",
		bin_itobin_pretty( keyScheduleBlock, buffer, sizeof(buffer) )
	);
}



void permuted_choice_2_B(void** state){
	keyblock_t keyBlock;
	keyBlock.C = 0xFFFF;
	keyBlock.D = 0xFFFF;


	uint64_t key  = _permuted_choice_2(keyBlock);


	char buffer[99] = "";
	
	assert_string_equal("1110 1001 0101 0100 1100 1101 1100 1110 1100 1011 0111 0101",
		bin_itobin_pretty( key, buffer, sizeof(buffer) )
	);
}



void build(void** state){
	uint64_t key = 0xFFFFFFFF;

	keyschedule_t keySchedule = build_keyschedule(key);


	char buffer[99] = "";
	
	assert_string_equal("111 1011 1001 0011 0010 1010 0000 1110 0001 0011 0000 1011",
		bin_itobin_pretty( keySchedule.key[0], buffer, sizeof(buffer) )
	);
}

/*

C: 1111 1111 0000 1111 0000 1111 0000
D: 0000 1111 0000 1111 0000 1111 0000


LS
C: 1111 1110 0001 1110 0001 1110 0001
D: 0001 1110 0001 1110 0001 1110 0000

CD
1111 1110 0001 1110 0001 1110 0001    0001 1110 0001 1110 0001 1110 0000
        11111110000111100001111000010001111000011110000111100000
6666655555555554444444444333333333322222222221111111111000000000
4321098765432109876543210987654321098765432109876543210987654321

PC2
011110111001001100101010000011100001001100001011

*/