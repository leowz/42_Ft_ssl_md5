#include "ft_ssl.h"

void sha256_init(SHA256_CTX *context)
{
	context->count[0] = 0;
	context->count[1] = 0;
	context->state[0] = 0x6A09E667;
	context->state[1] = 0xBB67AE85;
	context->state[2] = 0x3C6EF372;
	context->state[3] = 0xA54FF53A;
	context->state[4] = 0x510E527F;
	context->state[5] = 0x9B05688C;
	context->state[6] = 0x1F83D9AB;
	context->state[7] = 0x5BE0CD19;
}

void sha256_update(SHA256_CTX *context, unsigned char *input, unsigned int inputLen)
{
	unsigned int i;
	unsigned int index;
	unsigned int partLen;

	printf("%s\n", "update");
	index = (unsigned int)((context->count[0] >> 3) & 0x3F);
	if ((context->count[0] += ((UINT4)inputLen << 3)) < ((UINT4)inputLen << 3))
	  context->count[1]++;
	context->count[1] += ((UINT4)inputLen >> 29);
	printf("c1 %d, c0 %d\n", context->count[1], context->count[0]);
	partLen = 64 - index;
	if (inputLen >= partLen)
	{
		printf("%s\n", "update loop1");
	  md5_memcpy ((POINTER)&context->buffer[index], (POINTER)input, partLen);
	  sha256_transform (context->state, context->buffer);
	  i = partLen;
	  while (i + 63 < inputLen)
	  {
		printf("%s\n", "update loop2");
		  sha256_transform (context->state, &input[i]);
		  i += 64;
	  }
	 index = 0;
	}
	else
	{
		printf("%s\n", "update else");
	  i = 0;
	}
	md5_memcpy ((POINTER)&context->buffer[index], (POINTER)&input[i], inputLen-i);
}


void sha256_encode_length(unsigned char *output, UINT4 *input, unsigned int len)
{

    output[4] = (unsigned char)((input[0] >> 24) & 0xff);
    output[5] = (unsigned char)((input[0] >> 16) & 0xff);
    output[6] = (unsigned char)((input[0] >> 8) & 0xff);
    output[7] = (unsigned char)((input[0]) & 0xff);
    output[0] = (unsigned char)((input[1] >> 24) & 0xff);
    output[1] = (unsigned char)((input[1] >> 16) & 0xff);
    output[2] = (unsigned char)((input[1] >> 8) & 0xff);
    output[3] = (unsigned char)((input[1]) & 0xff);
}


void sha256_final(unsigned char digest[], SHA256_CTX *context)
{
	unsigned char bits[8];
	unsigned int index, padLen;
	unsigned char padding[64] = {
	  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	sha256_encode_length(bits, context->count, 8);
	index = (unsigned int)((context->count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	sha256_update (context, padding, padLen);
	sha256_update (context, bits, 8);
	sha256_encode (digest, context->state, 32);
	md5_memset ((POINTER)context, 0, sizeof (*context));
}
