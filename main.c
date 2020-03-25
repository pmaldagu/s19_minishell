/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 14:08:44 by pmaldagu          #+#    #+#             */
/*   Updated: 2020/03/25 16:24:01 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void logname(char **envp)
{
	int i;

	i = 0;
	while (ft_strncmp(envp[i], "LOGNAME", 7))
		i++;
	write(1, "\n[", 2);
	write(1, &envp[i][8], ft_strlen(&envp[i][8]));
	write(1, "] ", 2);
}

void banner(void)
{
	size_t i;
	size_t len;
	char *banner;
	char *sign;

	i = 0;
	len = 1;
	sign = "by pmaldagu";
	banner = "\n                                                                       ____                         \n      .'. .`.       | |..          | |             ..'''' |         | |            |        |       \n    .'   `   `.     | |  ``..      | |          .''       |_________| |______      |        |       \n  .'           `.   | |      ``..  | |       ..'          |         | |            |        |       \n.'               `. | |          ``| | ....''             |         | |___________ |_______ |_______\n";
	while (banner[len] != '\n')
		len++;
	len -= ft_strlen(sign) + 1;
	write(1, banner, ft_strlen(banner));
	while (i < len)
	{
		write(1, " ", 1);
		i++;
	}
	write(1, sign, ft_strlen(sign));
	write(1, "\n", 1);
}

int main(int argc, char **argv, char **envp)
{
	char *line;
	t_data pars;
	(void)argc;
	(void)argv;

	pars.path = NULL;
	banner();
	//printf("env = %s\n", envp[0]);
	while (1)
	{
		logname(envp);
		ft_acces(&pars);
		//write(0, "> ", 2);
		while(get_next_line(0, &line) != 1)
		{		
		}
		if (ft_pars(line, &pars, envp) == 7)
			return (0);
		//printf("cmd = %d\n", ft_pars(line));
	}
	return (0);
}
