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
