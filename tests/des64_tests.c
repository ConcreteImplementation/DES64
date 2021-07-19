#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>


#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <stdlib.h>

#include "../binary_utility/binary_utility.h"

#include "../des64.h"
#include "des64_internals_tests.c"
#include "des64_keyschedule_tests.c"


void encrypt_decrypt(void** state){
	char* originalSource = "Hello world!!!!!";
	char* source = malloc( strlen(originalSource)+1 );
	strncpy( source, originalSource, strlen(originalSource)+1 );

	keyschedule_t* key = des64_new_keyschedule(999);

	des64_encrypt(source, 16, key);
	des64_decrypt(source, 16, key);
	
	assert_string_equal(originalSource, source);

	free(key);
	free(source);
}


int main(int argc, char** argv){
	
	const struct CMUnitTest internals[] = {
		cmocka_unit_test(initial_permutation),
		cmocka_unit_test(final_permutation),
		cmocka_unit_test(permutation_back_and_forth),
		cmocka_unit_test(expansion),
		cmocka_unit_test(find_substitution),
		cmocka_unit_test(substitution),
		cmocka_unit_test(primitive),
		cmocka_unit_test(cipher_function)
	};


	const struct CMUnitTest keyschedule[] = {
		cmocka_unit_test(keyschedule_permuted_choice_1),
		cmocka_unit_test(keyschedule_permuted_choice_2),
		cmocka_unit_test(keyschedule_permuted_choice_2_2),
		cmocka_unit_test(keyschedule_make_keyschedule)
	};


	const struct CMUnitTest des64[] = {
		cmocka_unit_test(encrypt_decrypt)
	};


	printf("DES64_NUMBER_OF_ROUNDS = %d\n", DES64_NUMBER_OF_ROUNDS);

	cmocka_run_group_tests(internals, NULL, NULL);
	printf("\n");
	cmocka_run_group_tests(keyschedule, NULL, NULL);
	printf("\n");
	cmocka_run_group_tests(des64, NULL, NULL);
	printf("\n");

	return 0;
}
