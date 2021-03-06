#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#include "des64_global_definitions.h"
#include "des64.internal.h"



PUBLIC
des64_context* des64_new_context(uint64_t key){
	des64_context* context = malloc(sizeof(des64_context));
	if(NULL == context)
		return NULL;
	
	context->keyschedule = build_keyschedule(key);
	context->state = ENCIPHER;

	return context;
}

PUBLIC
void des64_set_to_encipher(des64_context* context) {
	if(context->state == ENCIPHER)
		return;
	context->keyschedule = invert_keyschedule(context->keyschedule);
	context->state = ENCIPHER;
}

PUBLIC
void des64_set_to_decipher(des64_context* context) {
	if(context->state == DECIPHER)
		return;
	context->keyschedule = invert_keyschedule(context->keyschedule);
	context->state = DECIPHER;
}

PUBLIC
int des64_enciphering_computation(void* plainText, size_t textSize, des64_context* context) {
	if(textSize % 8 != 0)
		return 1; // Incorrect padding

	size_t numberOfBlocks = textSize / DES64_BLOCK_SIZE;
	keyschedule_t keyschedule = context->keyschedule;



	_initial_permutation(plainText, numberOfBlocks);

	for(int i = 0; i < DES64_NUMBER_OF_ROUNDS-1 ; i++) {
		_cipher_function(plainText, numberOfBlocks, keyschedule.key[i]);
		_swap(plainText, numberOfBlocks);
	}
	_cipher_function(plainText, numberOfBlocks, keyschedule.key[DES64_NUMBER_OF_ROUNDS-1]);

	_final_permutation(plainText, numberOfBlocks);



	return 0;
}






PRIVATE
void _permutation(uint64_t* source, size_t numberOfBlocks, const char* table) {
	 while(numberOfBlocks--) {
		uint64_t destination = 0;

		DES64_DO_PERMUTATION(*source, destination, table, 64);
		
		*source = destination;
		source++;
	}
}

PRIVATE
void _initial_permutation(uint64_t* source, size_t numberOfBlocks) {
	_permutation(source, numberOfBlocks, INITIAL_PERMUTATION_TABLE);
}

PRIVATE
void _final_permutation(uint64_t* source, size_t numberOfBlocks) {
	_permutation(source, numberOfBlocks, FINAL_PERMUTATION_TABLE);
}



PRIVATE
uint64_t _expansion(uint64_t block) {
	uint64_t right = 0;

	DES64_DO_PERMUTATION(block, right, EXPANSION_TABLE, 48);

	return right;
}






#define LOWER_6BITS_MASK 0x3F // 11 1111

PRIVATE
int _find_substitution(int boxNumber, const int source) {
	return SUBSTITUTION_BOXES_TABLE[boxNumber][source & LOWER_6BITS_MASK];
}

PRIVATE
uint32_t _substitution(uint64_t source) {
	uint32_t destination = 0;
	
	for(int boxNumber = 7; boxNumber >= 0; boxNumber--) {
		uint32_t substitution = _find_substitution(boxNumber, source);
		destination |= substitution << (7-boxNumber)*4;
		source >>= 6;
	}

	return destination;
}



PRIVATE
void _primitive(uint32_t* source) {
	uint32_t destination = 0;

	DES64_DO_PERMUTATION(*source, destination, PRIMITIVE_TABLE, 32);

	*source = destination;
}



PRIVATE
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
PRIVATE
void _swap(uint64_t* source, size_t numberOfBlocks) {
	while( numberOfBlocks-- ) {
		*source = *source << 32 | *source >> 32;
		source++;
	}
}