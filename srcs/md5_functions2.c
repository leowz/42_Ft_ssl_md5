/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:23:28 by zweng             #+#    #+#             */
/*   Updated: 2019/09/18 21:09:35 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static void	rotate_register(t_uint4 regis[4])
{
	t_uint4	tmp;

	tmp = regis[3];
	regis[3] = regis[2];
	regis[2] = regis[1];
	regis[1] = regis[0];
	regis[0] = tmp;
}

void		ff(t_uint4 *abcd, t_uint4 x, int s, t_uint4 ac)
{
	abcd[0] += f(abcd[1], abcd[2], abcd[3]) + x + ac;
	abcd[0] = rotate_left(abcd[0], s);
	abcd[0] += abcd[1];
	rotate_register(abcd);
}

void		gg(t_uint4 *abcd, t_uint4 x, int s, t_uint4 ac)
{
	abcd[0] += g(abcd[1], abcd[2], abcd[3]) + x + ac;
	abcd[0] = rotate_left(abcd[0], s);
	abcd[0] += abcd[1];
	rotate_register(abcd);
}

void		hh(t_uint4 *abcd, t_uint4 x, int s, t_uint4 ac)
{
	abcd[0] += h(abcd[1], abcd[2], abcd[3]) + x + ac;
	abcd[0] = rotate_left(abcd[0], s);
	abcd[0] += abcd[1];
	rotate_register(abcd);
}

void		ii(t_uint4 *abcd, t_uint4 x, int s, t_uint4 ac)
{
	abcd[0] += i(abcd[1], abcd[2], abcd[3]) + x + ac;
	abcd[0] = rotate_left(abcd[0], s);
	abcd[0] += abcd[1];
	rotate_register(abcd);
}
