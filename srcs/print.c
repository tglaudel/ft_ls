/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 11:48:36 by tglaudel          #+#    #+#             */
/*   Updated: 2017/03/15 19:18:13 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void push_in_buf(char *s, int force_print)
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

void print_opt_l(t_elem *elem, t_max *max, int opt)
{
	(void)opt;
	(void)max;
	push_in_buf(elem->data->perm, 0);
	push_in_buf(" ", 0);
	// puts_larg(elem->data->stat.st_nlink, );
	push_in_buf(ft_itoa(elem->data->stat.st_nlink), 0);
	push_in_buf(" ", 0);
	push_in_buf(elem->data->pwuid->pw_name, 0);
	push_in_buf(" ", 0);
	push_in_buf(elem->data->grgid->gr_name, 0);
	push_in_buf(" ", 0);
	push_in_buf(ft_itoa(elem->data->stat.st_size), 0);
	push_in_buf(" ", 0);
}

void	print_elem(t_elem *elem, t_max *max, int opt)
{
	if (have_opt('l', opt))
		print_opt_l(elem, max, opt);
	push_in_buf(elem->data->name, 0);
	push_in_buf("\n", 0);
}

void	print_list_elem(t_elem *start, int opt)
{
	t_elem		*tmp;
	t_max		max;

	tmp = start;
	if (start->data->path_parent)
		ft_printf("%s:\n", start->data->path_parent);
	max.size = biggest_elem_size(start);
	max.pid = biggest_elem_pid(start);
	max.gid = biggest_elem_gid(start);
	max.link = biggest_elem_link(start);
	// printf("size %d , pid %d , gid %d , link %d\n", max.size, max.pid, max.gid, max.link );
	while (tmp)
	{
		if ((have_opt('a', opt) && tmp->data->name[0] == '.')
			|| tmp->data->name[0] != '.')
			print_elem(tmp, &max, opt);
		tmp = tmp->next;
	}
}
