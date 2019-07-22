#include "ft_ssl.h"
#include "md5.h"

void sha256_encode(unsigned char *output, UINT4 *input, unsigned int len)
{
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4) {
    output[j] = (unsigned char)((input[i] >> 24) & 0xff);
    output[j+1] = (unsigned char)((input[i] >> 16) & 0xff);
    output[j+2] = (unsigned char)((input[i] >> 8) & 0xff);
    output[j+3] = (unsigned char)((input[i]) & 0xff);
  }
}

void sha256_decode(UINT4 *output, unsigned char *input, unsigned int len)
{
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4)
      output[i] = ((UINT4)input[j]) << 24 | (((UINT4)input[j+1]) << 16)
              | (((UINT4)input[j+2]) << 8) | (((UINT4)input[j+3]) << 0);
}

void sha_print(unsigned char digest[32])
{
  unsigned int i;

  for (i = 0; i < 32; i++)
    ft_printf("%02x", digest[i]);
}
