/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 15:18:39 by tglaudel          #+#    #+#             */
/*   Updated: 2017/03/17 16:10:03 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	puts_larg(int n, char *s, int max)
{
	int len;

	len = s == NULL ? count_large(n) : ft_strlen(s);
	while (len < max)
	{
		push_in_buf(" ", 0);
		len++;
	}
}

static void	print_size(t_elem *elem, t_max *max)
{
	char *tmp;

	tmp = NULL;
	push_in_buf("  ", 0);
	puts_larg(elem->data->stat.st_size, NULL, max->size);
	if ((elem->data->perm[0] == 'b') || (elem->data->perm[0] == 'c'))
	{
		push_in_buf((tmp = ft_itoa(MAJOR(elem->data->stat.st_rdev))), 0);
		ft_strdel(&tmp);
		push_in_buf(", ", 0);
		push_in_buf((tmp = ft_itoa(MINOR(elem->data->stat.st_rdev))), 0);
	}
	else
		push_in_buf((tmp = ft_itoa(elem->data->stat.st_size)), 0);
	ft_strdel(&tmp);
}

static void	print_time(t_elem *elem)
{
	char	**tmp;
	char	*tmp2;
	int		n;

	n = -1;
	tmp = NULL;
	tmp2 = NULL;
	push_in_buf(" ", 0);
	if ((time(NULL) - (elem->data->stat.st_mtime)) > 15548400 \
		|| (elem->data->stat.st_mtime) > (time(NULL)))
	{
		tmp = ft_strsplit(ctime(&elem->data->stat.st_mtime), ' ');
		push_in_buf(tmp[1], 0);
		push_in_buf("  ", 0);
		push_in_buf(tmp[2], 0);
		push_in_buf("  ", 0);
		push_in_buf((tmp2 = ft_strtrim(tmp[4])), 0);
		ft_strdel(&tmp2);
		while (tmp[++n] != NULL)
			ft_strdel(&tmp[n]);
		free(tmp);
	}
	else
		push_in_buf(elem->data->time, 0);
	push_in_buf(" ", 0);
}

void		print_opt_l(t_elem *elem, t_max *max)
{
	char *tmp;

	tmp = NULL;
	push_in_buf(elem->data->perm, 0);
	push_in_buf("  ", 0);
	puts_larg(elem->data->stat.st_nlink, NULL, max->link);
	push_in_buf((tmp = ft_itoa(elem->data->stat.st_nlink)), 0);
	ft_strdel(&tmp);
	push_in_buf(" ", 0);
	puts_larg(0, elem->data->pwuid->pw_name, max->pid);
	push_in_buf(elem->data->pwuid->pw_name, 0);
	push_in_buf("  ", 0);
	puts_larg(0, elem->data->grgid->gr_name, max->gid);
	push_in_buf(elem->data->grgid->gr_name, 0);
	print_size(elem, max);
	print_time(elem);
}
