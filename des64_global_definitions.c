#include <stdint.h>



const uint64_t BITMASKS[64] = { 
	0x1,                0x2,                0x4,                0x8,
	0x10,               0x20,               0x40,               0x80,
	0x100,              0x200,              0x400,              0x800,
	0x1000,             0x2000,             0x4000,             0x8000,
	0x10000,            0x20000,            0x40000,            0x80000,
	0x100000,           0x200000,           0x400000,           0x800000, 
	0x1000000,          0x2000000,          0x4000000,          0x8000000, 
	0x10000000,         0x20000000,         0x40000000,         0x80000000, 
	0x100000000,        0x200000000,        0x400000000,        0x800000000, 
	0x1000000000,       0x2000000000,       0x4000000000,       0x8000000000, 
	0x10000000000,      0x20000000000,      0x40000000000,      0x80000000000,
	0x100000000000,     0x200000000000,     0x400000000000,     0x800000000000,
	0x1000000000000,    0x2000000000000,    0x4000000000000,    0x8000000000000,
	0x10000000000000,   0x20000000000000,   0x40000000000000,   0x80000000000000,
	0x100000000000000,  0x200000000000000,  0x400000000000000,  0x800000000000000,
	0x1000000000000000, 0x2000000000000000, 0x4000000000000000, 0x8000000000000000
};



const char INITIAL_PERMUTATION_TABLE[64] = {
	58-1, 50-1, 42-1, 34-1, 26-1, 18-1, 10-1, 2-1,
	60-1, 52-1, 44-1, 36-1, 28-1, 20-1, 12-1, 4-1,
	62-1, 54-1, 46-1, 38-1, 30-1, 22-1, 14-1, 6-1,
	64-1, 56-1, 48-1, 40-1, 32-1, 24-1, 16-1, 8-1,
	57-1, 49-1, 41-1, 33-1, 25-1, 17-1,  9-1, 1-1,
	59-1, 51-1, 43-1, 35-1, 27-1, 19-1, 11-1, 3-1,
	61-1, 53-1, 45-1, 37-1, 29-1, 21-1, 13-1, 5-1,
	63-1, 55-1, 47-1, 39-1, 31-1, 23-1, 15-1, 7-1
};



const char FINAL_PERMUTATION_TABLE[64] = {
	40-1,  8-1, 48-1, 16-1, 56-1, 24-1, 64-1, 32-1,
	39-1,  7-1, 47-1, 15-1, 55-1, 23-1, 63-1, 31-1,
	38-1,  6-1, 46-1, 14-1, 54-1, 22-1, 62-1, 30-1,
	37-1,  5-1, 45-1, 13-1, 53-1, 21-1, 61-1, 29-1,
	36-1,  4-1, 44-1, 12-1, 52-1, 20-1, 60-1, 28-1,
	35-1,  3-1, 43-1, 11-1, 51-1, 19-1, 59-1, 27-1,
	34-1,  2-1, 42-1, 10-1, 50-1, 18-1, 58-1, 26-1,
	33-1,  1-1, 41-1,  9-1, 49-1, 17-1, 57-1, 25-1
};



const char EXPANSION_TABLE[48] = {
	32-1,  1-1,  2-1,  3-1,  4-1,  5-1,
	 4-1,  5-1,  6-1,  7-1,  8-1,  9-1,
	 8-1,  9-1, 10-1, 11-1, 12-1, 13-1,
	12-1, 13-1, 14-1, 15-1, 16-1, 17-1,
	16-1, 17-1, 18-1, 19-1, 20-1, 21-1,
	20-1, 21-1, 22-1, 23-1, 24-1, 25-1,
	24-1, 25-1, 26-1, 27-1, 28-1, 29-1,
	28-1, 29-1, 30-1, 31-1, 32-1,  1-1
};



const char SUBSTITUTION_BOXES_TABLE[8][64] = {
	//S1
	{
		14,  0,  4, 15, 13,  7,  1,  4,  2, 14, 15,  2, 11, 13,  8,  1, 
		 3, 10, 10,  6,  6, 12, 12, 11,  5,  9,  9,  5,  0,  3,  7,  8, 
		 4, 15,  1, 12, 14,  8,  8,  2, 13,  4,  6,  9,  2,  1, 11,  7, 
		15,  5, 12, 11,  9,  3,  7, 14,  3, 10, 10,  0,  5,  6,  0, 13 
	}, 

	//S2
	{
		15,  3,  1, 13,  8,  4, 14,  7,  6, 15, 11,  2,  3,  8,  4, 14, 
		 9, 12,  7,  0,  2,  1, 13, 10, 12,  6,  0,  9,  5, 11, 10,  5, 
		 0, 13, 14,  8,  7, 10, 11,  1, 10,  3,  4, 15, 13,  4,  1,  2, 
		 5, 11,  8,  6, 12,  7,  6, 12,  9,  0,  3,  5,  2, 14, 15,  9 
	}, 

	//S3
	{
		10, 13,  0,  7,  9,  0, 14,  9,  6,  3,  3,  4, 15,  6,  5, 10, 
		 1,  2, 13,  8, 12,  5,  7, 14, 11, 12,  4, 11,  2, 15,  8,  1, 
		13,  1,  6, 10,  4, 13,  9,  0,  8,  6, 15,  9,  3,  8,  0,  7, 
		11,  4,  1, 15,  2, 14, 12,  3,  5, 11, 10,  5, 14,  2,  7, 12 
	}, 

	//S4
	{
		 7, 13, 13,  8, 14, 11,  3,  5,  0,  6,  6, 15,  9,  0, 10,  3, 
		 1,  4,  2,  7,  8,  2,  5, 12, 11,  1, 12, 10,  4, 14, 15,  9, 
		10,  3,  6, 15,  9,  0,  0,  6, 12, 10, 11,  1,  7, 13, 13,  8, 
		15,  9,  1,  4,  3,  5, 14, 11,  5, 12,  2,  7,  8,  2,  4, 14 
	}, 

	//S5
	{
		 2, 14, 12, 11,  4,  2,  1, 12,  7,  4, 10,  7, 11, 13,  6,  1, 
		 8,  5,  5,  0,  3, 15, 15, 10, 13,  3,  0,  9, 14,  8,  9,  6, 
		 4, 11,  2,  8,  1, 12, 11,  7, 10,  1, 13, 14,  7,  2,  8, 13, 
		15,  6,  9, 15, 12,  0,  5,  9,  6, 10,  3,  4,  0,  5, 14,  3 
	}, 

	//S6
	{
		12, 10,  1, 15, 10,  4, 15,  2,  9,  7,  2, 12,  6,  9,  8,  5, 
		 0,  6, 13,  1,  3, 13,  4, 14, 14,  0,  7, 11,  5,  3, 11,  8, 
		 9,  4, 14,  3, 15,  2,  5, 12,  2,  9,  8,  5, 12, 15,  3, 10, 
		 7, 11,  0, 14,  4,  1, 10,  7,  1,  6, 13,  0, 11,  8,  6, 13 
	}, 

	//S7
	{
		 4, 13, 11,  0,  2, 11, 14,  7, 15,  4,  0,  9,  8,  1, 13, 10, 
		 3, 14, 12,  3,  9,  5,  7, 12,  5,  2, 10, 15,  6,  8,  1,  6, 
		 1,  6,  4, 11, 11, 13, 13,  8, 12,  1,  3,  4,  7, 10, 14,  7, 
		10,  9, 15,  5,  6,  0,  8, 15,  0, 14,  5,  2,  9,  3,  2, 12 
	}, 

	//S8
	{
		13,  1,  2, 15,  8, 13,  4,  8,  6, 10, 15,  3, 11,  7,  1,  4, 
		10, 12,  9,  5,  3,  6, 14, 11,  5,  0,  0, 14, 12,  9,  7,  2, 
		 7,  2, 11,  1,  4, 14,  1,  7,  9,  4, 12, 10, 14,  8,  2, 13, 
		 0, 15,  6, 12, 10,  9, 13,  0, 15,  3,  3,  5,  5,  6,  8, 11 
	} 
};



const char PRIMITIVE_TABLE[32] = {
	32-25, 32- 4, 32-11, 32-22,
	32- 6, 32-30, 32-13, 32-19,
	32- 9, 32- 3, 32-27, 32-32,
	32-14, 32-24, 32- 8, 32- 2,
	32-10, 32-31, 32-18, 32- 5,
	32-26, 32-23, 32-15, 32- 1,
	32-17, 32-28, 32-12, 32-29,
	32-21, 32-20, 32- 7, 32-16
};







const char PERMUTED_CHOICE_1_TABLE[56] = {
	64- 4, 64-12, 64-20, 64-28, 64- 5, 64-13, 64-21,
	64-29, 64-37, 64-45, 64-53, 64-61, 64- 6, 64-14,
	64-22, 64-30, 64-38, 64-46, 64-54, 64-62, 64- 7,
	64-15, 64-23, 64-31, 64-39, 64-47, 64-55, 64-63,

	64-36, 64-44, 64-52, 64-60, 64- 3, 64-11, 64-19,
	64-27, 64-38, 64-43, 64-51, 64-59, 64- 2, 64-10,
	64-18, 64-26, 64-34, 64-42, 64-50, 64-58, 64- 1,
	64- 9, 64-17, 64-25, 64-33, 64-41, 64-49, 64-57

};



const char PERMUTED_CHOICE_2_TABLE[48] = {
	56-32, 56-29, 56-36, 56-50, 56-42, 56-46,
	56-53, 56-34, 56-56, 56-39, 56-49, 56-44,
	56-48, 56-33, 56-45, 56-51, 56-40, 56-30,
	56-55, 56-47, 56-37, 56-31, 56-52, 56-41,
	
	56- 2, 56-13, 56-20, 56-27, 56- 7, 56-16,
	56- 8, 56-26, 56- 4, 56-12, 56-19, 56-23,
	56-10, 56-21, 56- 6, 56-15, 56-28, 56- 3,
	56- 5, 56- 1, 56-24, 56-11, 56-17, 56-14
};



const char KEYSCHEDULE_LEFT_SHIFT_TABLE[16] = {
	1, 1, 2, 2,
	2, 2, 2, 2,
	1, 2, 2, 2,
	2, 2, 2, 1
};