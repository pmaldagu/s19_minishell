/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edessain <edessain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:14:50 by edessain          #+#    #+#             */
/*   Updated: 2021/02/08 11:14:52 by edessain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_strlen_endl(char const *s)
{
	int i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return (i);
}

int		ft_strchr_pos(const char *s, int c)
{
	int pos;

	pos = 0;
	while (s && s[pos])
	{
		if (s[pos] == c)
			return (pos);
		pos++;
	}
	if (s && s[pos] == c)
		return (pos);
	return (-1);
}

char	*ft_strjoin_to_eol(char *s1, char *buf)
{
	char	*tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(tab = malloc(ft_strlen_endl(s1) + ft_strlen_endl(buf) + 1)))
		return (NULL);
	while (s1 && s1[j])
		tab[i++] = s1[j++];
	while (buf && *buf && *buf != '\n')
		tab[i++] = *buf++;
	tab[i] = 0;
	free(s1);
	return (tab);
}

int		get_next_line(int fd, char **line)
{
	static char		buf[FOPEN_MAX][BUFFER_SIZE + 1];
	int				ret;
	int				i;

	if (BUFFER_SIZE < 1 || fd < 0 || fd > FOPEN_MAX || !line
					|| !(*line = ft_strjoin_to_eol(NULL, buf[fd])))
		return (-1);
	ret = 1;
	while (ft_strchr_pos(buf[fd], '\n') == -1 && ret && ret != -1)
	{
		ret = read(fd, buf[fd], BUFFER_SIZE);
		buf[fd][ret] = '\0';
		if (!(*line = ft_strjoin_to_eol(*line, buf[fd])))
			return (-1);
	}
	i = 0;
	ret = ft_strchr_pos(buf[fd], '\n') + 1;
	if (buf[fd][0] == 0)
		return (0);
	while (buf[fd][ret] != '\0' && ret)
		buf[fd][i++] = buf[fd][ret++];
	buf[fd][i] = 0;
	return (1);
}
