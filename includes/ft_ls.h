/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 13:36:51 by tglaudel          #+#    #+#             */
/*   Updated: 2016/06/02 19:30:15 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include "../libft/includes/printf.h"
# include "../libft/includes/get_next_line.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/dir.h>

# define OPT_STRING "RrtalSsUc"

typedef struct stat t_stat;
typedef struct passwd t_psswd;
typedef struct group t_group;

typedef struct		s_data
{
	char			*name;
	char			*path;
	char			*path_parent;
	char			*time;
	char			*perm;
	t_stat			stat;
	DIR				*rep;
	t_psswd			*pwuid;
	t_group			*grgid;
}					t_data;

typedef struct		s_elem
{
	t_data			*data;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_env
{
	int				opt;
	t_elem			*elem_start;
}					t_env;

/*
** Opt :
*/

int					have_opt(char o, int opt);
int					get_opt(char **av, int *offset);

/*
** Sort :
*/

t_elem				*sort_function(t_elem *start, int opt);
t_elem				*sort_time(t_elem *start);
t_elem				*sort_lexico(t_elem *start);
int					sort_condition(t_elem *elem, t_elem *new, int opt);

/*
** Elem & args:
*/

void 				add_elem(t_elem **start, t_elem *new, int opt);
void				loop_elem(t_elem *start, int opt);
t_elem				*get_args(char **av, int ac, int opt);
void				recurse_loop(t_elem *start, int opt);
t_elem				*new_elem(t_stat stat, char *name, char *path, char *path_parent);

/*
** Print:
*/

void				print_error_lst(t_elem *error);
void				print_elem(t_elem *elem, int opt);
void				print_list_elem(t_elem *start, int opt);

/*
** free:
*/

void				free_list(t_elem *elem);

#endif
