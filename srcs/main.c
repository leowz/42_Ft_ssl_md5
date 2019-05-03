/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:28:19 by zweng             #+#    #+#             */
/*   Updated: 2019/04/03 11:58:21 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*void		error_log(const char *name, const char *msg)
{
	if (name && msg)
		ft_dprintf(STDERR_FILENO, "ft_ssl: %s: %s\n", name, msg);
}*/

static void	command_tips(void)
{
	ft_printf("Standard commands:\n\n");
	ft_printf("Message Digest commands:\n");
	ft_printf("md5\n");
	ft_printf("sha256\n");
	ft_printf("\n");
	ft_printf("Cipher commands:\n");
}

static void	usage(void)
{
	ft_printf("usage: ft_ssl command [command opts] [command args]\n");
}

int			main(int ac, char **av)
{
	if (ac > 1)
	{
		if (ft_strcmp(av[1], "md5") == 0)
			md5(ac, av);
		else if (ft_strcmp(av[1], "sha256") == 0)
			;
		else
		{
			ft_dprintf(STDERR_FILENO,
					"ft_ssl: Error: %s is an invalid command\n", av[1]);
			ft_printf("\n");
			command_tips();			
		}
	}
	else
		usage();
	return (0);
}