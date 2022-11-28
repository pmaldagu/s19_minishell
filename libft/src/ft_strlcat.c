/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edessain <edessain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:12:45 by edessain          #+#    #+#             */
/*   Updated: 2021/02/08 11:12:46 by edessain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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
