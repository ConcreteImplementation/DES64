#ifndef _DES64_INTERNAL_HEADER_
#define _DES64_INTERNAL_HEADER_



#include "des64.h"
#include "des64_keyschedule.h"


typedef enum State {
	ENCIPHER,
	DECIPHER
} State;

typedef struct des64_context {
	keyschedule_t keyschedule;
	State state;
} des64_context;


PRIVATE
void _initial_permutation(uint64_t* source, size_t length);
PRIVATE
void _final_permutation(uint64_t* source, size_t length);

PRIVATE
uint64_t _expansion(uint64_t block);
PRIVATE
int _find_substitution(int boxNumber, const int block6bits);
PRIVATE
uint32_t _substitution(uint64_t source);
PRIVATE
void _primitive(uint32_t* source);

PRIVATE
void _swap(uint64_t* source, size_t numberOfBlocks);
PRIVATE
void _cipher_function(uint64_t* source, size_t numberOfBlocks, uint64_t key);



#endif