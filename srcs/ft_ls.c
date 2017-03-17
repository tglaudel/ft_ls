/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 16:35:30 by tglaudel          #+#    #+#             */
/*   Updated: 2017/03/17 15:14:58 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*create_path(char *path, char *name)
{
	char *new_path;
	char *tmp;

	tmp = ft_strjoin(path, "/");
	new_path = ft_strjoin(tmp, name);
	ft_strdel(&tmp);
	return (new_path);
}

int		is_dot_directory(t_elem *elem)
{
	if (ft_strcmp(elem->data->name, ".") == 0
		|| ft_strcmp(elem->data->name, "..") == 0)
		return (1);
	return (0);
}

void	loop_dir(t_elem *elem, int opt, int total)
{
	struct dirent	*dir;
	t_elem			*list;
	t_elem			*error;
	t_stat			st;
	char			*p;

	list = NULL;
	error = NULL;
	if ((elem->data->rep = opendir(elem->data->path)) == NULL)
		print_error(elem->data->path);
	while (elem->data->rep != NULL && (dir = readdir(elem->data->rep)) != NULL)
	{
		p = create_path(elem->data->path, dir->d_name);
		lstat(p, &st) == -1 ? add_error(&error, new_elem(st, dir->d_name, p,
			elem->data->path)) : (total += add_elem(&list, new_elem(st,
			dir->d_name, p, elem->data->path), opt));
	}
	elem->data->rep == NULL ? 0 : closedir(elem->data->rep);
	list == NULL ? 0 : print_list_elem(list, opt, total);
	error == NULL ? 0 : print_error_lst(error);
	if (have_opt('R', opt) && list != NULL)
		recurse_loop(list, opt);
	free_list(list);
}

void	recurse_loop(t_elem *start, int opt)
{
	t_elem *elem;

	elem = start;
	while (elem)
	{
		if (S_ISDIR(elem->data->stat.st_mode) && !is_dot_directory(elem))
		{
			if (have_opt('a', opt) || elem->data->name[0] != '.')
				loop_dir(elem, opt, 0);
		}
		elem = elem->next;
	}
}

void	loop_elem(t_elem *start, int opt)
{
	t_elem	*elem;
	t_max	max;

	elem = start;
	while (elem)
	{
		if (S_ISDIR(elem->data->stat.st_mode))
			loop_dir(elem, opt, 0);
		else
		{
			max.size = biggest_elem_size(start, opt);
			max.pid = biggest_elem_pid(start, opt);
			max.gid = biggest_elem_gid(start, opt);
			max.link = biggest_elem_link(start, opt);
			print_elem(elem, &max, opt);
		}
		elem = elem->next;
	}
}
