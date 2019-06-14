#include "md5.h"

static void round_1(UINT4 *abcd, UINT4 *x)
{
	ff (abcd, x[ 0], S11, 0xd76aa478); /* 1 */
	ff (abcd, x[ 1], S12, 0xe8c7b756); /* 2 */
	ff (abcd, x[ 2], S13, 0x242070db); /* 3 */
	ff (abcd, x[ 3], S14, 0xc1bdceee); /* 4 */
	ff (abcd, x[ 4], S11, 0xf57c0faf); /* 5 */
	ff (abcd, x[ 5], S12, 0x4787c62a); /* 6 */
	ff (abcd, x[ 6], S13, 0xa8304613); /* 7 */
	ff (abcd, x[ 7], S14, 0xfd469501); /* 8 */
	ff (abcd, x[ 8], S11, 0x698098d8); /* 9 */
	ff (abcd, x[ 9], S12, 0x8b44f7af); /* 10 */
	ff (abcd, x[10], S13, 0xffff5bb1); /* 11 */
	ff (abcd, x[11], S14, 0x895cd7be); /* 12 */
	ff (abcd, x[12], S11, 0x6b901122); /* 13 */
	ff (abcd, x[13], S12, 0xfd987193); /* 14 */
	ff (abcd, x[14], S13, 0xa679438e); /* 15 */
	ff (abcd, x[15], S14, 0x49b40821); /* 16 */
}

static void round_2(UINT4 *abcd, UINT4 *x)
{
	gg (abcd, x[ 1], S21, 0xf61e2562); /* 17 */
	gg (abcd, x[ 6], S22, 0xc040b340); /* 18 */
	gg (abcd, x[11], S23, 0x265e5a51); /* 19 */
	gg (abcd, x[ 0], S24, 0xe9b6c7aa); /* 20 */
	gg (abcd, x[ 5], S21, 0xd62f105d); /* 21 */
	gg (abcd, x[10], S22,  0x2441453); /* 22 */
	gg (abcd, x[15], S23, 0xd8a1e681); /* 23 */
	gg (abcd, x[ 4], S24, 0xe7d3fbc8); /* 24 */
	gg (abcd, x[ 9], S21, 0x21e1cde6); /* 25 */
	gg (abcd, x[14], S22, 0xc33707d6); /* 26 */
	gg (abcd, x[ 3], S23, 0xf4d50d87); /* 27 */
	gg (abcd, x[ 8], S24, 0x455a14ed); /* 28 */
	gg (abcd, x[13], S21, 0xa9e3e905); /* 29 */
	gg (abcd, x[ 2], S22, 0xfcefa3f8); /* 30 */
	gg (abcd, x[ 7], S23, 0x676f02d9); /* 31 */
	gg (abcd, x[12], S24, 0x8d2a4c8a); /* 32 */
}

static void round_3(UINT4 *abcd, UINT4 *x)
{
	hh (abcd, x[ 5], S31, 0xfffa3942); /* 33 */
	hh (abcd, x[ 8], S32, 0x8771f681); /* 34 */
	hh (abcd, x[11], S33, 0x6d9d6122); /* 35 */
	hh (abcd, x[14], S34, 0xfde5380c); /* 36 */
	hh (abcd, x[ 1], S31, 0xa4beea44); /* 37 */
	hh (abcd, x[ 4], S32, 0x4bdecfa9); /* 38 */
	hh (abcd, x[ 7], S33, 0xf6bb4b60); /* 39 */
	hh (abcd, x[10], S34, 0xbebfbc70); /* 40 */
	hh (abcd, x[13], S31, 0x289b7ec6); /* 41 */
	hh (abcd, x[ 0], S32, 0xeaa127fa); /* 42 */
	hh (abcd, x[ 3], S33, 0xd4ef3085); /* 43 */
	hh (abcd, x[ 6], S34,  0x4881d05); /* 44 */
	hh (abcd, x[ 9], S31, 0xd9d4d039); /* 45 */
	hh (abcd, x[12], S32, 0xe6db99e5); /* 46 */
	hh (abcd, x[15], S33, 0x1fa27cf8); /* 47 */
	hh (abcd, x[ 2], S34, 0xc4ac5665); /* 48 */
}

static void round_4(UINT4 *abcd, UINT4 *x)
{
	ii (abcd, x[ 0], S41, 0xf4292244); /* 49 */
	ii (abcd, x[ 7], S42, 0x432aff97); /* 50 */
	ii (abcd, x[14], S43, 0xab9423a7); /* 51 */
	ii (abcd, x[ 5], S44, 0xfc93a039); /* 52 */
	ii (abcd, x[12], S41, 0x655b59c3); /* 53 */
	ii (abcd, x[ 3], S42, 0x8f0ccc92); /* 54 */
	ii (abcd, x[10], S43, 0xffeff47d); /* 55 */
	ii (abcd, x[ 1], S44, 0x85845dd1); /* 56 */
	ii (abcd, x[ 8], S41, 0x6fa87e4f); /* 57 */
	ii (abcd, x[15], S42, 0xfe2ce6e0); /* 58 */
	ii (abcd, x[ 6], S43, 0xa3014314); /* 59 */
	ii (abcd, x[13], S44, 0x4e0811a1); /* 60 */
	ii (abcd, x[ 4], S41, 0xf7537e82); /* 61 */
	ii (abcd, x[11], S42, 0xbd3af235); /* 62 */
	ii (abcd, x[ 2], S43, 0x2ad7d2bb); /* 63 */
	ii (abcd, x[ 9], S44, 0xeb86d391); /* 64 */
}

void md5_transform(UINT4 state[4], unsigned char block[64])
{
	UINT4 x[16];
	UINT4 abcd[4];

	abcd[0] = state[0];
	abcd[1] = state[1];
	abcd[2] = state[2];
	abcd[3] = state[3];
	md5_decode (x, block, 64);
	round_1(abcd, x);
	round_2(abcd, x);
	round_3(abcd, x);
	round_4(abcd, x);
	state[0] += abcd[0];
	state[1] += abcd[1];
	state[2] += abcd[2];
	state[3] += abcd[3];
	md5_memset ((POINTER)x, 0, sizeof (x));
}
