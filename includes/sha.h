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
void sha_print(unsigned char digest[]);

#endif
