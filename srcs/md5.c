#include "md5.h"

/* Encodes input (UINT4) into output (unsigned char) by 4 bytes. Assumes len is
  a multiple of 4.
  This function transform a UINT4 into 4 unsianged char every loop.
 */
static void Encode(unsigned char *output, UINT4 *input, unsigned int len)
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
static void Decode(UINT4 *output, unsigned char *input, unsigned int len)
{
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4)
      output[i] = ((UINT4)input[j]) | (((UINT4)input[j+1]) << 8)
              | (((UINT4)input[j+2]) << 16) | (((UINT4)input[j+3]) << 24);
}

/* Note: Replace "for loop" with standard memcpy if possible.
 */

static void md5_memcpy(POINTER output, POINTER input, unsigned int len)
{
  unsigned int i;

  for (i = 0; i < len; i++)
      output[i] = input[i];
}

/* Note: Replace "for loop" with standard memset if possible.
 */
static void md5_memset(POINTER output, int value, unsigned int len)
{
  unsigned int i;

  for (i = 0; i < len; i++)
      ((char *)output)[i] = (char)value;
}
// first byte Ox80 is 1000 0000; 1 is the first bit after the message
// padding max is msg / 64 = 56, so max padding is 56 + (64 - 56) = 64 bytes
static unsigned char PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* MD5 basic transformation. Transforms state based on block. */
static void md5_transform(UINT4 state[4], unsigned char block[64])
{
  UINT4 x[16];
  UINT4 abcd[4];

  abcd[0] = state[0];
  abcd[1] = state[1];
  abcd[2] = state[2];
  abcd[3] = state[3];

  Decode (x, block, 64);

  /* Round 1 */
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

 /* Round 2 */
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

  /* Round 3 */
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

  /* Round 4 */
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


  state[0] += abcd[0];
  state[1] += abcd[1];
  state[2] += abcd[2];
  state[3] += abcd[3];

  /* Zeroize sensitive information. */
  md5_memset ((POINTER)x, 0, sizeof (x));
}
/* MD5 initialization. Begins an MD5 operation, writing a new context.
 */
void md5_init(MD5_CTX *context)                                        /* context */
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
void md5_update(MD5_CTX *context, unsigned char *input, unsigned int inputLen)
{
  unsigned int i, index, partLen;

  /* Compute number of bytes mod 64 */
  index = (unsigned int)((context->count[0] >> 3) & 0x3F);

  /* Update number of bits */
  // accumulate bits number in count[0]; since inputLen is string length
  // meaning inputlen is number of chars
  if ((context->count[0] += ((UINT4)inputLen << 3)) < ((UINT4)inputLen << 3))
      context->count[1]++;
  // since the operation << 3 remove the top 3 bits of inputLen, here record
  // the top 3 bits that overflows
  context->count[1] += ((UINT4)inputLen >> 29);

  partLen = 64 - index;

  /* Transform as many times as possible. */
  // if inputLen < partLen then not transform
  if (inputLen >= partLen) {
	  //for padding index is the index after which starts padding
	  //in other normal case index == 0
      md5_memcpy ((POINTER)&context->buffer[index], (POINTER)input, partLen);
      md5_transform (context->state, context->buffer);

	  //execute 64 byte block, 16-word block until remainder of mode 64 block
     for (i = partLen; i + 63 < inputLen; i += 64)
       md5_transform (context->state, &input[i]);

     index = 0;
  }
  else
      i = 0;

  /* Buffer remaining input */
  md5_memcpy ((POINTER)&context->buffer[index], (POINTER)&input[i], inputLen-i);
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the
  the message digest and zeroizing the context.
 */
void md5_final(unsigned char digest[16], MD5_CTX *context)
{
  unsigned char bits[8];
  unsigned int index, padLen;

  /* Save number of bits. encode 8 bytes from count[2] that has 2 UINT4 (8 bytes in total)*/
  Encode (bits, context->count, 8);

  /* Pad out to 56 mod 64. */
  // bit length / 8 mode 64 
  index = (unsigned int)((context->count[0] >> 3) & 0x3f);
  //if less than 56 ok esle 56 + 64 padding
  padLen = (index < 56) ? (56 - index) : (120 - index);
  md5_update (context, PADDING, padLen);

  /* Append length (before padding) */
  // length is 64 -56 = 8 bytes, 64 bits size; 512 - 448 = 64 bits = 8 bytes;
  md5_update (context, bits, 8);

  /* Store state in digest */
  Encode (digest, context->state, 16);

  /* Zeroize sensitive information. */
  md5_memset ((POINTER)context, 0, sizeof (*context));
}
