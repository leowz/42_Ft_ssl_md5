/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:39:57 by zweng             #+#    #+#             */
/*   Updated: 2019/09/18 21:11:04 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha.h"

t_uint4	sha256_maj(t_uint4 x, t_uint4 y, t_uint4 z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

t_uint4	sha256_bsig0(t_uint4 word)
{
	return ((word >> 2) | (word << 30))
	^ ((word >> 13) | (word << 19))
	^ ((word >> 22) | (word << 10));
}

t_uint4	sha256_bsig1(t_uint4 word)
{
	return ((word >> 6) | (word << 26))
	^ ((word >> 11) | (word << 21))
	^ ((word >> 25) | (word << 7));
}

t_uint4	sha256_ssig0(t_uint4 word)
{
	return ((word >> 7) | (word << 25))
	^ ((word >> 18) | (word << 14))
	^ (word >> 3);
}

t_uint4	sha256_ssig1(t_uint4 word)
{
	return ((word >> 17) | (word << 15))
	^ ((word >> 19) | (word << 13))
	^ (word >> 10);
}
