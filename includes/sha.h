/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:12:10 by zweng             #+#    #+#             */
/*   Updated: 2019/09/18 21:06:19 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA_H
# define SHA_H

typedef unsigned char	*t_pointer;
typedef unsigned int	t_uint4;

typedef struct
{
	t_uint4				count[2];
	t_uint4				state[8];
	unsigned char		buffer[64];
}	t_sha256;

void					sha256(int ac, char **av);
void					sha256_init(t_sha256 *context);
void					sha256_update(t_sha256 *context,
		unsigned char *input, unsigned int input_len);
void					sha256_final(unsigned char digest[],
		t_sha256 *context);
void					sha256_transform(t_uint4 state[4],
		unsigned char block[64]);
void					sha_print(unsigned char digest[]);
void					sha256_encode(unsigned char *output,
		t_uint4 *input, unsigned int len);
void					sha256_decode(t_uint4 *output,
		unsigned char *input, unsigned int len);
t_uint4					sha256_maj(t_uint4 x, t_uint4 y, t_uint4 z);
t_uint4					sha256_bsig0(t_uint4 word);
t_uint4					sha256_bsig1(t_uint4 word);
t_uint4					sha256_ssig0(t_uint4 word);
t_uint4					sha256_ssig1(t_uint4 word);
#endif
