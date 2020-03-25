/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 14:08:44 by pmaldagu          #+#    #+#             */
/*   Updated: 2020/03/25 13:41:23 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void banner(void)
{
	char *banner;

	banner = "\n                                                                       ____                         \n      .'. .`.       | |..          | |             ..'''' |         | |            |        |       \n    .'   `   `.     | |  ``..      | |          .''       |_________| |______      |        |       \n  .'           `.   | |      ``..  | |       ..'          |         | |            |        |       \n.'               `. | |          ``| | ....''             |         | |___________ |_______ |_______\n\n";
	write(1, banner, ft_strlen(banner));
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
