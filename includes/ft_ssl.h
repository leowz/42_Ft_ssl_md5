/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:29:17 by zweng             #+#    #+#             */
/*   Updated: 2019/09/04 18:45:57 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSH_H
# define FT_SSH_H

# include "libft.h"
# include "ft_printf.h"
# include "md5.h"
# include "sha.h"

# define F_P		16
# define F_QUITE	8
# define F_FILE		4
# define F_REVERSE	2
# define F_STRING	1
# define F_DEFAULT	0

void	hash(int ac, char **av, int index);

void	md5_string (char *string, int flag);
void 	md5_file (char *filename, int flag);
void md5_filter(int repeat);
void sha256_string (char *string, int flag);
void sha256_file (char *filename, int flag);
void sha256_filter(int repeat);
	
#endif
