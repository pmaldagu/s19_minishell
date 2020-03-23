/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 14:15:12 by pmaldagu          #+#    #+#             */
/*   Updated: 2020/03/23 19:07:27 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_cmd(char *line)
{
	int i;

	i = 0;
	write (0, "minishell: command not found: ", 30);
	while (ft_isalpha(line[i]))
	{
		write(0, &line[i], 1);
		i++;
	}
	write (0, "\n", 1);
	return (0);
}

int	ft_pars(char *line, t_data *pars)
{
	int i;
	int j;

	i = 0;
	while (line[i] == 32)
		i++;
	j = i;
	while (ft_isalpha(line[j]))
	{
		line[j] = ft_tolower(line[j]);
		j++;
	}
	if (!(ft_strncmp(&line[i], "echo", 4)))
		return (ft_echo(&line[i]));
	else if (!(ft_strncmp(&line[i], "cd", 2)))
		return (ft_cd(&line[i], pars));
	else if (!(ft_strncmp(&line[i], "pwd", 3)))
		return (ft_pwd());
	else if (!(ft_strncmp(&line[i], "export", 6)))
		return (4);
	else if (!(ft_strncmp(&line[i], "unset", 5)))
		return (5);
	else if (!(ft_strncmp(&line[i], "env", 3)))
		return (6);
	else if (!(ft_strncmp(&line[i], "exit", 4)))
		return (7);
	else
		return (no_cmd(&line[i]));
}
