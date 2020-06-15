/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 15:30:58 by pmaldagu          #+#    #+#             */
/*   Updated: 2020/03/25 15:02:38 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_env(char *line, char **envp)
{
	int i;
	size_t j;
	char *keyword;

	i = 1;
	while (ft_isalpha(line[i]))
	{
		ft_toupper(line[i]);
		i++;
	}
	keyword = ft_substr(line, 1, i - 1);
	i = 0;
	while (ft_strncmp(keyword, envp[i], ft_strlen(keyword)))
		i++;
	j = ft_strlen(keyword) + 1;
	write(1, &envp[i][j], ft_strlen(&envp[i][j]));
	return (j);
}

int	ft_echo(char *line, char **envp)
{
	int i;
	char a;

	i = 4;
	a = '\n';
	if (line[i] && ft_isalpha(line[i]))
		return (no_cmd(line));
	while (line[i] == 32)
		i++;
	while (line[i] && line[i] != '|')
	{
		if (!(ft_strncmp(&line[i], "-n ", 3)))
		{
			a = '\r';
			i += 2;
		}
		if (line[i] == '$')
			i += echo_env(&line[i], envp);
		write(0, &line[i], 1);
		i++;
	}
	write(0, &a, 1);
	return (1);
}
