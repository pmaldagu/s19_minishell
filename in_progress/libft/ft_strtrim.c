/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossuin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:33:59 by agossuin          #+#    #+#             */
/*   Updated: 2019/10/09 14:34:04 by agossuin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		char_in_set(char c, const char *set)
{
	while (set && *set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static int		ft_count_trim(const char *s1, const char *set)
{
	int		totrim;
	int		end;

	totrim = 0;
	end = ft_strlen(s1);
	while (char_in_set(s1[totrim], set))
		totrim++;
	if ((size_t)totrim == ft_strlen(s1))
		return (0);
	while (char_in_set(s1[--end], set))
		totrim++;
	return (ft_strlen(s1) - totrim);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		count;
	char	*new_s;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	count = ft_count_trim(s1, set);
	if (!(new_s = malloc(sizeof(char) * (count + 1))))
		return (NULL);
	while (char_in_set(*s1, set))
		s1++;
	while (i < count)
		new_s[i++] = *s1++;
	new_s[i] = '\0';
	return (new_s);
}
