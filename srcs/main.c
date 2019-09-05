/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:28:19 by zweng             #+#    #+#             */
/*   Updated: 2019/09/05 17:33:51 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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

void hash(int ac, char **av, int index)
{
	int i;
	int	f; //  q=2, r=1, default=0
	void	(*string[2])(char *, int) = {md5_string, sha256_string};
	void	(*filter[2])(int) = {md5_filter, sha256_filter};
	void	(*file[2])(char *, int) = {md5_file, sha256_file};

	f = F_DEFAULT;
	if (ac > 2)
	{
		i = 1;
		while (++i < ac && !(f & F_FILE))
		{
			if (av[i][0] == '-' && av[i][1] == 's')
			{
				if (++i < ac)
				{
					f = f | F_STRING;
					(*string[index])(av[i], f);
				}
				else
					ft_printf("md5: option requires an argument -- s\n");
			}
			else if (av[i][0] == '-' && av[i][1] == 'q')
			{
				f = f | F_QUITE;
			}
			else if (av[i][0] == '-' && av[i][1] == 'r')
			{
				f = f | F_REVERSE;
			}
			else if (av[i][0] == '-' && av[i][1] == 'p')
			{
				f = f | F_P;
				(*filter[index])(f & F_P);
			}
			else if (av[i][0] == '-')
				ft_printf("md5: illegal option -- %c\n", av[i][1]);
			else
			{
				f = f | F_FILE;
				break ;
			}
		}
		if (!(f & F_P) && (!(f & F_STRING) && !(f & F_FILE)))
			(*filter[index])(f & F_P);
		while (i < ac)
			(*file[index])(av[i++], f);
	}
	else
		(*filter[index])(0);
}

int			main(int ac, char **av)
{
	if (ac > 1)
	{
		if (ft_strcmp(av[1], "md5") == 0)
			hash(ac, av, 0);
		else if (ft_strcmp(av[1], "sha256") == 0)
			hash(ac, av, 1);
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
