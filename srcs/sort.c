/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 15:01:16 by tglaudel          #+#    #+#             */
/*   Updated: 2016/06/02 19:32:05 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_elem			*sort_lexico(t_elem *start)
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

t_elem			*sort_time(t_elem *start)
{
	return (start);
}

t_elem			*sort_function(t_elem *start, int opt)
{
	if (have_opt('u', opt))
		return (start);
	else if (have_opt('t', opt))
		return (sort_time(start));
	else
		return (sort_lexico(start));
}
