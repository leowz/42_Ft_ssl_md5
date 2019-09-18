/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:43:35 by zweng             #+#    #+#             */
/*   Updated: 2019/09/18 21:09:48 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

t_uint4	f(t_uint4 x, t_uint4 y, t_uint4 z)
{
	return ((x & y) | ((~x) & z));
}

t_uint4	g(t_uint4 x, t_uint4 y, t_uint4 z)
{
	return ((x & z) | (y & (~z)));
}

t_uint4	h(t_uint4 x, t_uint4 y, t_uint4 z)
{
	return (x ^ y ^ z);
}

t_uint4	i(t_uint4 x, t_uint4 y, t_uint4 z)
{
	return (y ^ (x | (~z)));
}

t_uint4	rotate_left(t_uint4 x, int n)
{
	return ((x << n) | (x >> (32 - n)));
}
