/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 11:48:36 by tglaudel          #+#    #+#             */
/*   Updated: 2017/03/16 19:28:05 by tglaudel         ###   ########.fr       */
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

void	puts_larg(int n, char *s, int max)
{
	int len;

	len = s == NULL ? count_large(n): ft_strlen(s);
	while (len < max)
	{
		push_in_buf(" ", 0);
		len++;
	}
}

void	print_opt_l(t_elem *elem, t_max *max, int opt)
{
	(void)opt;
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
	push_in_buf("  ", 0);
	puts_larg(elem->data->stat.st_size, NULL, max->size);
	push_in_buf((tmp = ft_itoa(elem->data->stat.st_size)), 0);
	ft_strdel(&tmp);
	push_in_buf(" ", 0);
	push_in_buf(elem->data->time, 0);
	push_in_buf(" ", 0);
}

void	print_elem(t_elem *elem, t_max *max, int opt)
{
	char	*link;

	if (have_opt('l', opt))
		print_opt_l(elem, max, opt);
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

void print_total(int total)
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
