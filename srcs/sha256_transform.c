#include "md5.h"

static void round_1(UINT4 *regi, UINT4 *x)
{
	ff (regi, x[ 0], S11, 0xd76aa478); /* 1 */
	ff (regi, x[ 1], S12, 0xe8c7b756); /* 2 */
	ff (regi, x[ 2], S13, 0x242070db); /* 3 */
	ff (regi, x[ 3], S14, 0xc1bdceee); /* 4 */
	ff (regi, x[ 4], S11, 0xf57c0faf); /* 5 */
	ff (regi, x[ 5], S12, 0x4787c62a); /* 6 */
	ff (regi, x[ 6], S13, 0xa8304613); /* 7 */
	ff (regi, x[ 7], S14, 0xfd469501); /* 8 */
	ff (regi, x[ 8], S11, 0x698098d8); /* 9 */
	ff (regi, x[ 9], S12, 0x8b44f7af); /* 10 */
	ff (regi, x[10], S13, 0xffff5bb1); /* 11 */
	ff (regi, x[11], S14, 0x895cd7be); /* 12 */
	ff (regi, x[12], S11, 0x6b901122); /* 13 */
	ff (regi, x[13], S12, 0xfd987193); /* 14 */
	ff (regi, x[14], S13, 0xa679438e); /* 15 */
	ff (regi, x[15], S14, 0x49b40821); /* 16 */
}

static void round_2(UINT4 *regi, UINT4 *x)
{
	gg (regi, x[ 1], S21, 0xf61e2562); /* 17 */
	gg (regi, x[ 6], S22, 0xc040b340); /* 18 */
	gg (regi, x[11], S23, 0x265e5a51); /* 19 */
	gg (regi, x[ 0], S24, 0xe9b6c7aa); /* 20 */
	gg (regi, x[ 5], S21, 0xd62f105d); /* 21 */
	gg (regi, x[10], S22,  0x2441453); /* 22 */
	gg (regi, x[15], S23, 0xd8a1e681); /* 23 */
	gg (regi, x[ 4], S24, 0xe7d3fbc8); /* 24 */
	gg (regi, x[ 9], S21, 0x21e1cde6); /* 25 */
	gg (regi, x[14], S22, 0xc33707d6); /* 26 */
	gg (regi, x[ 3], S23, 0xf4d50d87); /* 27 */
	gg (regi, x[ 8], S24, 0x455a14ed); /* 28 */
	gg (regi, x[13], S21, 0xa9e3e905); /* 29 */
	gg (regi, x[ 2], S22, 0xfcefa3f8); /* 30 */
	gg (regi, x[ 7], S23, 0x676f02d9); /* 31 */
	gg (regi, x[12], S24, 0x8d2a4c8a); /* 32 */
}

static void round_3(UINT4 *regi, UINT4 *x)
{
	hh (regi, x[ 5], S31, 0xfffa3942); /* 33 */
	hh (regi, x[ 8], S32, 0x8771f681); /* 34 */
	hh (regi, x[11], S33, 0x6d9d6122); /* 35 */
	hh (regi, x[14], S34, 0xfde5380c); /* 36 */
	hh (regi, x[ 1], S31, 0xa4beea44); /* 37 */
	hh (regi, x[ 4], S32, 0x4bdecfa9); /* 38 */
	hh (regi, x[ 7], S33, 0xf6bb4b60); /* 39 */
	hh (regi, x[10], S34, 0xbebfbc70); /* 40 */
	hh (regi, x[13], S31, 0x289b7ec6); /* 41 */
	hh (regi, x[ 0], S32, 0xeaa127fa); /* 42 */
	hh (regi, x[ 3], S33, 0xd4ef3085); /* 43 */
	hh (regi, x[ 6], S34,  0x4881d05); /* 44 */
	hh (regi, x[ 9], S31, 0xd9d4d039); /* 45 */
	hh (regi, x[12], S32, 0xe6db99e5); /* 46 */
	hh (regi, x[15], S33, 0x1fa27cf8); /* 47 */
	hh (regi, x[ 2], S34, 0xc4ac5665); /* 48 */
}

static void round_4(UINT4 *regi, UINT4 *x)
{
	ii (regi, x[ 0], S41, 0xf4292244); /* 49 */
	ii (regi, x[ 7], S42, 0x432aff97); /* 50 */
	ii (regi, x[14], S43, 0xab9423a7); /* 51 */
	ii (regi, x[ 5], S44, 0xfc93a039); /* 52 */
	ii (regi, x[12], S41, 0x655b59c3); /* 53 */
	ii (regi, x[ 3], S42, 0x8f0ccc92); /* 54 */
	ii (regi, x[10], S43, 0xffeff47d); /* 55 */
	ii (regi, x[ 1], S44, 0x85845dd1); /* 56 */
	ii (regi, x[ 8], S41, 0x6fa87e4f); /* 57 */
	ii (regi, x[15], S42, 0xfe2ce6e0); /* 58 */
	ii (regi, x[ 6], S43, 0xa3014314); /* 59 */
	ii (regi, x[13], S44, 0x4e0811a1); /* 60 */
	ii (regi, x[ 4], S41, 0xf7537e82); /* 61 */
	ii (regi, x[11], S42, 0xbd3af235); /* 62 */
	ii (regi, x[ 2], S43, 0x2ad7d2bb); /* 63 */
	ii (regi, x[ 9], S44, 0xeb86d391); /* 64 */
}

void sha256_transform(UINT4 state[4], unsigned char block[64])
{
	  /* Constants defined in FIPS 180-3, section 4.2.2 */
  static const UINT4 K[64] = {
      0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
      0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
      0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
      0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
      0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
      0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
      0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
      0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
      0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
      0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
      0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
      0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
      0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
  };
  	int        t, t4;                   /* Loop counter */
  	UINT4   temp1, temp2;            /* Temporary word value */
  	UINT4   w[64];                   /* Word sequence */
	UINT4	regi[8];

	regi[0] = state[0];
	regi[1] = state[1];
	regi[2] = state[2];
	regi[3] = state[3];
	regi[4] = state[4];
	regi[5] = state[5];
	regi[6] = state[6];
	regi[7] = state[7];
	md5_decode (w, block, 64);

	for (t = 16; t < 64; t++)
    	W[t] = SHA256_sigma1(W[t-2]) + W[t-7] + SHA256_sigma0(W[t-15]) + W[t-16];

	for (t = 0; t < 64; t++) {
	    temp1 = H + SHA256_SIGMA1(E) + SHA_Ch(E,F,G) + K[t] + W[t];
	    temp2 = SHA256_SIGMA0(A) + SHA_Maj(A,B,C);
	    H = G;
	    G = F;
	    F = E;
	    E = D + temp1;
	    D = C;
	    C = B;
	    B = A;
	    A = temp1 + temp2;
    }

    state[0] += regi[0];
	state[1] += regi[1];
	state[2] += regi[2];
	state[3] += regi[3];
}
