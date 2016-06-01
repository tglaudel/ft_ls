/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:21:52 by tglaudel          #+#    #+#             */
/*   Updated: 2016/06/01 14:45:54 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_elem		*get_args(char **av, int ac)
{
	int		i;
	t_stat	stat;
	t_elem	*list;
	t_elem	*error;

	list = NULL;
	error = NULL;
	i = -1;
	while (av[++i])
	{
		if (stat(av[i], &stat) == -1)
			add_elem(error, new_elem(NULL, av[i], NULL));
		else
			add_elem(list, new_elem(stat, av[i], NULL));
	}
	print_error_lst(error);
	return (list);
}
