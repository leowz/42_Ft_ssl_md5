/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:29:17 by zweng             #+#    #+#             */
/*   Updated: 2019/04/03 17:23:03 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSH_H
# define FT_SSH_H

# include "libft.h"
# include "ft_printf.h"
# include "md5.h"
# include "sha.h"

int     xgetopt(int argc, char **argv, const char *optstring);
void	hash(int ac, char **av, int index);

char    *xoptarg;
int     xoptind;
int     xopterr;
	
#endif
