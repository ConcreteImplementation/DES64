#ifndef _DES64_DEFINES_HEADER_
#define _DES64_DEFINES_HEADER_

#include <stdint.h>



#define PUBLIC

#ifdef TESTING
	#define PRIVATE
#else
	#define PRIVATE static
#endif



#ifndef DES64_NUMBER_OF_ROUNDS
	#define DES64_NUMBER_OF_ROUNDS 16
#else
	#if DES64_NUMBER_OF_ROUNDS != 16
		#warning DES64_NUMBER_OF_ROUNDS != 16
	#endif

	#if   DES64_NUMBER_OF_ROUNDS <  1
		#error "DES64_NUMBER_OF_ROUNDS <  1"
	#elif DES64_NUMBER_OF_ROUNDS > 16
		#error "DES64_NUMBER_OF_ROUNDS > 16"
	#elif DES64_NUMBER_OF_ROUNDS % 2 != 0
		#warning "DES64_NUMBER_OF_ROUNDS is odd"
	#endif
#endif




// Precomputed bitmasks
const uint64_t MASKS[64];



#define DES64_IS_BIT_SET(source, table, index) \
	( source  &  MASKS[ table[index] -1 ] )

#define DES64_DO_PERMUTATION(source, destination, table, iterations) \
	for(int i = 0; i < iterations; i++)                        \
		if( DES64_IS_BIT_SET(source, table, i) )               \
			destination |= MASKS[i]; 
			


#endif