/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 13:39:50 by tglaudel          #+#    #+#             */
/*   Updated: 2016/06/01 14:19:22 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void init_env(t_env *e)
{
	e->opt = 0;
	data_start = NULL;
}

int main(int ac, char **av)
{
	int		offset;
	t_env	e;

	(void)ac;
	init(&e);
	e.opt = get_opt(av, &offset);
	e.elem_start = get_args(&av[offset], ac);
	ft_putnbr(offset);
	return (0);
}
