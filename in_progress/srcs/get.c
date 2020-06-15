/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossuin <agossuin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:29:25 by agossuin          #+#    #+#             */
/*   Updated: 2020/04/09 16:45:35 by agossuin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** We get to this with exec or ./ .
*/

void	ft_get_exe(t_cmd *cmd)
{
	cmd->cmd = EXEC;
}

/*
** Our line is something like "hello=john".
** We add this variable to the 'cmd->vars'.
**
** OKAY I THINK I FUCKED UP. THIS FUNCTION IS PROBABLY ONLY WORKING WHEN THE
** VARIABLE IS AT THE BEGINNING OF THE LINE. OTHERWISE IT SHOULD WORK FINE.
*/

void	ft_get_var(t_cmd *cmd)
{
	int		i;
	char	*var;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (cmd->line[i] && cmd->line[i] != '=')
		i++;
	tmp = ft_substr(&(cmd->line[cmd->i]), 0, i + 1);
	cmd->i += i + 1;
	tmp2 = ft_minidup(cmd);
	var = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	ft_var_to_lst(cmd->vars, var);
	free(var);
}

/*
** Gets ECHO or ECHON.
*/

void	ft_get_echo(t_cmd *cmd)
{
	cmd->cmd = ECHO;
	while (cmd->line[cmd->i] && ft_isspace(cmd->line[cmd->i]))
		cmd->i++;
	if (!ft_strncmp(&(cmd->line[cmd->i]), "-n", 2)
		&& ft_isspace(cmd->line[cmd->i + 2]))
	{
		cmd->cmd = ECHON;
		cmd->i += 2;
	}
}

/*
** Gets the command index from the line we dupped.
** If we found nothing, sets the error to command not found.
*/

void	ft_get_cmd(t_cmd *cmd)
{
	char	*command;

	command = ft_minidup(cmd);
	if (!ft_strncmp(command, "exec", 5))
		cmd->cmd = EXEC;
	else if (!ft_strncmp(command, "echo", 5))
		ft_get_echo(cmd);
	else if (!ft_strncmp(command, "cd", 3))
		cmd->cmd = CD;
	else if (!ft_strncmp(command, "env", 4))
		cmd->cmd = ENV;
	else if (!ft_strncmp(command, "pwd", 4))
		cmd->cmd = PWD;
	else if (!ft_strncmp(command, "export", 7))
		cmd->cmd = EXPORT;
	else if (!ft_strncmp(command, "unset", 6))
		cmd->cmd = UNSET;
	else if (!ft_strncmp(command, "exit", 5))
		cmd->cmd = EXIT;
	else if (!cmd->exit_status && (cmd->cmd = ERROR))
	{
		cmd->exit_status = COMMAND_NOT_FOUND;
		cmd->error = ft_strdup(command);
	}
	free(command);
}

/*
** Stocks the arguments we met.
*/

void	ft_get_arg(t_cmd *cmd)
{
	char *var;

	var = ft_minidup(cmd);
	ft_lstadd_back(&(cmd->args), ft_lstnew((void*)ft_strdup(var)));
	free(var);
}
