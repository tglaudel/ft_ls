/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 11:48:36 by tglaudel          #+#    #+#             */
/*   Updated: 2017/03/17 15:19:19 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	push_in_buf(char *s, int force_print)
{
	static char	buf[BUF_SIZE];
	static int	pos;
	int			n;

	n = -1;
	if (force_print == 1)
	{
		write(1, buf, pos + 1);
		pos = 0;
		ft_bzero(buf, BUF_SIZE);
		return ;
	}
	while (s[++n] != '\0')
	{
		if (pos == BUF_SIZE - 1)
		{
			write(1, buf, BUF_SIZE);
			pos = 0;
			ft_bzero(buf, BUF_SIZE);
		}
		buf[pos++] = s[n];
	}
}

void	print_elem(t_elem *elem, t_max *max, int opt)
{
	char	*link;

	if (have_opt('l', opt))
		print_opt_l(elem, max);
	push_in_buf(elem->data->name, 0);
	if (have_opt('l', opt) && S_ISLNK(elem->data->stat.st_mode))
	{
		link = ft_strnew(255);
		readlink(elem->data->path, link, 255);
		push_in_buf(" -> ", 0);
		push_in_buf(link, 0);
		ft_strdel(&link);
	}
	push_in_buf("\n", 0);
}

void	print_total(int total)
{
	char *tmp;

	tmp = NULL;
	push_in_buf("total ", 0);
	push_in_buf((tmp = ft_itoa(total)), 0);
	ft_strdel(&tmp);
	push_in_buf("\n", 0);
}

void	print_list_elem(t_elem *start, int opt, int total)
{
	static int	first = 0;
	t_elem		*tmp;
	t_max		max;

	tmp = start;
	if (start->data->path_parent && first == 1)
	{
		push_in_buf("\n", 0);
		push_in_buf(start->data->path_parent, 0);
		push_in_buf(":\n", 0);
	}
	if (have_opt('l', opt) && tmp->next->next != NULL)
		print_total(total);
	initialize_max(&max, start, opt);
	while (tmp)
	{
		if ((have_opt('a', opt) && tmp->data->name[0] == '.')
			|| tmp->data->name[0] != '.')
			print_elem(tmp, &max, opt);
		tmp = tmp->next;
	}
	first = 1;
}
