#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>


#include <stdio.h>
#include <string.h>


#include "des64_internal.h"
#include "../binary_utility/binary_utility.h"

void initial_permutation(void** state){
	uint64_t source = 0xFFFFFFFF;

	uint64_t destination = _initial_permutation(source);

	char buffer [65] = "";
	char bufferpretty[81] = "";

	bin_itoa(destination, buffer, sizeof(buffer));

	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_string_equal("1111 0000 1111 0000 1111 0000 1111 0000 1111 0000 1111 0000 1111 0000 1111 0000",
		bin_getptr_skipleadingzeros(bufferpretty));
}


void final_permutation(void** state){
	uint64_t source = 0xF0F0F0F0F0F0F0F0;

	uint64_t destination = _final_permutation(source);

	char buffer [65] = "";
	char bufferpretty[81] = "";

	bin_itoa(destination, buffer, sizeof(buffer));

	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_string_equal("1111 1111 1111 1111 1111 1111 1111 1111",
		bin_getptr_skipleadingzeros(bufferpretty));
}



void permutation_back_and_forth(void** state){
	uint64_t source = 0xFFFFFFFF;

	uint64_t destination1 = _initial_permutation(source);
	uint64_t destination2 = _final_permutation(destination1);

	assert_int_equal(source, destination2);
}


int main(int argc, char** argv){
	const struct CMUnitTest tests_des64_internals[] = {
		cmocka_unit_test(initial_permutation),
		cmocka_unit_test(final_permutation),
		cmocka_unit_test(permutation_back_and_forth)
	};


	cmocka_run_group_tests(tests_des64_internals, NULL, NULL);
	printf("\n");

	return 0;
}
