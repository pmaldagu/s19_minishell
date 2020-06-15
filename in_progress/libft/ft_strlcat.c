/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossuin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 21:34:24 by agossuin          #+#    #+#             */
/*   Updated: 2019/08/15 12:34:40 by agossuin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	l;
	int				test;

	i = 0;
	test = 0;
	l = size;
	if (size > ft_strlen(dest))
		l = ft_strlen(dest);
	while (l + 1 < size && src[i] && (test = 1))
		dest[l++] = src[i++];
	if (test == 1 && dest != NULL)
		dest[l] = 0;
	l += ft_strlen(&src[i]);
	return (l);
}
