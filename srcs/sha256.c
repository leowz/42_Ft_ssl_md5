/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:29:11 by zweng             #+#    #+#             */
/*   Updated: 2019/09/18 21:10:40 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	sha256_init(t_sha256 *context)
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

void	sha256_update(t_sha256 *context, unsigned char *input,
		unsigned int i_len)
{
	unsigned int i;
	unsigned int index;
	unsigned int p_len;

	index = (unsigned int)((context->count[0] >> 3) & 0x3F);
	if ((context->count[0] += ((t_uint4)i_len << 3)) < ((t_uint4)i_len << 3))
		context->count[1]++;
	context->count[1] += ((t_uint4)i_len >> 29);
	p_len = 64 - index;
	if (i_len >= p_len)
	{
		md5_memcpy((t_pointer)&context->buffer[index], (t_pointer)input, p_len);
		sha256_transform(context->state, context->buffer);
		i = p_len;
		while (i + 63 < i_len)
		{
			sha256_transform(context->state, &input[i]);
			i += 64;
		}
		index = 0;
	}
	else
		i = 0;
	md5_memcpy((t_pointer)&context->buffer[index],
			(t_pointer)&input[i], i_len - i);
}

void	sha256_encode_length(unsigned char *output, t_uint4 *input)
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

void	sha256_final(unsigned char digest[], t_sha256 *context)
{
	unsigned char	bits[8];
	unsigned int	index;
	unsigned int	p_len;
	unsigned char	padding[64];

	ft_bzero(padding, sizeof(unsigned char) * 64);
	*padding = 0x80;
	sha256_encode_length(bits, context->count);
	index = (unsigned int)((context->count[0] >> 3) & 0x3f);
	p_len = (index < 56) ? (56 - index) : (120 - index);
	sha256_update(context, padding, p_len);
	sha256_update(context, bits, 8);
	sha256_encode(digest, context->state, 32);
	md5_memset((t_pointer)context, 0, sizeof(*context));
}
