/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 16:54:52 by tglaudel          #+#    #+#             */
/*   Updated: 2016/06/02 14:26:55 by tglaudel         ###   ########.fr       */
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
		free(elem);
		elem = NULL;
		elem = tmp;
	}
}
