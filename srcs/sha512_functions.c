#include "sha.h"

UINT4 sha256_maj(UINT4 x, UINT4 y, UINT4 z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

UINT4 sha256_bsig0(UINT4 word)
{
	 return ((word >> 2) | (word << 30))
	 ^ ((word >> 13) | (word << 19))
	 ^ ((word >> 22) | (word << 10));
}

UINT4 sha256_bsig1(UINT4 word)
{
	 return ((word >> 6) | (word << 26))
	 ^ ((word >> 11) | (word << 21))
	 ^ ((word >> 25) | (word << 7));
}

UINT4 sha256_ssig0(UINT4 word)
{
	 return ((word >> 7) | (word << 25))
	 ^ ((word >> 18) | (word << 14))
	 ^ (word >> 3);
}

UINT4 sha256_ssig1(UINT4 word)
{
	 return ((word >> 17) | (word << 15))
	 ^ ((word >> 19) | (word << 13))
	 ^ (word >> 10);
}