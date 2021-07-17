#include "../des64.internal.h"



void initial_permutation(void** state){
	uint64_t source = 0xFFFFFFFF;

	_initial_permutation(&source, 1);

	char buffer[99] = "";
	assert_string_equal(
		"1111 0000 1111 0000 1111 0000 1111 0000 1111 0000 1111 0000 1111 0000 1111 0000",
		bin_itoa_pretty( source, buffer, sizeof(buffer) )
	);
}


void final_permutation(void** state){
	uint64_t source = 0xF0F0F0F0F0F0F0F0;

	_final_permutation(&source, 1);

	char buffer[99] = "";
	assert_string_equal(
		"1111 1111 1111 1111 1111 1111 1111 1111",
		bin_itoa_pretty( source, buffer, sizeof(buffer) )
	);
}

void permutation_back_and_forth(void** state){
	uint64_t sourceOriginal =  0xFFFFFFFF;
	uint64_t sourceWork = sourceOriginal;

	_initial_permutation(&sourceOriginal, 1);
	_final_permutation(&sourceOriginal, 1);

	assert_int_equal(sourceOriginal, sourceWork);
}



void expansion(void** state){
	uint64_t source =  0xFFFF;

	uint64_t expanded = _expansion(source);

	char buffer[99] = "";
	assert_string_equal( "1000 0000 0000 0000 0000 0001 0111 1111 1111 1111 1111 1110",
		bin_itoa_pretty( expanded, buffer, sizeof(buffer) )
	);
}



void find_substitution(void** state){
	uint32_t source =  0;
	uint32_t destination = 0;

	source =  0x1B; //011011
	destination = _find_substitution(0, source);
	assert_int_equal(destination, 0x5);

	source =  0x35; //110101
	destination = _find_substitution(3, source);
	assert_int_equal(destination, 0x5);

	source =  0x28; //101000
	destination = _find_substitution(7, source);
	assert_int_equal(destination, 0x9);
}

void substitution(void** state){
	uint64_t source =  0x0F0F0F0F0F0F;
	// 000011 110000 111100 001111 000011 110000 111100 001111
	// 8 1 1  7 2 8  6 2 14 5 1 7  4 1 1  3 2 8  2 2 14 1 1 7
	// 15     10     11     1      8      11     2      1
	// 1111   1010   1011   0001   1000   1011   0010   0001
	uint32_t destination = _substitution(source);

	char buffer[99] = "";
	assert_string_equal( "1111 1010 1011 0001 1000 1011 0010 0001",
		bin_itoa_pretty( destination, buffer, sizeof(buffer) )
	);
}


void primitive(void** state){
	uint32_t source =  0xFFFF;

	_primitive(&source);

	char buffer[99] = "";
	assert_string_equal( "110 1010 1100 1011 1001 0011 0010 0011",
		bin_itoa_pretty( source, buffer, sizeof(buffer) )
	);
}
