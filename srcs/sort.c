/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 15:01:16 by tglaudel          #+#    #+#             */
/*   Updated: 2017/03/15 16:19:43 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int			sort_lexico(t_elem *e1, t_elem *e2, int opt)
{
	if (have_opt('r', opt))
		return (ft_strcmp(e1->data->name, e2->data->name) < 0);
	return (ft_strcmp(e1->data->name, e2->data->name) > 0);
}

static int			sort_time(t_elem *e1, t_elem *e2, int opt)
{
	if (e1->data->stat.st_ctime == e2->data->stat.st_ctime)
		return (sort_lexico(e1, e2, opt));
	if (have_opt('r', opt))
		return (e1->data->stat.st_ctime > e2->data->stat.st_ctime);
	return (e1->data->stat.st_ctime < e2->data->stat.st_ctime);
}

static int			sort_size(t_elem *e1, t_elem *e2, int opt)
{
	if (e1->data->stat.st_size == e2->data->stat.st_size)
		return (sort_lexico(e1, e2, opt));
	if (have_opt('r', opt))
		return (e1->data->stat.st_size > e2->data->stat.st_size);
	return (e1->data->stat.st_size < e2->data->stat.st_size);
}

int					sort_function(t_elem *e1, t_elem *e2, int opt)
{
	if (have_opt('t', opt))
		return (sort_time(e1, e2, opt));
	else if (have_opt('S', opt))
		return (sort_size(e1, e2, opt));
	else
		return (sort_lexico(e1, e2, opt));
}

t_elem				*sort_all(t_elem *start)
{
	t_elem *elem;
	t_data *data;

	elem = start;
	while (elem && elem->next)
	{
		if (ft_strcmp(elem->data->name, elem->next->data->name) > 0)
		{
			data = elem->next->data;
			elem->next->data = elem->data;
			elem->data = data;
			elem = start;
		}
		else
			elem = elem->next;
	}
	return (start);
}
