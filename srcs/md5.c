/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:36:29 by zweng             #+#    #+#             */
/*   Updated: 2019/04/11 17:29:06 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static void MD5Transform(UINT4 [4], unsigned char [64]);
static void Encode(unsigned char *, UINT4 *, unsigned int);
static void Decode(UINT4 *, unsigned char *, unsigned int);
static void MD5_memcpy(POINTER, POINTER, unsigned int);
static void MD5_memset(POINTER, int, unsigned int);

/* F, G, H and I are basic MD5 functions. */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits. */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation. */
#define FF(a, b, c, d, x, s, ac) { \
 (a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) { \
 (a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) { \
 (a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) { \
 (a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

void MD5Init (MD5_CTX *context)
{
  context->count[0] = context->count[1] = 0;
  /* Load magic initialization constants. */
  context->state[0] = 0x67452301;
  context->state[1] = 0xefcdab89;
  context->state[2] = 0x98badcfe;
  context->state[3] = 0x10325476;
}

/* MD5 block update operation. Continues an MD5 message-digest
  operation, processing another message block, and updating the
  context.
 */
void MD5Update (MD5_CTX *context, unsigned char *input, unsigned int inputLen)
{
  unsigned int i, index, partLen;

  /* Compute number of bytes mod 64 */
  index = (unsigned int)((context->count[0] >> 3) & 0x3F);
  printf("Index is %d\n", index);

  /* Update number of bits */
  if ((context->count[0] += ((UINT4)inputLen << 3)) < ((UINT4)inputLen << 3))
      context->count[1]++;
  context->count[1] += ((UINT4)inputLen >> 29);

  partLen = 64 - index;

  /* Transform as many times as possible. */
  if (inputLen >= partLen)
  {
      MD5_memcpy ((POINTER)&context->buffer[index], (POINTER)input, partLen);
      MD5Transform (context->state, context->buffer);
	  for (i = partLen; i + 63 < inputLen; i += 64)
		  MD5Transform (context->state, &input[i]);
	  index = 0;
  }
  else
      i = 0;
  /* Buffer remaining input */
  MD5_memcpy ((POINTER)&context->buffer[index], (POINTER)&input[i], inputLen-i);
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the
  the message digest and zeroizing the context.
 */
void MD5Final (unsigned char digest[16], MD5_CTX *context)
{
  unsigned char bits[8];
  unsigned int index, padLen;
  unsigned char PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  /* Save number of bits */
  Encode (bits, context->count, 8);

  /* Pad out to 56 mod 64. */
  index = (unsigned int)((context->count[0] >> 3) & 0x3f);
  padLen = (index < 56) ? (56 - index) : (120 - index);
  MD5Update (context, PADDING, padLen);

  /* Append length (before padding) */
  MD5Update (context, bits, 8);

  /* Store state in digest */
  Encode (digest, context->state, 16);

  /* Zeroize sensitive information. */
  MD5_memset ((POINTER)context, 0, sizeof (*context));
}

/* MD5 basic transformation. Transforms state based on block. */
static void MD5Transform (state, block)
UINT4 state[4];
unsigned char block[64];
{
  UINT4 x[16];
  UINT4 regis[4];

  regis[0] = state[0];
  regis[1] = state[1];
  regis[2] = state[2];
  regis[3] = state[3];
  Decode (x, block, 64);

  /* Round 1 */
  // abcd register, x input, s shift, last table T[1 ... 64] sine values
  ff(regis, x[0], S11, 0xd76aa478);
  ff(regis, x[1], S12, 0xe8c7b756);
  ff(regis, x[2], S13, 0x242070db);
  ff(regis, x[3], S14, 0xc1bdceee);
  ff(regis, x[4], S11, 0xf57c0faf);
  ff(regis, x[5], S12, 0x4787c62a);
  ff(regis, x[6], S13, 0xa8304613);
  ff(regis, x[7], S14, 0xfd469501);
  ff(regis, x[8], S11, 0x698098d8);
  ff(regis, x[9], S12, 0x8b44f7af);
  ff(regis, x[10], S13, 0xffff5bb1);
  ff(regis, x[11], S14, 0x895cd7be);
  ff(regis, x[12], S11, 0x6b901122);
  ff(regis, x[13], S12, 0xfd987193);
  ff(regis, x[14], S13, 0xa679438e);
  ff(regis, x[15], S14, 0x49b40821);

 /* Round 2 */
  gg(regis, x[1], S21, 0xf61e2562); /* 17 */
  gg(regis, x[6], S22, 0xc040b340); /* 18 */
  gg(regis, x[11], S23, 0x265e5a51); /* 19 */
  gg(regis, x[0], S24, 0xe9b6c7aa); /* 20 */
  gg(regis, x[5], S21, 0xd62f105d); /* 21 */
  gg(regis, x[10], S22,  0x2441453); /* 22 */
  gg(regis, x[15], S23, 0xd8a1e681); /* 23 */
  gg(regis, x[4], S24, 0xe7d3fbc8); /* 24 */
  gg(regis, x[9], S21, 0x21e1cde6); /* 25 */
  gg(regis, x[14], S22, 0xc33707d6); /* 26 */
  gg(regis, x[3], S23, 0xf4d50d87); /* 27 */
  gg(regis, x[8], S24, 0x455a14ed); /* 28 */
  gg(regis, x[13], S21, 0xa9e3e905); /* 29 */
  gg(regis, x[2], S22, 0xfcefa3f8); /* 30 */
  gg(regis, x[7], S23, 0x676f02d9); /* 31 */
  gg(regis, x[12], S24, 0x8d2a4c8a); /* 32 */

  /* Round 3 */
  hh(regis, x[5], S31, 0xfffa3942); /* 33 */
  hh(regis, x[8], S32, 0x8771f681); /* 34 */
  hh(regis, x[11], S33, 0x6d9d6122); /* 35 */
  hh(regis, x[14], S34, 0xfde5380c); /* 36 */
  hh(regis, x[1], S31, 0xa4beea44); /* 37 */
  hh(regis, x[4], S32, 0x4bdecfa9); /* 38 */
  hh(regis, x[7], S33, 0xf6bb4b60); /* 39 */
  hh(regis, x[10], S34, 0xbebfbc70); /* 40 */
  hh(regis, x[13], S31, 0x289b7ec6); /* 41 */
  hh(regis, x[0], S32, 0xeaa127fa); /* 42 */
  hh(regis, x[3], S33, 0xd4ef3085); /* 43 */
  hh(regis, x[6], S34,  0x4881d05); /* 44 */
  hh(regis, x[9], S31, 0xd9d4d039); /* 45 */
  hh(regis, x[12], S32, 0xe6db99e5);
  hh(regis, x[15], S33, 0x1fa27cf8);
  hh(regis, x[2], S34, 0xc4ac5665);

  /* Round 4 */
  ii(regis, x[ 0], S41, 0xf4292244);
  ii(regis, x[ 7], S42, 0x432aff97);
  ii(regis, x[14], S43, 0xab9423a7);
  ii(regis, x[ 5], S44, 0xfc93a039);
  ii(regis, x[12], S41, 0x655b59c3);
  ii(regis, x[ 3], S42, 0x8f0ccc92);
  ii(regis, x[10], S43, 0xffeff47d);
  ii(regis, x[ 1], S44, 0x85845dd1);
  ii(regis, x[ 8], S41, 0x6fa87e4f);
  ii(regis, x[15], S42, 0xfe2ce6e0);
  ii(regis, x[ 6], S43, 0xa3014314);
  ii(regis, x[13], S44, 0x4e0811a1);
  ii(regis, x[ 4], S41, 0xf7537e82);
  ii(regis, x[11], S42, 0xbd3af235);
  ii(regis, x[ 2], S43, 0x2ad7d2bb);
  ii(regis, x[ 9], S44, 0xeb86d391);

  state[0] += regis[0];
  state[1] += regis[1];
  state[2] += regis[2];
  state[3] += regis[3];

  /* Zeroize sensitive information. */
  MD5_memset ((POINTER)x, 0, sizeof (x));
}

/* Encodes input (UINT4) into output (unsigned char). Assumes len is
  a multiple of 4.
 */
static void Encode (output, input, len)
unsigned char *output;
UINT4 *input;
unsigned int len;
{
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4) {
    output[j] = (unsigned char)(input[i] & 0xff);
    output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
    output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
    output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
  }
}

/* Decodes input (unsigned char) into output (UINT4). Assumes len is
  a multiple of 4.
 */
static void Decode (output, input, len)
UINT4 *output;
unsigned char *input;
unsigned int len;
{
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4)
      output[i] = ((UINT4)input[j]) | (((UINT4)input[j+1]) << 8)
              | (((UINT4)input[j+2]) << 16) | (((UINT4)input[j+3]) << 24);
}

/* Note: Replace "for loop" with standard memcpy if possible.
 */

static void MD5_memcpy (output, input, len)
POINTER output;
POINTER input;
unsigned int len;
{
  unsigned int i;

  for (i = 0; i < len; i++)
      output[i] = input[i];
}

/* Note: Replace "for loop" with standard memset if possible.
 */
static void MD5_memset (output, value, len)
POINTER output;
int value;
unsigned int len;
{
  unsigned int i;

  for (i = 0; i < len; i++)
      ((char *)output)[i] = (char)value;
}
