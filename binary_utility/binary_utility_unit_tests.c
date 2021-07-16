#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>


#include <stdio.h>
#include <string.h>


#include "binary_utility.h"


void test_bin_sizeof_macro(void** state){
	char c;
	assert_int_equal(8, bin_sizeof(char));
	assert_int_equal(8, bin_sizeof(c));

	uint16_t interger16;
	assert_int_equal(16, bin_sizeof(int16_t));
	assert_int_equal(16, bin_sizeof(uint16_t));
	assert_int_equal(16, bin_sizeof(interger16));

	uint32_t interger32;
	assert_int_equal(32, bin_sizeof(int32_t));
	assert_int_equal(32, bin_sizeof(uint32_t));
	assert_int_equal(32, bin_sizeof(interger32));

	uint64_t interger64;
	assert_int_equal(64, bin_sizeof(int64_t));
	assert_int_equal(64, bin_sizeof(uint64_t));
	assert_int_equal(64, bin_sizeof(interger64));
}


void test_bin_rotr_macro(void** state){
	unsigned int n = 0xA000;
	char buffer [65] = "";
	char bufferpretty[81] = "";

	bin_itoa(n, buffer, sizeof(buffer));
	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_string_equal("1010 0000 0000 0000",
		bin_getptr_skipleadingzeros(bufferpretty));


	n = rotr(n, 1);

	bin_itoa(n, buffer, sizeof(buffer));
	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_string_equal("101 0000 0000 0000",
		bin_getptr_skipleadingzeros(bufferpretty));

	n = rotr(n, 4);

	bin_itoa(n, buffer, sizeof(buffer));
	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_string_equal("101 0000 0000",
		bin_getptr_skipleadingzeros(bufferpretty));


	n = rotr(n, 8);

	bin_itoa(n, buffer, sizeof(buffer));
	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_string_equal("101",
		bin_getptr_skipleadingzeros(bufferpretty));



	n = rotr(n, 3);

	bin_itoa(n, buffer, sizeof(buffer));
	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_string_equal("1010 0000 0000 0000 0000 0000 0000 0000",
		bin_getptr_skipleadingzeros(bufferpretty));
}



void test_bin_rotl_macro(void** state){
	unsigned int n = 0xA000;
	char buffer [65] = "";
	char bufferpretty[81] = "";

	bin_itoa(n, buffer, sizeof(buffer));
	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_string_equal("1010 0000 0000 0000",
		bin_getptr_skipleadingzeros(bufferpretty));


	n = rotl(n, 1);

	bin_itoa(n, buffer, sizeof(buffer));
	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_string_equal("1 0100 0000 0000 0000",
		bin_getptr_skipleadingzeros(bufferpretty));

	n = rotl(n, 4);

	bin_itoa(n, buffer, sizeof(buffer));
	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_string_equal("1 0100 0000 0000 0000 0000",
		bin_getptr_skipleadingzeros(bufferpretty));


	n = rotl(n, 8);

	bin_itoa(n, buffer, sizeof(buffer));
	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_string_equal("1 0100 0000 0000 0000 0000 0000 0000",
		bin_getptr_skipleadingzeros(bufferpretty));


	n = rotl(n, 3);

	bin_itoa(n, buffer, sizeof(buffer));
	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_string_equal("1010 0000 0000 0000 0000 0000 0000 0000",
		bin_getptr_skipleadingzeros(bufferpretty));

	
	n = rotl(n, 3);

	bin_itoa(n, buffer, sizeof(buffer));
	bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_string_equal("101",
		bin_getptr_skipleadingzeros(bufferpretty));
}







void test_bin_itoa(void** state){
	char buffer[65] = "";

	int i = 5;
	ERRBIN_T ret = ERRBIN_SUCCESS;


	ret = bin_itoa(i, buffer, sizeof(buffer));
	assert_int_equal(ret , ERRBIN_SUCCESS);
	assert_string_equal("101", bin_getptr_skipleadingzeros(buffer));

	ret = bin_itoa(MASK64<<63, buffer, sizeof(buffer));
	assert_int_equal(ret , ERRBIN_SUCCESS);
	assert_string_equal("1000000000000000000000000000000000000000000000000000000000000000",
		bin_getptr_skipleadingzeros(buffer));

	i = 10;
	ret = bin_itoa(i, buffer, sizeof(buffer));
	assert_int_equal(ret , ERRBIN_SUCCESS);
	assert_string_equal("1010", bin_getptr_skipleadingzeros(buffer));

	i = 715827882;
	ret = bin_itoa(i, buffer, sizeof(buffer));
	assert_int_equal(ret , ERRBIN_SUCCESS);
	assert_string_equal("101010101010101010101010101010", bin_getptr_skipleadingzeros(buffer));

	i = 2863311530;
	ret = bin_itoa(i, buffer, sizeof(buffer));
	assert_int_equal(ret , ERRBIN_SUCCESS);
	assert_string_equal("10101010101010101010101010101010", bin_getptr_skipleadingzeros(buffer));
}




void test_bin_itoa_error(void** state){
	char buffer[64] = "";

	ERRBIN_T ret = bin_itoa(MASK64<<63, buffer, sizeof(buffer));

	assert_int_equal(ret , ERRBIN_BUFFER_TOO_SMALL);
}




void test_string_printpretty(void** state){
	char buffer[65] = "";
	char bufferpretty[81] = "";
	int i = 0x2AAAAAAA;
	bin_itoa(i, buffer, sizeof(buffer));

	ERRBIN_T ret = bin_string_prettyspace(bin_getptr_skipleadingzeros(buffer), bufferpretty, sizeof(bufferpretty), 4);
	
	assert_int_equal(ret , ERRBIN_SUCCESS);
	assert_string_equal("10 1010 1010 1010 1010 1010 1010 1010", bufferpretty);
}



void test_string_printpretty_error(void** state){
	char buffer[65] = "";
	char bufferpretty[80] = "";
	int i = 0x2AAAAAAA;
	bin_itoa(i, buffer, sizeof(buffer));
	
	ERRBIN_T ret = bin_string_prettyspace(buffer, bufferpretty, sizeof(bufferpretty), 4);

	assert_int_equal(ret , ERRBIN_BUFFER_TOO_SMALL);
}




void test_bin_itoa_pretty(void** state){
	char buffer[255] = "";
	int i = 0x2AAAAAAA;
	
	assert_string_equal("10 1010 1010 1010 1010 1010 1010 1010", 
		bin_itoa_pretty( i, buffer, sizeof(buffer) )
	);
}


int main(int argc, char** argv){
	const struct CMUnitTest tests_macros[] = {
		cmocka_unit_test(test_bin_sizeof_macro),
		cmocka_unit_test(test_bin_rotr_macro),
		cmocka_unit_test(test_bin_rotl_macro)
	};

	const struct CMUnitTest tests_convertions[] = {
		cmocka_unit_test(test_bin_itoa),
		cmocka_unit_test(test_bin_itoa_error),
		cmocka_unit_test(test_string_printpretty),
		cmocka_unit_test(test_string_printpretty_error),
		cmocka_unit_test(test_bin_itoa_pretty)
	};





	cmocka_run_group_tests(tests_macros, NULL, NULL);
	printf("\n");
	cmocka_run_group_tests(tests_convertions, NULL, NULL);


	return 0;
}
