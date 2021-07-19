#include <stdio.h>
#include <stdint.h>


#include "des64_global_defines.h"
#include "des64.tables.h"
#include "des64.internal.h"

#include "des64_keyschedule.h"
#include "des64_keyschedule.internal.h"



void _permutation(uint64_t* source, size_t numberOfBlocks, const short* table) {
	 while(numberOfBlocks--) {
		uint64_t destination = 0;

		DES64_DO_PERMUTATION(*source, destination, table, 64);
		
		*source = destination;
		source++;
	}
}

void _initial_permutation(uint64_t* source, size_t numberOfBlocks) {
	_permutation(source, numberOfBlocks, IP);
}

void _final_permutation(uint64_t* source, size_t numberOfBlocks) {
	_permutation(source, numberOfBlocks, FP);
}



uint64_t _expansion(uint64_t block) {
	uint64_t right = 0;

	DES64_DO_PERMUTATION(block, right, EXP, 48);

	return right;
}

int _find_substitution(int boxNumber, const int block6bits) {
	int i = ( (block6bits & 0x20) >> 4 )  |  (block6bits & 0x1);
	int j = (block6bits & 0x1E) >> 1;
	return SBOX[boxNumber][i][j];
}
uint32_t _substitution(uint64_t source) {
	uint32_t destination = 0;

	for(int boxNumber = 0; boxNumber < 8 ; boxNumber++) {
		uint32_t substitution = _find_substitution(boxNumber, source);
		destination |= substitution  <<  (boxNumber * 4);
		source >>= 6;
	}

	return destination;
}

void _primitive(uint32_t* source) {
	uint32_t destination = 0;

	DES64_DO_PERMUTATION(*source, destination, P, 32);

	*source = destination;
}


void _cipher_function(uint64_t* source, size_t numberOfBlocks, uint64_t key) {
	
	while( numberOfBlocks-- ) {
		uint64_t right48bit = _expansion(*source);
		
		right48bit ^= key;

		uint32_t right32bits = _substitution(right48bit);

		_primitive(&right32bits);

		right32bits ^= *source >> 32;
		
		*source = (uint64_t)right32bits << 32 | *source & 0xFFFFFFFF;

		source++;
	}

}


void _swap(uint64_t* source, size_t numberOfBlocks) {
	while( numberOfBlocks-- ) {
		*source = *source << 32 | *source >> 32;
		source++;
	}
}



void des64_encrypt(void* plainText, size_t textSize, keyschedule_t* keyschedule) {
	// if(0 >= DES64_NUMBER_OF_ROUNDS || DES64_NUMBER_OF_ROUNDS > 16) {
	// 	fprintf(stderr, "Error: DES64_NUMBER_OF_ROUNDS == %d\n", DES64_NUMBER_OF_ROUNDS);
	// 	return;
	// }
	
	// if(textSize % 8 != 0)
	// 	return; // Incorrect padding

	size_t numberOfBlocks = textSize / DES64_BLOCK_SIZE;


	_initial_permutation(plainText, numberOfBlocks);

	for(int i = 0; i < DES64_NUMBER_OF_ROUNDS-1 ; i++) {
		_cipher_function(plainText, numberOfBlocks, keyschedule->key[i]);
		_swap(plainText, numberOfBlocks);
	}
	_cipher_function(plainText, numberOfBlocks, keyschedule->key[DES64_NUMBER_OF_ROUNDS-1]);

	_final_permutation(plainText, numberOfBlocks);
}



void des64_decrypt(void* plainText, size_t textSize, keyschedule_t* keyschedule) {
	// if(0 >= DES64_NUMBER_OF_ROUNDS || DES64_NUMBER_OF_ROUNDS > 16) {
	// 	printf(stderr, "Error: DES64_NUMBER_OF_ROUNDS == %d\n", DES64_NUMBER_OF_ROUNDS);
	// 	return;
	// }
	
	// if(textSize % 8 != 0)
	// 	return; // Incorrect padding

	size_t numberOfBlocks = textSize / DES64_BLOCK_SIZE;

	_initial_permutation(plainText, numberOfBlocks);

	for(int i = DES64_NUMBER_OF_ROUNDS-1; i > 0; i--) {
		_cipher_function(plainText, numberOfBlocks, keyschedule->key[i]);
		_swap(plainText, numberOfBlocks);
	}
	_cipher_function(plainText, numberOfBlocks, keyschedule->key[0]);

	_final_permutation(plainText, numberOfBlocks);
}