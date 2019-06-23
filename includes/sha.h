/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:12:10 by zweng             #+#    #+#             */
/*   Updated: 2019/06/14 16:30:32 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA_H
# define SHA_H

typedef unsigned char	*POINTER;
typedef unsigned int	UINT4;

typedef struct
{
  UINT4					count[2];
  UINT4					state[8];
  unsigned char			buffer[64];
}						SHA256_CTX;


void					sha256(int ac, char **av);
void sha256_init(SHA256_CTX *context);
void sha256_update(SHA256_CTX *context, unsigned char *input, unsigned int inputLen);
void sha256_final(unsigned char digest[], SHA256_CTX *context);
void sha256_transform(UINT4 state[4], unsigned char block[64]);
void sha_print(unsigned char digest[]);
void sha256_encode(unsigned char *output, UINT4 *input, unsigned int len);
void sha256_decode(UINT4 *output, unsigned char *input, unsigned int len);

#ifndef USE_MODIFIED_MACROS
#define SHA_Ch(x,y,z)        (((x) & (y)) ^ ((~(x)) & (z)))
#define SHA_Maj(x,y,z)       (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#else /* USE_MODIFIED_MACROS */
/*
 * The following definitions are equivalent and potentially faster.
 */

#define SHA_Ch(x, y, z)      (((x) & ((y) ^ (z))) ^ (z))
#define SHA_Maj(x, y, z)     (((x) & ((y) | (z))) | ((y) & (z)))

#endif /* USE_MODIFIED_MACROS */

#define SHA_Parity(x, y, z)  ((x) ^ (y) ^ (z))


#endif
