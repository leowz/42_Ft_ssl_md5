/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:13:47 by zweng             #+#    #+#             */
/*   Updated: 2019/09/18 21:10:16 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

void	md5_encode(unsigned char *output, t_uint4 *input, unsigned int len)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[j] = (unsigned char)(input[i] & 0xff);
		output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
		output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
		output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
		i++;
		j += 4;
	}
}

void	md5_decode(t_uint4 *output, unsigned char *input, unsigned int len)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[i] = ((t_uint4)input[j]) | (((t_uint4)input[j + 1]) << 8)
		| (((t_uint4)input[j + 2]) << 16) | (((t_uint4)input[j + 3]) << 24);
		i++;
		j += 4;
	}
}

void	md5_memcpy(t_pointer output, t_pointer input, unsigned int len)
{
	unsigned int i;

	i = 0;
	while (i < len)
	{
		output[i] = input[i];
		i++;
	}
}

void	md5_memset(t_pointer output, int value, unsigned int len)
{
	unsigned int i;

	i = 0;
	while (i < len)
	{
		((char *)output)[i] = (char)value;
		i++;
	}
}

void	md5_print(unsigned char digest[16])
{
	unsigned int i;

	i = 0;
	while (i < 16)
	{
		ft_printf("%02x", digest[i]);
		i++;
	}
}
