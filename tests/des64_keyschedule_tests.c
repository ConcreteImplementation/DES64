#include "../des64_keyschedule.internal.h"



void permuted_choice_1(void** state){
	uint64_t key =  0xFFFFFFFF;
	

	keyblock_t keyBlock = _permuted_choice_1(key);


	char buffer[99] = "";
	
	uint32_t blockC = keyBlock.C;
	assert_string_equal("1111 0000 1111 0000 1111 0000 1111",
		bin_itobin_pretty( blockC, buffer, sizeof(buffer) )
	);

	uint32_t blockD = keyBlock.D;
	assert_string_equal("1111 0000 1111 0000 1111 0000 0000",
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
	keyBlock.C = 0x3FFF;
	keyBlock.D = 0x3FFF;


	uint64_t key  = _permuted_choice_2(keyBlock);


	char buffer[99] = "";
	
	assert_string_equal("101 0001 1010 1100 1010 1100 0100 1100 1101 1101 0110 1000",
		bin_itobin_pretty( key, buffer, sizeof(buffer) )
	);
}
/*
00000000000000 11111111111111 00000000000000 11111111111111
00000000011111 11111222222222 23333333333444 44444445555555
12345678901234 56789012345678 90123456789012 34567890123456

0101 0001 1010 1100 1010 1100 0100 1100 1101 1101 0110 1000

*/

void build(void** state){
	uint64_t key = 0xFFFFFFFF;

	keyschedule_t keySchedule = build_keyschedule(key);


	char buffer[99] = "";
	
	assert_string_equal("111 1011 0001 0100 1110 1001 0011 1010 0100 1011 0010 0110",
		bin_itobin_pretty( keySchedule.key[0], buffer, sizeof(buffer) )
	);
}

/*

C: 1111 0000 1111 0000 1111 0000 1111
D: 1111 0000 1111 0000 1111 0000 0000


LS
C: 1110 0001 1110 0001 1110 0001 1111
D: 1110 0001 1110 0001 1110 0000 0001

CD
11100001111000 01111000011111 11100001111000 01111000000001
00000000011111 11111222222222 23333333333444 44444445555555
12345678901234 56789012345678 90123456789012 34567890123456

PC2
011110110001010011101001001110100100101100100110

expected
111 1011 0001 0100 1110 1001 0011 1010 0100 1011 0010 0110

*/