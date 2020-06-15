/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossuin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:13:54 by agossuin          #+#    #+#             */
/*   Updated: 2019/10/07 11:13:56 by agossuin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*tmp_dst;
	char	*tmp_src;

	tmp_dst = (char*)dst;
	tmp_src = (char*)src;
	if (src < dst)
	{
		i = len;
		while (i--)
			tmp_dst[i] = tmp_src[i];
	}
	else if (src > dst)
	{
		i = 0;
		while (i < len)
			tmp_dst[i++] = *tmp_src++;
	}
	return (dst);
}
