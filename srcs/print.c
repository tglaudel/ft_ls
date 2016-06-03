/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 11:48:36 by tglaudel          #+#    #+#             */
/*   Updated: 2016/06/02 17:23:18 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_elem(t_elem *elem, int opt)
{
	(void)opt;
	if (have_opt('l', opt))
	{
		ft_printf("%s %d %s ", elem->data->perm, elem->data->stat.st_nlink, elem->data->pwuid->pw_name);
		ft_printf("%s %5d %s ", elem->data->grgid->gr_name, elem->data->stat.st_size, elem->data->time);
	}
	write(1, elem->data->name, ft_strlen(elem->data->name));
	write(1, "\n", 1);
}

void	print_list_elem(t_elem *start, int opt)
{
	t_elem *tmp;

	tmp = start;
	if (start->data->path_parent)
		ft_printf("%s:\n", start->data->path_parent);
	while (tmp)
	{
		print_elem(tmp, opt);
		tmp = tmp->next;
	}
	ft_putchar('\n');
}
