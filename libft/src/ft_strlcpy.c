/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edessain <edessain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:12:53 by edessain          #+#    #+#             */
/*   Updated: 2021/02/08 11:12:53 by edessain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;

	i = 0;
	if (dst == NULL || src == NULL)
		return (0);
	while (i + 1 < size && *src)
		dst[i++] = *src++;
	if (size != 0)
		dst[i] = '\0';
	return (ft_strlen(src - i));
}
