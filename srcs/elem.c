/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:30:57 by tglaudel          #+#    #+#             */
/*   Updated: 2017/03/17 15:36:34 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*get_permission(t_stat stat)
{
	char	*perm;

	perm = ft_strnew(10);
	perm[0] = '-';
	perm[0] = (S_ISDIR(stat.st_mode)) ? 'd' : perm[0];
	perm[0] = (S_ISFIFO(stat.st_mode)) ? 'p' : perm[0];
	perm[0] = (S_ISCHR(stat.st_mode)) ? 'c' : perm[0];
	perm[0] = (S_ISBLK(stat.st_mode)) ? 'b' : perm[0];
	perm[0] = (S_ISSOCK(stat.st_mode)) ? 's' : perm[0];
	perm[0] = (S_ISLNK(stat.st_mode)) ? 'l' : perm[0];
	perm[1] = stat.st_mode & S_IRUSR ? 'r' : '-';
	perm[2] = stat.st_mode & S_IWUSR ? 'w' : '-';
	perm[3] = stat.st_mode & S_IXUSR ? 'x' : '-';
	perm[4] = stat.st_mode & S_IRGRP ? 'r' : '-';
	perm[5] = stat.st_mode & S_IWGRP ? 'w' : '-';
	perm[6] = stat.st_mode & S_IXGRP ? 'x' : '-';
	perm[7] = stat.st_mode & S_IROTH ? 'r' : '-';
	perm[8] = stat.st_mode & S_IWOTH ? 'w' : '-';
	perm[9] = stat.st_mode & S_IXOTH ? 'x' : '-';
	return (perm);
}

static void	get_elem_information(t_elem *elem)
{
	elem->data->pwuid = getpwuid(elem->data->stat.st_uid);
	elem->data->grgid = getgrgid(elem->data->stat.st_gid);
	elem->data->time = ft_strsub(ctime(&elem->data->stat.st_ctime), 4, 12);
	elem->data->perm = get_permission(elem->data->stat);
}

int			add_elem(t_elem **start, t_elem *new, int opt)
{
	t_elem *elem;

	if ((elem = *start) == NULL || sort_function(elem, new, opt) > 0)
	{
		*start = new;
		new->next = elem;
	}
	else
		while (elem)
		{
			if (elem->next == NULL)
			{
				elem->next = new;
				break ;
			}
			else if (sort_function(elem->next, new, opt) > 0)
			{
				new->next = elem->next;
				elem->next = new;
				break ;
			}
			elem = elem->next;
		}
	return (new->data->perm[0] == 'l' ? 0 : new->data->stat.st_blocks);
}

void		add_error(t_elem **start, t_elem *new)
{
	t_elem *elem;

	if ((elem = *start) == NULL)
	{
		*start = new;
		new->next = elem;
	}
	else
		while (elem)
		{
			if (elem->next == NULL)
			{
				elem->next = new;
				break ;
			}
			elem = elem->next;
		}
}

t_elem		*new_elem(t_stat stat, char *name, char *path, char *path_parent)
{
	t_elem	*new;

	if ((new = (t_elem*)malloc(sizeof(t_elem))) == NULL)
		ft_errors("ERROR : Malloc new_elem failed.", 1, 0);
	if ((new->data = (t_data*)malloc(sizeof(t_data))) == NULL)
		ft_errors("ERROR : Malloc new_elem failed", 1, 0);
	new->data->name = ft_strdup(name);
	if (path)
		new->data->path = path;
	else
		new->data->path = NULL;
	if (path_parent)
		new->data->path_parent = ft_strdup(path_parent);
	else
		new->data->path_parent = NULL;
	new->data->stat = stat;
	path == NULL ? 0 : get_elem_information(new);
	new->next = NULL;
	return (new);
}
