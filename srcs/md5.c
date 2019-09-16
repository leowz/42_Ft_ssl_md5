#include "md5.h"

void md5_init(MD5_CTX *context)
{
	context->count[0] = 0;
	context->count[1] = 0;
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
}

void md5_update(MD5_CTX *context, unsigned char *input, unsigned int inputLen)
{
	unsigned int i;
	unsigned int index;
	unsigned int partLen;

	index = (unsigned int)((context->count[0] >> 3) & 0x3F);
	if ((context->count[0] += ((UINT4)inputLen << 3)) < ((UINT4)inputLen << 3))
	  context->count[1]++;
	context->count[1] += ((UINT4)inputLen >> 29);
	partLen = 64 - index;
	if (inputLen >= partLen)
	{
	  md5_memcpy ((POINTER)&context->buffer[index], (POINTER)input, partLen);
	  md5_transform (context->state, context->buffer);
	  i = partLen;
	  while (i + 63 < inputLen)
	  {
		  md5_transform (context->state, &input[i]);
		  i += 64;
	  }
	 index = 0;
	}
	else
	  i = 0;
	md5_memcpy ((POINTER)&context->buffer[index],
			(POINTER)&input[i], inputLen-i);
}

void md5_final(unsigned char digest[16], MD5_CTX *context)
{
	unsigned char bits[8];
	unsigned int index, padLen;
	unsigned char padding[64] = {
	  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	md5_encode(bits, context->count, 8);
	index = (unsigned int)((context->count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	md5_update(context, padding, padLen);
	md5_update(context, bits, 8);
	md5_encode(digest, context->state, 16);
	md5_memset((POINTER)context, 0, sizeof(*context));
}
