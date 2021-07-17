#include <stdio.h>
#include <stdint.h>


#include "des64_global_defines.h"
#include "des64.tables.h"
#include "des64.internal.h"

#include "des64_keyschedule.h"



void _permutation(uint64_t* source, size_t length, const short* table) {
	while(length--) {
		uint64_t destination = 0;

		DES64_DO_PERMUTATION(*source, destination, table, 64);
		
		*source = destination;
		source++;
	}
}

void _initial_permutation(uint64_t* source, size_t length) {
	_permutation(source, length, IP);
}

void _final_permutation(uint64_t* source, size_t length) {
	_permutation(source, length, FP);
}



uint64_t _expansion(uint64_t block) {
	uint64_t right = 0;

	DES64_DO_PERMUTATION(block, right, EXP, 48);

	return right;
}

// _substitution()
// _permutation32bits()


void _cipher_function(uint64_t* source, size_t textSize, keyschedule_t* keySchedule) {
	while( textSize-- ) {
		uint64_t right = _expansion(*source);
		right ^= keySchedule->key;

		// uint32_t r _substitution(R);
		// _permution32bits(r);

		*source =  (uint64_t)right << 32 | *source >> 32;
		source++;
	}
}

void des_encrypt(uint64_t* plainText, size_t textSize, uint64_t key) {
	// if(textSize % 8 != 0)
	// 	make_padding(plainText, &textSize);
	
	
	keyschedule_t keyschedule[DES64_NUMBER_OF_ROUNDS];
	make_keyschedule(key, keyschedule);

	_initial_permutation(plainText, textSize);

	// for(int i = 0; i < DES64_NUMBER_OF_ROUNDS; i++) {
	// _cipher_function(...);
	//}

	_final_permutation(plainText, textSize);
}