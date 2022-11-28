/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edessain <edessain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:12:22 by edessain          #+#    #+#             */
/*   Updated: 2021/02/08 11:12:23 by edessain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new_s;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	if (!(new_s = malloc((ft_strlen(s1) + 1) * sizeof(char))))
		return (NULL);
	while (s1 && *s1)
		new_s[i++] = *s1++;
	new_s[i] = '\0';
	return (new_s);
}
