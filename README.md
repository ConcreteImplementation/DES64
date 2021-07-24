# DES64
"64" because I doubt that they had the luxury of `uint64_t` in 1975.

An exercice in `C`, trying to follow [FIPS publication 46-3](https://csrc.nist.gov/csrc/media/publications/fips/46/3/archive/1999-10-25/documents/fips46-3.pdf)


Although some optimization decisions were made, this exercice is far from optimal. I wanted to come up with a concise and readable solution on my own. Thus, delta swap and butterfly networks has not been used, and iterations are not unrolled. I might consider this on a next rewrite.

Keyschedule computation and padding is decoupled from the enciphering computation so that they are processed independently. This makes it more efficient to process multiple files with the same key as it is not recalculated each time. Padding is left to the client code to implement. This allows it to choose its method of padding. A simple ANSI padding is in the `demo/demo.c`

Done v1.0