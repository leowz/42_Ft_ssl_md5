/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:39:20 by zweng             #+#    #+#             */
/*   Updated: 2019/03/26 12:24:08 by zweng            ###   ########.fr       */
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

typedef unsigned char		*POINTER;
typedef unsigned short int	UINT2;
typedef unsigned long int	UINT4;
typedef struct {
  UINT4						count[2];
  UINT4						state[4];
  unsigned char				buffer[64];
} MD5_CTX;

#endif
