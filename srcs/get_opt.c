/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 11:13:48 by tglaudel          #+#    #+#             */
/*   Updated: 2016/06/01 14:05:51 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		add_opt(int pos, int opt)
{
	int		tmp;

	if (pos == -1)
		ft_errors("ERROR : Illegal option.", 1, 0);
	tmp = 1;
	tmp = tmp << pos;
	opt = opt | tmp;
	return (opt);
}

static int		position_in_opt(char o)
{
	int		i;

	i = -1;
	while (OPT_STRING[++i])
	{
		if (o == OPT_STRING[i])
			return (i);
	}
	return (-1);
}

int				have_opt(char o, int opt)
{
	int tmp;
	int i;

	tmp = 1;
	i = position_in_opt(o);
	tmp = tmp << i;
	if (tmp & opt)
		return (1);
	return (0);
}

int				get_opt(char **av, int *offset)
{
	int		opt;
	int		i;
	int		j;

	i = -1;
	opt = 0;
	while (av[++i])
	{
		j = 0;
		if (i != 0 && av[i][0] != '-')
			break ;
		if (av[i][0] == '-' && av[i][1] != '\0' && !ft_isdigit(av[i][1]))
			while (av[i][++j])
				opt = add_opt(position_in_opt(av[i][j]), opt);
	}
	*offset = i;
	return (opt);
}
