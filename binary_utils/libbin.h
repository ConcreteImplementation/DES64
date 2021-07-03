#define bin_sizeof(x) (sizeof(x)*8)

#define MASK64 ( (uint64_t) 1)

#define rotr(n, shift)  ( n>>shift  |  n<<(bin_sizeof(n)-shift) )
#define rotl(n, shift)  ( n<<shift  |  n>>(bin_sizeof(n)-shift) )



typedef enum {
	ERRBIN_SUCCESS = 0,
	ERRBIN_BUFFER_TOO_SMALL
} ERRBIN_T;


ERRBIN_T bin_itoa_typesize(uint64_t n, long typesize, char* buf, long bufsize);
 #define bin_itoa(n, buf, bufsize) (bin_itoa_typesize(n, sizeof(n), buf, bufsize))

char* bin_getptr_skipleadingzeros(char* buf);
ERRBIN_T bin_string_prettyspace(char* bufin, char* bufout, long bufoutsize, int space);