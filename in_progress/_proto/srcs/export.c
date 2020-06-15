/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 15:11:14 by pmaldagu          #+#    #+#             */
/*   Updated: 2020/04/03 20:04:27 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_export(char *line, char **envp)///totalement faux
{
	char *lastl;
	int i;
	int j;

	i = 0;
	j = 6;
	while (envp[i])
		i++;
	i -= 1;
	lastl = envp[i];
	while (line[j] == 32)
		j++;
	envp[i] = ft_strdup(&line[j]);
	i++;
	envp[i] = lastl;
	return (0);
}
