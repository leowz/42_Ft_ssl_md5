/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:30:11 by zweng             #+#    #+#             */
/*   Updated: 2019/09/18 21:09:19 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "md5.h"

void	md5_init(t_md5 *context)
{
	context->count[0] = 0;
	context->count[1] = 0;
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
}

void	md5_update(t_md5 *ctx, unsigned char *input, unsigned int i_len)
{
	unsigned int i;
	unsigned int index;
	unsigned int p_len;

	index = (unsigned int)((ctx->count[0] >> 3) & 0x3F);
	if ((ctx->count[0] += ((t_uint4)i_len << 3)) < ((t_uint4)i_len << 3))
		ctx->count[1]++;
	ctx->count[1] += ((t_uint4)i_len >> 29);
	p_len = 64 - index;
	if (i_len >= p_len)
	{
		md5_memcpy((t_pointer)&ctx->buffer[index], (t_pointer)input, p_len);
		md5_transform(ctx->state, ctx->buffer);
		i = p_len;
		while (i + 63 < i_len)
		{
			md5_transform(ctx->state, &input[i]);
			i += 64;
		}
		index = 0;
	}
	else
		i = 0;
	md5_memcpy((t_pointer)&ctx->buffer[index],
			(t_pointer)&input[i], i_len - i);
}

void	md5_final(unsigned char digest[16], t_md5 *context)
{
	unsigned char	bits[8];
	unsigned int	index;
	unsigned int	pad_len;
	unsigned char	padding[64];

	ft_bzero(padding, sizeof(unsigned char) * 64);
	*padding = 0x80;
	md5_encode(bits, context->count, 8);
	index = (unsigned int)((context->count[0] >> 3) & 0x3f);
	pad_len = (index < 56) ? (56 - index) : (120 - index);
	md5_update(context, padding, pad_len);
	md5_update(context, bits, 8);
	md5_encode(digest, context->state, 16);
	md5_memset((t_pointer)context, 0, sizeof(*context));
}
