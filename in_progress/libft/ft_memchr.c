/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossuin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:16:03 by agossuin          #+#    #+#             */
/*   Updated: 2019/10/07 12:16:53 by agossuin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
