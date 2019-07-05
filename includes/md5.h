/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:39:20 by zweng             #+#    #+#             */
/*   Updated: 2019/06/14 16:18:08 by zweng            ###   ########.fr       */
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

typedef unsigned char	*POINTER;
typedef unsigned int	UINT4;
typedef struct
{
  UINT4					count[2];
  UINT4					state[4];
  unsigned char			buffer[64];
}						MD5_CTX;

void						md5(int argc, char **argv);
void						md5_init(MD5_CTX *);
void						md5_update(MD5_CTX *,
							unsigned char *, unsigned int);
void						md5_transform(UINT4 state[4],
							unsigned char block[64]);
void						md5_final(unsigned char [16], MD5_CTX *);

void						md5_encode(unsigned char *output,
							UINT4 *input, unsigned int len);
void						md5_decode(UINT4 *output,
							unsigned char *input, unsigned int len);
void						md5_memcpy(POINTER output, POINTER input,
							unsigned int len);
void						md5_memset(POINTER output, int value,
							unsigned int len);
void						md5_print(unsigned char digest[16]);

UINT4						f(UINT4 x, UINT4 y, UINT4 z);
UINT4						g(UINT4 x, UINT4 y, UINT4 z);
UINT4						h(UINT4 x, UINT4 y, UINT4 z);
UINT4						i(UINT4 x, UINT4 y, UINT4 z);
UINT4						rotate_left(UINT4 x, int n);
void						ff(UINT4 *abcd, UINT4 x, int s, UINT4 ac);
void						gg(UINT4 *abcd, UINT4 x, int s, UINT4 ac);
void						hh(UINT4 *abcd, UINT4 x, int s, UINT4 ac);
void						ii(UINT4 *abcd, UINT4 x, int s, UINT4 ac);
#endif
