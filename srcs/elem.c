/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:30:57 by tglaudel          #+#    #+#             */
/*   Updated: 2016/06/02 14:29:40 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void add_elem(t_elem **start, t_elem *new)
{
	t_elem *elem;

	elem = *start;
	if (*start == NULL)
		*start = new;
	else
	{
		while (elem && elem->next)
			elem = elem->next;
		elem->next = new;
	}
}

t_elem		*new_elem(t_stat stat, char *name, char *path, char *path_parent)
{
	t_elem *new;

	if ((new = (t_elem*)malloc(sizeof(t_elem))) == NULL)
		ft_errors("ERROR : Malloc new_elem failed.", 1, 0);
	if ((new->data = (t_data*)malloc(sizeof(t_data))) == NULL)
		ft_errors("ERROR : Malloc new_elem failed", 1, 0);
	new->data->name = ft_strdup(name);
	if (path)
		new->data->path = ft_strdup(path);
	else
		new->data->path = NULL;
	if (path_parent)
		new->data->path_parent = ft_strdup(path_parent);
	else
		new->data->path_parent = NULL;
	new->data->stat = stat;
	new->next = NULL;
	return(new);
}
