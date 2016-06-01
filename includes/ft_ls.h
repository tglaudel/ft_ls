/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 13:36:51 by tglaudel          #+#    #+#             */
/*   Updated: 2016/06/01 14:22:17 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include "../libft/includes/printf.h"
# include "../libft/includes/get_next_line.h"

# define OPT_STRING "Rrtalu"

typedef struct		s_data
{
	char			*name;
	char			*path;
	t_stat			stat;
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

#endif
