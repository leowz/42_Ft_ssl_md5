/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:23:28 by zweng             #+#    #+#             */
/*   Updated: 2019/05/22 12:37:14 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static void	rotate_register(UINT4 regis[4])
{
	UINT4	tmp;

	tmp = regis[3];
	regis[3] = regis[2];
	regis[2] = regis[1];
	regis[1] = regis[0];
	regis[0] = tmp;
}

void		ff(UINT4 *abcd, UINT4 x, int s, UINT4 ac)
{
	abcd[0] += f(abcd[1], abcd[2], abcd[3]) + x + ac;
	abcd[0] = rotate_left(abcd[0], s);
	abcd[0] += abcd[1];
	rotate_register(abcd);
}

void		gg(UINT4 *abcd, UINT4 x, int s, UINT4 ac)
{
	abcd[0] += g(abcd[1], abcd[2], abcd[3]) + x + ac;
	abcd[0] = rotate_left(abcd[0], s);
	abcd[0] += abcd[1];
	rotate_register(abcd);
}

void		hh(UINT4 *abcd, UINT4 x, int s, UINT4 ac)
{
	abcd[0] += h(abcd[1], abcd[2], abcd[3]) + x + ac;
	abcd[0] = rotate_left(abcd[0], s);
	abcd[0] += abcd[1];
	rotate_register(abcd);
}

void		ii(UINT4 *abcd, UINT4 x, int s, UINT4 ac)
{
	abcd[0] += i(abcd[1], abcd[2], abcd[3]) + x + ac;
	abcd[0] = rotate_left(abcd[0], s);
	abcd[0] += abcd[1];
	rotate_register(abcd);
}
