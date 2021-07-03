
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



