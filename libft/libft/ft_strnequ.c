/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 10:00:04 by tglaudel          #+#    #+#             */
/*   Updated: 2015/11/28 11:49:08 by tglaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (n == 0)
		return (1);
	if (s1 && s2)
	{
		while ((int)*s1 == (int)*s2)
		{
			n--;
			if (*s1 == '\0' || n == 0)
				return (1);
			s1++;
			s2++;
		}
	}
	return (0);
}
