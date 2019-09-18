/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:43:46 by zweng             #+#    #+#             */
/*   Updated: 2019/09/18 21:11:25 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

void	sha256_encode(unsigned char *output, t_uint4 *input, unsigned int len)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[j] = (unsigned char)((input[i] >> 24) & 0xff);
		output[j + 1] = (unsigned char)((input[i] >> 16) & 0xff);
		output[j + 2] = (unsigned char)((input[i] >> 8) & 0xff);
		output[j + 3] = (unsigned char)((input[i]) & 0xff);
		i++;
		j += 4;
	}
}

void	sha256_decode(t_uint4 *output, unsigned char *input, unsigned int len)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[i] = ((t_uint4)input[j]) << 24 | (((t_uint4)input[j + 1]) << 16)
			| (((t_uint4)input[j + 2]) << 8) | (((t_uint4)input[j + 3]) << 0);
		i++;
		j += 4;
	}
}

void	sha_print(unsigned char digest[32])
{
	unsigned int i;

	i = 0;
	while (i < 32)
	{
		ft_printf("%02x", digest[i]);
		i++;
	}
}
