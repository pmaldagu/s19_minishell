/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:47:56 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/05 17:26:02 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*in_path_dir2_return(t_data *index, char c, char *path)
{
	if (c == ':' && files_exist(index, path))
		return (ft_strdup(path));
	return (NULL);
}

char	*in_path_dir2(t_data *index, char *path, int i, char *value)
{
	char		*tmp;
	char		*dir;

	if (!value[i])
		return (ft_strdup(path));
	while (value[i])
	{
		dir = ft_strdup("");
		while (value[i] && value[i] != ':')
		{
			dir = add_char(dir, value[i]);
			i++;
		}
		tmp = check_dir(ft_strdup(dir), path);
		if (files_exist(index, tmp))
		{
			free(dir);
			return (tmp);
		}
		if (value[i])
			i++;
		free(dir);
		free(tmp);
	}
	return (in_path_dir2_return(index, value[i - 1], path));
}

int		can_exec(char *path)
{
	struct stat	statbuf;
	DIR			*dir;

	if (!path)
		return (0);
	dir = opendir(path);
	if (dir != 0 || errno == 13)
		return (0);
	stat(path, &statbuf);
	if (statbuf.st_mode & S_IXUSR)
		return (1);
	return (0);
}

int		fork_exec(t_data *index, char *path_exec)
{
	pid_t		ret;
	char		*line;

	line = NULL;
	ret = fork();
	if (ret == 0)
		execve(path_exec, lsttoa(index->cmd), lsttoa(index->mnsh_env));
	else
	{
		if (index->signum || index->end_pipe)
		{
			kill(ret, SIGKILL);
			index->signum = 0;
		}
		else
			wait(&ret);
	}
	index->statut = ret / 256;
	return (1);
}

int		exec(t_data *index)
{
	char		*path_exec;
	int			path;
	char		*value;

	path = 0;
	value = get_var_value(index, "PATH");
	if (ft_strchr((char *)index->cmd->content, '/'))
		path_exec = ft_strdup((char *)index->cmd->content);
	else
	{
		path_exec = in_path_dir2(index, (char *)index->cmd->content, 0, value);
		if (path_exec && ft_strchr(path_exec, '/'))
			path = can_exec(path_exec);
	}
	free(value);
	if (!path_exec)
		return (0);
	if (!path && ft_errexec(index, path_exec))
	{
		free(path_exec);
		return (1);
	}
	fork_exec(index, path_exec);
	free(path_exec);
	return (1);
}
