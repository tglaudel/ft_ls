/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 13:39:50 by tglaudel          #+#    #+#             */
/*   Updated: 2017/03/16 18:39:04 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void init_env(t_env *e)
{
	e->opt = 0;
	e->elem_start = NULL;
}

int main(int ac, char **av)
{
	int		offset;
	t_env	e;

	init_env(&e);
	e.opt = get_opt(av, &offset);
	e.elem_start = get_args(&av[offset], ac - offset, e.opt);
	loop_elem(e.elem_start, e.opt);
	push_in_buf("", 1);
	return (0);
}
