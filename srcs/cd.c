/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 18:44:23 by pmaldagu          #+#    #+#             */
/*   Updated: 2020/03/23 19:13:28 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wrong_path(char *line)
{
	write(0, "cd: no such file or directory: ", 31);
	write(0, line, ft_strlen(line));
	write(0, "\n", 1);
	return (1);
}

int	ft_cd(char *line, t_data *pars)
{
	int i;
	char *npath;

	i = 2;
	npath = NULL;
	while (line[i] == 32)
		i++;
	if (line[i] == '.')
		i++;
	if (ft_isalpha(line[i]))
		npath = ft_strjoin(pars->path, &line[i]);
	else if (line[i] == '/')
		npath = ft_strdup(&line[i]);
	if (npath == NULL)
		return (1);
	if (chdir(npath) < 0)
		return (wrong_path(&line[i]));
	else
		return (1);
}


