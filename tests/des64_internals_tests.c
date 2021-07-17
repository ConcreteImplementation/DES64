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

void permutation32bits(void** state){
	uint32_t source =  0xFFFF;

	_permutation32bits(&source);

	char buffer[99] = "";
	assert_string_equal( "110 1010 1100 1011 1001 0011 0010 0011",
		bin_itoa_pretty( source, buffer, sizeof(buffer) )
	);
}
