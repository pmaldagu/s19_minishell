/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossuin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 22:59:09 by agossuin          #+#    #+#             */
/*   Updated: 2019/08/14 11:15:23 by agossuin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
