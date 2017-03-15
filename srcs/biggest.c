/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biggest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 18:17:43 by tglaudel          #+#    #+#             */
/*   Updated: 2017/03/15 18:40:40 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int count_large(int n)
{
	int len;

	len = 0;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int		biggest_elem_size(t_elem *start)
{
	t_elem	*tmp;
	int		n;
	int		len;

	n = 0;
	tmp = start;
	while (tmp)
	{
		if ((len = count_large(tmp->data->stat.st_size)) > n)
			n = len;
		tmp = tmp->next;
	}
	return (n);
}

int		biggest_elem_pid(t_elem *start)
{
	t_elem	*tmp;
	int		n;
	int		len;

	n = 0;
	tmp = start;
	while (tmp)
	{
		if ((len = ft_strlen(tmp->data->pwuid->pw_name)) > n)
			n = len;
		tmp = tmp->next;
	}
	return (n);
}

int		biggest_elem_gid(t_elem *start)
{
	t_elem	*tmp;
	int		n;
	int		len;

	n = 0;
	tmp = start;
	while (tmp)
	{
		if ((len = ft_strlen(tmp->data->grgid->gr_name)) > n)
			n = len;
		tmp = tmp->next;
	}
	return (n);
}

int		biggest_elem_link(t_elem *start)
{
	t_elem	*tmp;
	int		n;
	int		len;

	n = 0;
	tmp = start;
	while (tmp)
	{
		if ((len = count_large(tmp->data->stat.st_size)) > n)
			n = len;
		tmp = tmp->next;
	}
	return (n);
}
