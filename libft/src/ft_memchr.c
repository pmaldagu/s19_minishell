/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edessain <edessain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:10:43 by edessain          #+#    #+#             */
/*   Updated: 2021/02/08 11:10:44 by edessain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	char			*tmps;

	i = 0;
	tmps = 0;
	if (n != 0)
	{
		tmps = (char*)s;
		while (i < n && tmps[i])
		{
			if (tmps[i] == c)
				return (&tmps[i]);
			i++;
		}
		if (tmps[i] == c && tmps[i] == '\0')
			return (&tmps[i]);
	}
	return (NULL);
}
