#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>


#include <stdio.h>
#include <string.h>
#include <assert.h>

#define DES64_NUMBER_OF_ROUNDS 1

#include "des64_internal.h"
#include "../binary_utility/binary_utility.h"





//						I N T E R N A L S

void initial_permutation(void** state){
	uint64_t source = 0xFFFFFFFF;

	_initial_permutation(&source, 1);

	char buffer [65] = "";
	char bufferpretty[81] = "";

	bin_itoa(source, buffer, sizeof(buffer));

	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_string_equal("1111 0000 1111 0000 1111 0000 1111 0000 1111 0000 1111 0000 1111 0000 1111 0000",
		bin_getptr_skipleadingzeros(bufferpretty));
}


void final_permutation(void** state){
	uint64_t source = 0xF0F0F0F0F0F0F0F0;

	_final_permutation(&source, 1);

	char buffer [65] = "";
	char bufferpretty[81] = "";

	bin_itoa(source, buffer, sizeof(buffer));

	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_string_equal("1111 1111 1111 1111 1111 1111 1111 1111",
		bin_getptr_skipleadingzeros(bufferpretty));
}

void permutation_back_and_forth(void** state){
	uint64_t sourceOriginal =  0xFFFFFFFF;
	uint64_t sourceWork = sourceOriginal;

	_initial_permutation(&sourceOriginal, 1);
	_final_permutation(&sourceOriginal, 1);

	assert_int_equal(sourceOriginal, sourceWork);
}





//						K E Y S C H E D U L E

void keyschedule_permuted_choice_1(void** state){
	uint64_t key =  0xFFFFFFFF;
	
	key_block_t keyBlock = _keyschedule_permuted_choice_1(key);


	char buffer [65] = "";
	char bufferpretty[81] = "";

	uint32_t blockD = keyBlock.blocks.D;
	bin_itoa(blockD, buffer, sizeof(buffer));
	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);
	assert_string_equal("1111 1111 0000 1111 0000 1111 0000",
		bin_getptr_skipleadingzeros(bufferpretty));
	
	uint32_t blockC = keyBlock.blocks.C;
	bin_itoa(blockC, buffer, sizeof(buffer));
	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);
	assert_string_equal("1111 0000 1111 0000 1111 0000",
		bin_getptr_skipleadingzeros(bufferpretty));

}






int main(int argc, char** argv){

	assert(DES64_NUMBER_OF_ROUNDS >=  1);
	assert(DES64_NUMBER_OF_ROUNDS <= 16);
	#if DES64_NUMBER_OF_ROUNDS != 16
	#warning DES64_NUMBER_OF_ROUNDS != 16
	#endif
	
	
	const struct CMUnitTest internals[] = {
		cmocka_unit_test(initial_permutation),
		cmocka_unit_test(final_permutation),
		cmocka_unit_test(permutation_back_and_forth)
	};


	const struct CMUnitTest keyscedule[] = {
		cmocka_unit_test(keyschedule_permuted_choice_1)
	};

	cmocka_run_group_tests(internals, NULL, NULL);
	printf("\n");
	cmocka_run_group_tests(keyscedule, NULL, NULL);
	printf("\n");
	return 0;
}
