/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossuin <agossuin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:30:24 by agossuin          #+#    #+#             */
/*   Updated: 2020/04/09 16:30:26 by agossuin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** i+=2 for the ">>".
** Gets path to the file from minidup.
** Open a file in append mode.
** If a file was previously opened, close this file.
*/

void	ft_get_append(t_cmd *cmd)
{
	int		tmp;
	char	*path;

	cmd->i += 2;
	path = ft_minidup(cmd);
	if (!(tmp = open(path, O_CREAT | O_WRONLY | O_APPEND, 0b0110100100)))
	{
		cmd->error = path;
		cmd->exit_status = errno;
	}
	else
	{
		if (cmd->fd_output != 1 && cmd->fd_output != 0 && cmd->fd_output != tmp)
			close(cmd->fd_output);
		cmd->fd_output = 0;
		if (cmd->fd_append != 0)
			close(cmd->fd_append);
		cmd->fd_append = tmp;
	}
}

/*
** i+=1 for the ">".
** Gets path to the file from minidup.
** Open a file in truncate mode.
** If a file was previously opened, close this file.
*/

void	ft_get_output(t_cmd *cmd)
{
	int		tmp;
	char	*path;

	cmd->i += 1;
	path = ft_minidup(cmd);
	if (!(tmp = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0b0110100100)))
	{
		cmd->error = path;
		cmd->exit_status = errno;
	}
	else
	{
		if (cmd->fd_output != 1 && cmd->fd_output != 0)
			close(cmd->fd_output);
		if (cmd->fd_append != 0)
		{
			close(cmd->fd_append);
			cmd->fd_append = 0;
		}
		cmd->fd_output = tmp;
	}
}

/*
** i+=1 for the "<".
** Opens a file in reading mode.
*/

void	ft_get_input(t_cmd *cmd)
{
	char	*path;

	cmd->i += 1;
	path = ft_minidup(cmd);
	if (!(cmd->fd_input = open(path, O_RDONLY)))
	{
		cmd->error = path;
		cmd->exit_status = errno;
	}
}

/*
** Gets the type of redir.
*/

void	ft_get_redir(t_cmd *cmd)
{
	if (cmd->line[cmd->i] == '>' && cmd->line[cmd->i + 1] == '>')
		ft_get_append(cmd);
	else if (cmd->line[cmd->i] == '>')
		ft_get_output(cmd);
	else if (cmd->line[cmd->i] == '<')
		ft_get_input(cmd);
}
