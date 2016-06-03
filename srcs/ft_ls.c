/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 16:35:30 by tglaudel          #+#    #+#             */
/*   Updated: 2016/06/02 19:32:16 by tglaudel         ###   ########.fr       */
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
	if (ft_strcmp(elem->data->name, ".") == 0 || ft_strcmp(elem->data->name, "..") == 0)
		return (1);
	return (0);
}

void	loop_dir(t_elem *elem, int opt)
{
	struct dirent	*dir;
	t_elem			*list;
	t_elem			*error;
	t_stat			st;
	char			*p;

	list = NULL;
	error = NULL;
	if ((elem->data->rep = opendir(elem->data->path)) == NULL)
		return(ft_errors(elem->data->path, 0, 0));
	while ((dir = readdir(elem->data->rep)) != NULL)
	{
		p = create_path(elem->data->path, dir->d_name);
		if (lstat(p, &st) == -1)
			add_elem(&error, new_elem(st, dir->d_name, p, elem->data->path), opt);
		else
			add_elem(&list, new_elem(st, dir->d_name, p, elem->data->path), opt);
	}
	closedir(elem->data->rep);
	print_error_lst(error);
	print_list_elem(list, opt);
	if (have_opt('R', opt) && list != NULL)
		recurse_loop(list, opt);
	free_list(list);
}

void recurse_loop(t_elem *start, int opt)
{
	t_elem *elem;

	elem = start;
	while (elem)
	{
		if (S_ISDIR(elem->data->stat.st_mode) && !is_dot_directory(elem))
			loop_dir(elem, opt);
		elem = elem->next;
	}
}

void	loop_elem(t_elem *start, int opt)
{
	t_elem	*elem;

	elem = start;
	while (elem)
	{
		if (S_ISDIR(elem->data->stat.st_mode))
			loop_dir(elem, opt);
		else
			print_elem(elem, opt);
		elem = elem->next;
	}
}
