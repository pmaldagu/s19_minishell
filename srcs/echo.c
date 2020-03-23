/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 15:30:58 by pmaldagu          #+#    #+#             */
/*   Updated: 2020/03/23 18:03:50 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char *line)
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
		if (line[i] == '-' && line[i + 2] == 32)
		{
			if (!(ft_strncmp(&line[i], "-n", 2)))
			{
				a = '\r';
				i += 2;
			}
		}
		write(0, &line[i], 1);
		i++;
	}
	write(0, &a, 1);
	return (1);
}
