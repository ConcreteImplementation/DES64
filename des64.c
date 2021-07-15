#include <stdio.h>
#include <stdint.h>


#include "des64_tables.h"
#include "des64_defines.h"

#include "binary_utility/binary_utility.h"








void _permutation(uint64_t* source, size_t length, const short* table) {
	while(length--) {
		uint64_t destination = 0;

		for(int i = 0; i < 64; i++)
			if( DES64_IS_BIT_SET(*source, table, i) )
				destination |= MASKS[i];
		
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





void des_encrypt(uint64_t* plainText, size_t textSize, uint64_t key) {

	

}