/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 01:23:32 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/03 16:51:17 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"\

char	*add_interpretation(char *dir, char *new_path)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(dir, "..", 3) && ft_strncmp(dir, ".", 2))
	{
		new_path = add_char(new_path, '/');
		tmp = new_path;
		new_path = ft_strjoin(new_path, dir);
		free(tmp);
	}
	else if (!ft_strncmp(dir, "..", 3))
	{
		tmp = new_path;
		new_path = ft_substr(new_path, 0, ft_strlen(new_path) - \
			ft_strlen(ft_strrchr(new_path, '/')));
		free(tmp);
	}
	return (new_path);
}

char	*path_interpreter(char *path)
{
	char	**dir;
	char	*new_path;
	char	*tmp;
	int		i;

	i = 0;
	dir = ft_split(path, '/');
	new_path = ft_strdup("");
	while (dir[i])
	{
		new_path = add_interpretation(dir[i], new_path);
		free(dir[i]);
		i++;
	}
	if (!new_path[0])
		new_path = add_char(new_path, '/');
	free(dir);
	free(path);
	return (new_path);
}

char	*add_cwd(char *oldpath)
{
	char *pfx;
	char *tmp;
	char *path;

	path = ft_strjoin("/", oldpath);
	pfx = getcwd(NULL, 0);
	tmp = path;
	path = ft_strjoin(pfx, path);
	free(tmp);
	free(pfx);
	return (path);
}

char	*new_path(t_data *index, char *oldpath)
{
	char	*path;
	char	*tmp;

	if (ft_strchr(oldpath, ' '))
		return (ft_strdup(oldpath));
	else if (oldpath && !oldpath[0])
		return (getcwd(NULL, 0));
	else if (oldpath && oldpath[0] != '/')
		path = add_cwd(oldpath);
	else if (!oldpath || oldpath[0] == '~')
	{
		tmp = path;
		path = ft_strjoin(index->home, oldpath);
		free(tmp);
	}
	else
		path = ft_strdup(oldpath);
	return (path_interpreter(path));
}
