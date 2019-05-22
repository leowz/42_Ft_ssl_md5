#include "ft_ssl.h"
#include "md5.h"

/* md5_encodes input (UINT4) into output (unsigned char) by 4 bytes. Assumes len is
  a multiple of 4.
  This function transform a UINT4 into 4 unsianged char every loop.
 */
void md5_encode(unsigned char *output, UINT4 *input, unsigned int len)
{
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4) {
    output[j] = (unsigned char)(input[i] & 0xff);
    output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
    output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
    output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
  }
}

/* md5_decodes input (unsigned char) into output (UINT4). Assumes len is
  a multiple of 4.
 */
void md5_decode(UINT4 *output, unsigned char *input, unsigned int len)
{
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4)
      output[i] = ((UINT4)input[j]) | (((UINT4)input[j+1]) << 8)
              | (((UINT4)input[j+2]) << 16) | (((UINT4)input[j+3]) << 24);
}

/* Note: Replace "for loop" with standard memcpy if possible.
 */

void md5_memcpy(POINTER output, POINTER input, unsigned int len)
{
  unsigned int i;

  for (i = 0; i < len; i++)
      output[i] = input[i];
}

/* Note: Replace "for loop" with standard memset if possible.
 */
void md5_memset(POINTER output, int value, unsigned int len)
{
  unsigned int i;

  for (i = 0; i < len; i++)
      ((char *)output)[i] = (char)value;
}

/* Prints a message digest in hexadecimal.
 */
void md5_print(unsigned char digest[16])
{
  unsigned int i;

  for (i = 0; i < 16; i++)
    ft_printf("%02x", digest[i]);
}
