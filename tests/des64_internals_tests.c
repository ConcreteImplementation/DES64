#include "../des64.internal.h"



void initial_permutation(void** state){
	uint64_t source = 0xFFFFFFFF;

	_initial_permutation(&source, 1);

	char buffer[99] = "";
	assert_string_equal(
		"1111 0000 1111 0000 1111 0000 1111 0000 1111 0000 1111 0000 1111 0000 1111 0000",
		bin_itobin_pretty( source, buffer, sizeof(buffer) )
	);
}



void final_permutation(void** state){
	uint64_t source = 0xF0F0F0F0F0F0F0F0;

	_final_permutation(&source, 1);

	char buffer[99] = "";
	assert_string_equal(
		"1111 1111 1111 1111 1111 1111 1111 1111",
		bin_itobin_pretty( source, buffer, sizeof(buffer) )
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
	uint64_t source = 0xFFFF;

	uint64_t expanded = _expansion(source);

	char buffer[99] = "";
	assert_string_equal( "1000 0000 0000 0000 0000 0001 0111 1111 1111 1111 1111 1110",
		bin_itobin_pretty( expanded, buffer, sizeof(buffer) )
	);
}



void find_substitution(void** state){
	uint32_t source = 0;
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
	uint64_t source = 0x0F0F0F0F0F0F;
	// 000011   110000   111100    001111   000011   110000   111100    001111
	// 1[1][1]  2[2][8]  3[2][14]  4[1][7]  5[1][1]  6[2][8]  7[2][14]  8[1][7]
	// 15       5        14        3        11       7        9         4
	// 1111     0101     1110      0011     1011     0111     1001      0100
	uint32_t destination = _substitution(source);

	char buffer[99] = "";
	assert_string_equal( "1111 0101 1110 0011 1011 0111 1001 0100",
		bin_itobin_pretty( destination, buffer, sizeof(buffer) )
	);
}



void primitive(void** state){
	uint32_t source = 0xFFFF;

	_primitive(&source);

	char buffer[99] = "";
	assert_string_equal( "110 1010 1100 1011 1001 0011 0010 0011",
		bin_itobin_pretty( source, buffer, sizeof(buffer) )
	);
}

void cipher_function(void** state) {
	uint64_t source = 0xA;
	uint64_t key = 0x1;

	_cipher_function(&source, 1, key);

	char buffer[99] = "";
	assert_string_equal( "1011 0101 0111 1111 0111 1000 1110 0010 0000 0000 0000 0000 0000 0000 0000 1010",
		bin_itobin_pretty( source, buffer, sizeof(buffer) )
	);
}
/*
source
1010

expansion
101 0100

XOR with key 0x1
101 0101

substitution
000000   000000   000000   000000   000000   000000   000001   010101
1[0][0]  2[0][0]  3[0][0]  4[0][0]  5[0][0]  6[0][0]  7[1][0]  8[1][10]
14       15       10       7        2        12       13       6
1110     1111     1010     0111    0010      1100     1101     0110

primitive
11101111101001110010110011010110
33322222222221111111111000000000
21098765432109876543210987654321

10110101011111110111100011100010

XOR with left part 0x0
10110101011111110111100011100010

swap
1011010101111111011110001110001000000000000000000000000000000000

expected
1011 0101 0111 1111 0111 1000 1110 0010 0000 0000 0000 0000 0000 0000 0000 1010


*/