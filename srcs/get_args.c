/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:21:52 by tglaudel          #+#    #+#             */
/*   Updated: 2017/03/15 16:16:39 by tglaudel         ###   ########.fr       */
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

t_elem		*get_args(char **av, int ac, int opt)
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
		if (lstat(av[i], &st) == -1)
			add_elem(&error, new_elem(st, av[i], av[i], NULL), opt);
		else
			add_elem(&list, new_elem(st, av[i], av[i], NULL), opt);
	}
	if (ac == 0)
	{
		if (lstat(".", &st) == -1)
			ft_errors("heuu.. comment dire", 1, 0);
		add_elem(&list, new_elem(st, ".", ".", NULL), opt);
	}
	print_error_lst(sort_all(error));
	return (list);
}
