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
	ft_printf("%s\n", elem->data->name);
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
