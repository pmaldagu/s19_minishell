/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 18:53:58 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/01/28 21:03:47 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_errcd(t_data *index, t_list *tmp)
{
	char	*home;

	home = get_var_value(index, "HOME");
	if (!tmp && !home[0])
	{
		index->statut = ft_error_u("cd", NULL, 1, "HOME not set");
		free(home);
		return (1);
	}
	else if (tmp && tmp->next)
	{
		index->statut = ft_error_u("cd", NULL, 1, "too many arguments");
		free(home);
		return (1);
	}
	free(home);
	return (0);
}

int	set_oldpwd(t_data *index, char *pwd, char *path)
{
	char	*newpwd;
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", pwd);
	mod_env(index, oldpwd, 6);
	free(oldpwd);
	oldpwd = NULL;
	newpwd = ft_strjoin("PWD=", path);
	mod_env(index, newpwd, 3);
	free(newpwd);
	newpwd = NULL;
	return (1);
}

int	ft_cd(t_data *index)
{
	t_list	*tmp;
	char	*path;
	char	*pwd;
	char	*buf;

	tmp = index->cmd->next;
	if (ft_errcd(index, tmp))
		return (0);
	if (!tmp)
		path = get_var_value(index, "HOME");
	else
		path = new_path(index, (char *)tmp->content);
	pwd = get_var_value(index, "PWD");
	if (chdir(path) == 0)
		set_oldpwd(index, pwd, path);
	else
		index->statut = ft_error_u("cd", (char *)tmp->content, errno, NULL);
	free(pwd);
	free(path);
	return (1);
}
