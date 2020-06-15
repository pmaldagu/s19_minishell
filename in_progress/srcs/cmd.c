/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossuin <agossuin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:29:37 by agossuin          #+#    #+#             */
/*   Updated: 2020/04/09 16:51:13 by agossuin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Echo the arguments.
** 'test' is used to place spaces between the arguments.
** If "ECHO", write endl. Else is "ECHON".
*/

void		ft_echo(t_cmd *cmd, int fd)
{
	int		test;
	t_list	*args_cpy;

	test = 0;
	args_cpy = cmd->args;
	while (args_cpy)
	{
		if (test)
			write(fd, " ", 1);
		test = 1;
		ft_putstr_fd(args_cpy->content, fd);
		args_cpy = args_cpy->next;
	}
	if (cmd->cmd == ECHO)
		write(fd, "\n", 1);
}

/*
** Change directory.
** If we have '~' or no arguments, we first go to 'home' dirsctory.
** If failed chdir -> errno.
** Sets the 'OLDPWD' env variable.
*/

void		ft_cd(t_cmd *cmd, int res)
{
	char	*oldpwd;
	char	*home;
	char	tmp[600];

	getcwd(tmp, 600);
	oldpwd = ft_strjoin("OLDPWD=", tmp);
	if (!(cmd->args) || (cmd->args && ((char*)cmd->args->content)[0] == '~'))
	{
		home = ft_vardup("HOME", cmd->env, 4);
		chdir(home);
		free(home);
		if (cmd->args && chdir(&((char*)cmd->args->content)[2]) != 0)
			res = 1;
	}
	else if (chdir(cmd->args->content) != 0)
		res = 1;
	if (res == 1)
	{
		chdir(tmp);
		cmd->error = ft_strjoin("cd: ", cmd->args->content);
		cmd->exit_status = errno;
		ft_var_to_lst(cmd->env, oldpwd);
	}
	free(oldpwd);
}

/*
** Gets the 'pwd'. I can't remember why I didnt use the 'getcwd', but I think
** there is a reason.
*/

void		ft_pwd(t_cmd *cmd, int fd)
{
	t_list	*tmpenv;

	tmpenv = cmd->env;
	while (tmpenv)
	{
		if (tmpenv->content && !ft_strncmp(tmpenv->content, "PWD=", 4))
			return (ft_putendl_fd(&(((char*)tmpenv->content)[4]), fd));
		tmpenv = tmpenv->next;
	}
}

/*
** 3 possible cases:
**     1) export hello=john. -> to var, then to env.
**     2) export hello (hello i already in vars). -> from var to env.
**     2) export hello (hello is nowhere). -> nothing is done.
**
** The arguments for export were set in 'cmd->args'.
** 'cmd->vars' are the variables that are not in the general env.
*/

void		ft_export(t_cmd *cmd)
{
	t_list			*tmpvars;
	t_list			*tmpargs;
	unsigned int	size;

	tmpargs = cmd->args;
	while (tmpargs)
	{
		if (ft_isvar(tmpargs->content))
			ft_get_var(cmd);
		size = ft_strlen((char*)tmpargs->content);
		tmpvars = cmd->vars;
		while (tmpvars)
		{
			if (tmpvars->content && !ft_strncmp(tmpvars->content,
				tmpargs->content, size)
				&& ((char*)tmpvars->content)[size] == '=')
				ft_var_to_lst(cmd->env, tmpvars->content);
			tmpvars = tmpvars->next;
		}
		tmpargs = tmpargs->next;
	}
}

/*
** Takes the arguments away from a 't_list'.
*/

void		ft_unset_from(t_list *list, t_cmd *cmd)
{
	t_list			*args;
	unsigned int	size;

	args = cmd->args;
	while (args)
	{
		size = ft_strlen((char*)args->content);
		while (list)
		{
			if (list->content && !ft_strncmp(list->content, args->content, size)
				&& ((char*)list->content)[size] == '=')
			{
				free(list->content);
				list->content = NULL;
			}
			list = list->next;
		}
		args = args->next;
	}
}

/*
** Takes the arguments away from the 'cmd->env' and from the 'cmd->vars'.
*/

void		ft_unset(t_cmd *cmd)
{
	ft_unset_from(cmd->vars, cmd);
	ft_unset_from(cmd->env, cmd);
}
