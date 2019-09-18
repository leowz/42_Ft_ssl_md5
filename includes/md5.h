/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:39:20 by zweng             #+#    #+#             */
/*   Updated: 2019/09/18 21:02:25 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# define S11 7
# define S12 12
# define S13 17
# define S14 22
# define S21 5
# define S22 9
# define S23 14
# define S24 20
# define S31 4
# define S32 11
# define S33 16
# define S34 23
# define S41 6
# define S42 10
# define S43 15
# define S44 21

typedef unsigned char		*t_pointer;
typedef unsigned int		t_uint4;
typedef struct
{
	t_uint4					count[2];
	t_uint4					state[4];
	unsigned char			buffer[64];
}	t_md5;

void						md5(int argc, char **argv);
void						md5_init(t_md5 *ctx);
void						md5_update(t_md5 *ctx,
							unsigned char *str, unsigned int len);
void						md5_transform(t_uint4 state[4],
							unsigned char block[64]);
void						md5_final(unsigned char res[16], t_md5 *ctx);

void						md5_encode(unsigned char *output,
							t_uint4 *input, unsigned int len);
void						md5_decode(t_uint4 *output,
							unsigned char *input, unsigned int len);
void						md5_memcpy(t_pointer output, t_pointer input,
							unsigned int len);
void						md5_memset(t_pointer output, int value,
							unsigned int len);
void						md5_print(unsigned char digest[16]);

t_uint4						f(t_uint4 x, t_uint4 y, t_uint4 z);
t_uint4						g(t_uint4 x, t_uint4 y, t_uint4 z);
t_uint4						h(t_uint4 x, t_uint4 y, t_uint4 z);
t_uint4						i(t_uint4 x, t_uint4 y, t_uint4 z);
t_uint4						rotate_left(t_uint4 x, int n);
void						ff(t_uint4 *abcd, t_uint4 x, int s, t_uint4 ac);
void						gg(t_uint4 *abcd, t_uint4 x, int s, t_uint4 ac);
void						hh(t_uint4 *abcd, t_uint4 x, int s, t_uint4 ac);
void						ii(t_uint4 *abcd, t_uint4 x, int s, t_uint4 ac);
#endif
