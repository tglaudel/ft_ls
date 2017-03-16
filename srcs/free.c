/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 16:54:52 by tglaudel          #+#    #+#             */
/*   Updated: 2017/03/16 17:03:16 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		free_list(t_elem *elem)
{
	t_elem *tmp;

	while (elem)
	{
		tmp = elem->next;
		if (elem->data->path)
			ft_strdel(&elem->data->path);
		if (elem->data->name)
			ft_strdel(&elem->data->name);
		if (elem->data->path_parent)
			ft_strdel(&elem->data->path_parent);
		if (elem->data->time)
			ft_strdel(&elem->data->time);
		if (elem->data->perm)
			ft_strdel(&elem->data->perm);
		free(elem->data);
		free(elem);
		elem = NULL;
		elem = tmp;
	}
}
