/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:44:43 by zweng             #+#    #+#             */
/*   Updated: 2019/09/18 21:10:00 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static void	round_1(t_uint4 *abcd, t_uint4 *x)
{
	ff(abcd, x[0], S11, 0xd76aa478);
	ff(abcd, x[1], S12, 0xe8c7b756);
	ff(abcd, x[2], S13, 0x242070db);
	ff(abcd, x[3], S14, 0xc1bdceee);
	ff(abcd, x[4], S11, 0xf57c0faf);
	ff(abcd, x[5], S12, 0x4787c62a);
	ff(abcd, x[6], S13, 0xa8304613);
	ff(abcd, x[7], S14, 0xfd469501);
	ff(abcd, x[8], S11, 0x698098d8);
	ff(abcd, x[9], S12, 0x8b44f7af);
	ff(abcd, x[10], S13, 0xffff5bb1);
	ff(abcd, x[11], S14, 0x895cd7be);
	ff(abcd, x[12], S11, 0x6b901122);
	ff(abcd, x[13], S12, 0xfd987193);
	ff(abcd, x[14], S13, 0xa679438e);
	ff(abcd, x[15], S14, 0x49b40821);
}

static void	round_2(t_uint4 *abcd, t_uint4 *x)
{
	gg(abcd, x[1], S21, 0xf61e2562);
	gg(abcd, x[6], S22, 0xc040b340);
	gg(abcd, x[11], S23, 0x265e5a51);
	gg(abcd, x[0], S24, 0xe9b6c7aa);
	gg(abcd, x[5], S21, 0xd62f105d);
	gg(abcd, x[10], S22, 0x2441453);
	gg(abcd, x[15], S23, 0xd8a1e681);
	gg(abcd, x[4], S24, 0xe7d3fbc8);
	gg(abcd, x[9], S21, 0x21e1cde6);
	gg(abcd, x[14], S22, 0xc33707d6);
	gg(abcd, x[3], S23, 0xf4d50d87);
	gg(abcd, x[8], S24, 0x455a14ed);
	gg(abcd, x[13], S21, 0xa9e3e905);
	gg(abcd, x[2], S22, 0xfcefa3f8);
	gg(abcd, x[7], S23, 0x676f02d9);
	gg(abcd, x[12], S24, 0x8d2a4c8a);
}

static void	round_3(t_uint4 *abcd, t_uint4 *x)
{
	hh(abcd, x[5], S31, 0xfffa3942);
	hh(abcd, x[8], S32, 0x8771f681);
	hh(abcd, x[11], S33, 0x6d9d6122);
	hh(abcd, x[14], S34, 0xfde5380c);
	hh(abcd, x[1], S31, 0xa4beea44);
	hh(abcd, x[4], S32, 0x4bdecfa9);
	hh(abcd, x[7], S33, 0xf6bb4b60);
	hh(abcd, x[10], S34, 0xbebfbc70);
	hh(abcd, x[13], S31, 0x289b7ec6);
	hh(abcd, x[0], S32, 0xeaa127fa);
	hh(abcd, x[3], S33, 0xd4ef3085);
	hh(abcd, x[6], S34, 0x4881d05);
	hh(abcd, x[9], S31, 0xd9d4d039);
	hh(abcd, x[12], S32, 0xe6db99e5);
	hh(abcd, x[15], S33, 0x1fa27cf8);
	hh(abcd, x[2], S34, 0xc4ac5665);
}

static void	round_4(t_uint4 *abcd, t_uint4 *x)
{
	ii(abcd, x[0], S41, 0xf4292244);
	ii(abcd, x[7], S42, 0x432aff97);
	ii(abcd, x[14], S43, 0xab9423a7);
	ii(abcd, x[5], S44, 0xfc93a039);
	ii(abcd, x[12], S41, 0x655b59c3);
	ii(abcd, x[3], S42, 0x8f0ccc92);
	ii(abcd, x[10], S43, 0xffeff47d);
	ii(abcd, x[1], S44, 0x85845dd1);
	ii(abcd, x[8], S41, 0x6fa87e4f);
	ii(abcd, x[15], S42, 0xfe2ce6e0);
	ii(abcd, x[6], S43, 0xa3014314);
	ii(abcd, x[13], S44, 0x4e0811a1);
	ii(abcd, x[4], S41, 0xf7537e82);
	ii(abcd, x[11], S42, 0xbd3af235);
	ii(abcd, x[2], S43, 0x2ad7d2bb);
	ii(abcd, x[9], S44, 0xeb86d391);
}

void		md5_transform(t_uint4 state[4], unsigned char block[64])
{
	t_uint4 x[16];
	t_uint4 abcd[4];

	abcd[0] = state[0];
	abcd[1] = state[1];
	abcd[2] = state[2];
	abcd[3] = state[3];
	md5_decode(x, block, 64);
	round_1(abcd, x);
	round_2(abcd, x);
	round_3(abcd, x);
	round_4(abcd, x);
	state[0] += abcd[0];
	state[1] += abcd[1];
	state[2] += abcd[2];
	state[3] += abcd[3];
	md5_memset((t_pointer)x, 0, sizeof(x));
}
