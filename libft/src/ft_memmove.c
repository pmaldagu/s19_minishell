/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edessain <edessain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:11:08 by edessain          #+#    #+#             */
/*   Updated: 2021/02/08 11:11:10 by edessain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
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
