#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>


#include <stdio.h>
#include <string.h>
#include <assert.h>


#include "../binary_utility/binary_utility.h"


#include "des64_internals_tests.c"
#include "des64_keyschedule_tests.c"



int main(int argc, char** argv){
	
	const struct CMUnitTest internals[] = {
		cmocka_unit_test(initial_permutation),
		cmocka_unit_test(final_permutation),
		cmocka_unit_test(permutation_back_and_forth)
	};


	const struct CMUnitTest keyschedule[] = {
		cmocka_unit_test(keyschedule_permuted_choice_1),
		cmocka_unit_test(keyschedule_permuted_choice_2),
		cmocka_unit_test(keyschedule_permuted_choice_2_2)
	};


	cmocka_run_group_tests(internals, NULL, NULL);
	printf("\n");
	cmocka_run_group_tests(keyschedule, NULL, NULL);
	printf("\n");
	return 0;
}
