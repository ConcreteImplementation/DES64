#ifndef _KEYSCHEDULE_HEADER_
#define _KEYSCHEDULE_HEADER_


#include <stdint.h>

typedef struct {
	uint64_t key:48;
} keyschedule_t;


void make_keyschedule(uint64_t key, keyschedule_t* outKeySchedule);


#endif