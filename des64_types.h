#ifndef _DES64_TYPES_HEADER_
#define _DES64_TYPES_HEADER_

#include <stdint.h>


typedef	union {
	uint64_t block:56;

	struct {
		uint32_t C:28;
		uint32_t D:28;
	} blocks;
	
} key_block_t;






// typedef struct {
// 	uint32_t right;
// 	uint32_t left;
// 	uint64_t temp: 48;
// } half_t;

// typedef struct {
// 	uint64_t key:48;
// } key_schedule_t;


#endif