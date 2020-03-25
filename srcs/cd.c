/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 18:44:23 by pmaldagu          #+#    #+#             */
/*   Updated: 2020/03/25 10:13:08 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wrong_path(char *line)
{
	write(1, "cd: no such file or directory: ", 31);
	write(1, line, ft_strlen(line));
	write(1, "\n", 1);
	return (1);
}

void	remove_dir(t_data *pars)
{
	int i;

	i = 0;
	while (pars->path[i])
		i++;
	while (pars->path[i] != '/')
		i--;
	while (pars->path[i])
	{
		pars->path[i] = 0;
		i++;
	}
	pars->path = ft_strdup(pars->path);
}

int	cd_back(char *line, t_data *pars)
{
	int i;

	i = 0;
	while (!(ft_strncmp(&line[i], "..", 2) || line[i] == '/'))
	{
		if (!(ft_strncmp(&line[i], "..", 2)))
		{
			remove_dir(pars);
			i += 3;
		}
		else if (line[i] == '/')
			i++;
	}
	return (i);
}

int	ft_cd(char *line, t_data *pars)
{
	int i;

	i = 2;
	while (line[i] == 32)
		i++;
	if (!(ft_strncmp(&line[i], "./", 2)))
		i += 2;
	else if (!(ft_strncmp(&line[i], "..", 2)))
		i += cd_back(&line[i], pars) + 1;
	if (ft_isalpha(line[i]))
	{
		pars->path = ft_strjoin(pars->path, "/");
		pars->path = ft_strjoin(pars->path, &line[i]);
	}
	else if (line[i] == '/')
		pars->path = ft_strdup(&line[i]);
	if (pars->path == NULL)
		return (1);
	if (chdir(pars->path) < 0)
		return (wrong_path(&line[i]));
	else
		return (1);
}


