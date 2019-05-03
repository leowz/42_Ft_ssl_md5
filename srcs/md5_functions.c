/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:43:35 by zweng             #+#    #+#             */
/*   Updated: 2019/04/05 12:18:28 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

UINT4	f(UINT4 x, UINT4 y, UINT4 z)
{
	return ((x & y) | ((~x) & z));
}

UINT4	g(UINT4 x, UINT4 y, UINT4 z)
{
	return ((x & y) | (x & (~z)));
}

UINT4	h(UINT4 x, UINT4 y, UINT4 z)
{
	return (x ^ y ^ z);
}

UINT4	i(UINT4 x, UINT4 y, UINT4 z)
{
	return ((x ^ y) | (~z));
}

UINT4	rotate_left(UINT4 x, int n)
{
	return ((x << n) | (x >> (32 - n)));
}
