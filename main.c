/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 14:08:44 by pmaldagu          #+#    #+#             */
/*   Updated: 2020/03/25 09:40:49 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char *line;
	t_data pars;

	pars.path = NULL;
	while (1)
	{
		ft_acces(&pars);
		//write(0, "> ", 2);
		while(get_next_line(0, &line) != 1)
		{		
		}
		if (ft_pars(line, &pars) == 7)
			return (0);
		//printf("cmd = %d\n", ft_pars(line));
	}
	return (0);
}
