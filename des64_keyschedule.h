#ifndef _KEYSCHEDULE_HEADER_
#define _KEYSCHEDULE_HEADER_


#include <stdint.h>

// typedef struct {
// 	uint64_t key:48;
// } keyschedule_t;


typedef struct keyschedule_t keyschedule_t;

keyschedule_t* des64_new_keyschedule(uint64_t key);


#endif