/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossuin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:42:09 by agossuin          #+#    #+#             */
/*   Updated: 2019/10/10 15:35:54 by agossuin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_megafree(char **tab, int y)
{
	while (--y >= 0)
		free(tab[y]);
	free(tab);
	return (NULL);
}

static int		ft_len_to_sep(char const *str, char c)
{
	int		i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

static int		ft_count_words(char const *str, char c)
{
	int count;
	int pos;

	count = 1;
	if (str[0] == c)
		count = 0;
	pos = 0;
	while (str[pos] && str[pos + 1])
	{
		if (str[pos] == c && str[pos + 1] != c)
			count++;
		pos++;
	}
	return (count);
}

static char		*ft_tmp_str(const char *str, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	if ((tmp = malloc(sizeof(char) * (ft_len_to_sep(str, c) + 1))) != 0)
	{
		while (str[i] != c && str[i] != '\0')
		{
			tmp[i] = str[i];
			i++;
		}
		tmp[i] = '\0';
		return (tmp);
	}
	return (NULL);
}

char			**ft_split(char const *str, char c)
{
	int		i;
	int		y;
	char	**split;

	i = 0;
	y = 0;
	if (str == NULL)
		return (NULL);
	if (!(split = malloc(sizeof(char *) * (ft_count_words(str, c) + 1))))
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			if (!(split[y] = ft_tmp_str(&str[i], c)))
				return (ft_megafree(split, y));
			i = i + ft_len_to_sep(&str[i], c);
			y++;
		}
		else if (str[i] == c)
			i++;
	}
	split[y] = NULL;
	return (split);
}
