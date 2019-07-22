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

typedef unsigned char		*POINTER;
typedef unsigned int		UINT4;
typedef unsigned long int	UINT8;

typedef struct
{
  UINT4					count[2];
  UINT4					state[8];
  unsigned char			buffer[64];
}						SHA256_CTX;

typedef struct
{
  UINT8					count[2];
  UINT8					state[8];
  unsigned char			buffer[64];
}						SHA512_CTX;


void					sha256(int ac, char **av);
void 					sha256_init(SHA256_CTX *context);
void					sha256_update(SHA256_CTX *context,
	unsigned char *input, unsigned int inputLen);
void sha256_final(unsigned char digest[], SHA256_CTX *context);
void sha256_transform(UINT4 state[4], unsigned char block[64]);
void sha_print(unsigned char digest[]);
void sha256_encode(unsigned char *output, UINT4 *input, unsigned int len);
void sha256_decode(UINT4 *output, unsigned char *input, unsigned int len);
UINT4 sha256_maj(UINT4 x, UINT4 y, UINT4 z);
UINT4 sha256_bsig0(UINT4 word);
UINT4 sha256_bsig1(UINT4 word);
UINT4 sha256_ssig0(UINT4 word);
UINT4 sha256_ssig1(UINT4 word);

#endif
