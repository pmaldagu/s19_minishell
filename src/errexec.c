/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errexec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:47:56 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/03 17:41:39 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_errexec(t_data *index, char *path)
{
	DIR			*dir;
	struct stat	statbuf;
	char		*check;
	int			error;

	check = path;
	dir = opendir(check);
	error = errno;
	if (dir != 0 || error == 13)
	{
		index->statut = ft_error_u(NULL, path, 126, "is a directory");
		closedir(dir);
	}
	else if ((stat(check, &statbuf) < 0))
		index->statut =
			ft_error_u(NULL, path, 127, "No such file or directory");
	else if (!(statbuf.st_mode & S_IXUSR && statbuf.st_mode & S_IRUSR))
		index->statut = ft_error_u(NULL, path, 126, "Permission denied");
	else
		return (0);
	return (1);
}

int		files_exist(t_data *index, char *path)
{
	DIR			*dir;
	struct stat	statbuf;
	char		*tmp;

	tmp = new_path(index, path);
	if ((stat(path, &statbuf)) >= 0 && !(dir = opendir(path)))
	{
		closedir(dir);
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

char	*check_dir(char *dir, char *path)
{
	char	*tmp;
	char	*path_dup;

	if (!dir[0])
	{
		free(dir);
		path_dup = ft_strdup(path);
		return (path_dup);
	}
	else
	{
		tmp = ft_strjoin(dir, "/");
		free(dir);
		dir = ft_strjoin(tmp, path);
		free(tmp);
		return (dir);
	}
}
