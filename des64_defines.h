#ifndef _DES64_DEFINES_HEADER_
#define _DES64_DEFINES_HEADER_



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
		#error "DES64_NUMBER_OF_ROUNDS is odd"
	#endif
#endif



#define DES64_IS_BIT_SET(source, table, index)  ( source  &  MASKS[ table[index] -1 ] )



#endif