/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 15:30:58 by pmaldagu          #+#    #+#             */
/*   Updated: 2020/03/23 15:46:15 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char *line)
{
	int i;

	i = 4;
	if (line[i] && ft_isalpha(line[i]))
		return (no_cmd(line));
	while (line[i] == 32)
		i++;
	while (line[i] && line[i] != '|')
	{
		write(0, &line[i], 1);
		i++;
	}
	write(0, "\n", 1);
	return (1);
}
