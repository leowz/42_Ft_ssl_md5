/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:40:27 by zweng             #+#    #+#             */
/*   Updated: 2019/09/18 21:11:15 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const t_uint4 g_k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
	0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
	0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
	0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
	0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
	0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
	0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
	0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

t_uint4		sha256_ch(t_uint4 x, t_uint4 y, t_uint4 z)
{
	return ((x & y) ^ ((~x) & z));
}

static void	processing(t_uint4 *regi, t_uint4 *w, int t)
{
	t_uint4	temp1;
	t_uint4	temp2;

	temp1 = regi[7] + sha256_bsig1(regi[4])
		+ sha256_ch(regi[4], regi[5], regi[6]) + g_k[t] + w[t];
	temp2 = sha256_bsig0(regi[0]) + sha256_maj(regi[0], regi[1], regi[2]);
	regi[7] = regi[6];
	regi[6] = regi[5];
	regi[5] = regi[4];
	regi[4] = regi[3] + temp1;
	regi[3] = regi[2];
	regi[2] = regi[1];
	regi[1] = regi[0];
	regi[0] = temp1 + temp2;
}

static void	output_result(t_uint4 *state, t_uint4 *regi)
{
	state[0] += regi[0];
	state[1] += regi[1];
	state[2] += regi[2];
	state[3] += regi[3];
	state[4] += regi[4];
	state[5] += regi[5];
	state[6] += regi[6];
	state[7] += regi[7];
}

void		sha256_transform(t_uint4 state[8], unsigned char block[64])
{
	int			t;
	t_uint4		w[64];
	t_uint4		regi[8];

	sha256_decode(w, block, 64);
	t = 16;
	while (t < 64)
	{
		w[t] = sha256_ssig1(w[t - 2]) + w[t - 7]
			+ sha256_ssig0(w[t - 15]) + w[t - 16];
		t++;
	}
	ft_memcpy((void *)regi, (void *)state, sizeof(t_uint4) * 8);
	t = 0;
	while (t < 64)
	{
		processing(regi, w, t);
		t++;
	}
	output_result(state, regi);
}
