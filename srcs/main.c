/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:26:59 by zweng             #+#    #+#             */
/*   Updated: 2019/09/18 21:07:20 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	g_f = F_DEFAULT;

static void	command_tips(void)
{
	ft_printf("Standard commands:\n\n");
	ft_printf("Message Digest commands:\n");
	ft_printf("md5\n");
	ft_printf("sha256\n");
	ft_printf("\n");
	ft_printf("Cipher commands:\n");
}

static void	save_line(int *i, int ac, char **av, int index)
{
	static void	(*string[2])(char *, int) = {md5_string, sha256_string};

	if (++(*i) < ac)
	{
		g_f = g_f | F_STRING;
		(*string[index])(av[*i], g_f);
	}
	else
		ft_printf("md5: option requires an argument -- s\n");
}

static int	handle_param(int *i, int ac, char **av, int index)
{
	static void	(*filter[2])(int) = {md5_filter, sha256_filter};

	if (av[*i][0] == '-' && av[*i][1] == 's')
		save_line(i, ac, av, index);
	else if (av[*i][0] == '-' && av[*i][1] == 'q')
		g_f = g_f | F_QUITE;
	else if (av[*i][0] == '-' && av[*i][1] == 'r')
		g_f = g_f | F_REVERSE;
	else if (av[*i][0] == '-' && av[*i][1] == 'p')
	{
		g_f = g_f | F_P;
		(*filter[index])(g_f & F_P);
	}
	else if (av[*i][0] == '-')
		ft_printf("md5: illegal option -- %c\n", av[*i][1]);
	else
	{
		g_f = g_f | F_FILE;
		return (FALSE);
	}
	return (TRUE);
}

void		hash(int ac, char **av, int index)
{
	int			i;
	static void	(*filter[2])(int) = {md5_filter, sha256_filter};
	static void	(*file[2])(char *, int) = {md5_file, sha256_file};

	if (ac > 2)
	{
		i = 1;
		while (++i < ac && !(g_f & F_FILE))
		{
			if (!handle_param(&i, ac, av, index))
				break ;
		}
		if (!(g_f & F_P) && (!(g_f & F_STRING) && !(g_f & F_FILE)))
			(*filter[index])(g_f & F_P);
		while (i < ac)
			(*file[index])(av[i++], g_f);
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
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}
