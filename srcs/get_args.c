/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:21:52 by tglaudel          #+#    #+#             */
/*   Updated: 2016/06/02 16:17:56 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void print_error_lst(t_elem *error)
{
	t_elem *elem;

	elem = error;
	while (elem)
	{
		ft_printf("ft_ls: %s: No such file or directory\n", elem->data->name);
		elem = elem->next;
	}
	free_list(error);
}

t_elem		*get_args(char **av, int ac)
{
	int		i;
	t_stat	st;
	t_elem	*list;
	t_elem	*error;

	list = NULL;
	error = NULL;
	i = -1;
	while (av[++i])
	{
		if (stat(av[i], &st) == -1)
			add_elem(&error, new_elem(st, av[i], av[i], NULL));
		else
			add_elem(&list, new_elem(st, av[i], av[i], NULL));
	}
	if (ac == 0)
	{
		if (stat(".", &st) == -1)
			ft_errors("heuu.. comment dire", 1, 0);
		add_elem(&list, new_elem(st, ".", ".", NULL));
	}
	print_error_lst(sort_lexico(error));
	return (list);
}
