#include "md5.h"


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
// first byte Ox80 is 1000 0000; 1 is the first bit after the message
// padding max is msg / 64 = 56, so max padding is 56 + (64 - 56) = 64 bytes
	unsigned char padding[64] = {
	  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

  /* Save number of bits. encode 8 bytes from count[2] that has 2 UINT4 (8 bytes in total)*/
  md5_encode (bits, context->count, 8);

  /* Pad out to 56 mod 64. */
  // bit length / 8 mode 64 
  index = (unsigned int)((context->count[0] >> 3) & 0x3f);
  //if less than 56 ok esle 56 + 64 padding
  padLen = (index < 56) ? (56 - index) : (120 - index);
  md5_update (context, padding, padLen);

  /* Append length (before padding) */
  // length is 64 -56 = 8 bytes, 64 bits size; 512 - 448 = 64 bits = 8 bytes;
  md5_update (context, bits, 8);

  /* Store state in digest */
  md5_encode (digest, context->state, 16);

  /* Zeroize sensitive information. */
  md5_memset ((POINTER)context, 0, sizeof (*context));
}
