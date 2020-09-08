/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossuin <agossuin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:30:14 by agossuin          #+#    #+#             */
/*   Updated: 2020/09/08 16:57:53 by pmaldag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Free the args and reset all to the default values.
** Also sets the value of '$?' and 'PWD' (this is where i use the get_cwd).
*/

extern char *pwd;

void	ft_reset_cmd(t_cmd *cmd)
{
	char	*tmp;
	char	s[100];

	cmd->cmd = 0;
	ft_lstclear(&(cmd->args), free);
	cmd->args = NULL;
	if (cmd->fd_output != 0 && cmd->fd_output != 1)
		close(cmd->fd_output);
	cmd->fd_output = 1;
	if (cmd->fd_append != 0 && cmd->fd_append != 1)
		close(cmd->fd_append);
	cmd->fd_append = 0;
	if (cmd->fd_input != 0 && cmd->fd_input != 1)
		close(cmd->fd_input);
	cmd->fd_input = 0;
	tmp = ft_itoa(cmd->exit_status);
	ft_var_to_lst(cmd->vars, ft_strjoin("?=", tmp));
	free(tmp);
	cmd->exit_status = 0;
	free(cmd->error);
	cmd->error = NULL;
	getcwd(s, 100);
	tmp = ft_strjoin("PWD=", s);
	ft_var_to_lst(cmd->env, tmp);
	free(tmp);
}

/*
** Errors are in the errors fd : 2.
** 2 "manual errors", the other are automatics with `strerror(errno)`.
*/

void	ft_puterror(t_cmd *cmd)
{
	ft_putstr_fd(cmd->error, 2);
	ft_putstr_fd(": ", 2);
	if (cmd->exit_status == BAD_SUBSTITUTION)
		ft_putendl_fd("bad substition", 2);
	else if (cmd->exit_status == COMMAND_NOT_FOUND)
		ft_putendl_fd("command not found", 2);
	else
		ft_putendl_fd(strerror(cmd->exit_status), 2);
}

/*
** If fd_output is set to 0: we use fd_append.
** If exit status -> something went wrong -> ft_puterror.
** Ft_reset_cmd obviously resets the commands and free the arguments.
*/

void	apply_cmd(t_cmd *cmd)
{
	int		fd;

	fd = (cmd->fd_output) ? cmd->fd_output : cmd->fd_append;
	if (!cmd->exit_status)
	{
		// if (cmd->cmd == EXEC)
		// 	ft_exec(cmd);
		if (cmd->cmd == ECHO || cmd->cmd == ECHON)
			ft_echo(cmd, fd);
		else if (cmd->cmd == CD)
			ft_cd(cmd, 0);
		else if (cmd->cmd == ENV)
			ft_putenv(cmd->env, fd);
		else if (cmd->cmd == PWD)
			ft_pwd(cmd, fd);
		else if (cmd->cmd == EXPORT)
			ft_export(cmd);
		else if (cmd->cmd == UNSET)
			ft_unset(cmd);
		else if (cmd->cmd == EXIT)
			return ;
	}
	if (cmd->exit_status)
		ft_puterror(cmd);
	ft_reset_cmd(cmd);
}

/*
** Ft_parsing_cmd is recursive.
**
** Skips spaces.
** Check if it is the endl or if we should EXIT. -> return and apply command.
** Check if we have a ';' -> only apply command.
** Check if we don't stock a command yet and ispath. -> EXEC.
** Check if we don't stock a command yet and isvar. -> get_variables.
** Check if we don't stock a command yet and redir. -> get_redirection.
** Check if we don't stock a command yet. -> get_command.
** Else -> get_arguments.
*/

void	ft_parsing_cmd(t_cmd *cmd)
{
	while (ft_isspace(cmd->line[cmd->i]))
		cmd->i++;
	if (cmd->line[cmd->i] == '\0' || cmd->cmd == EXIT || cmd->line[cmd->i] == '#')
		return (apply_cmd(cmd));
	else if (cmd->line[cmd->i] == ';' && cmd->i++)
		apply_cmd(cmd);
	// else if (cmd->line[cmd->i] == '|')
	// {
	// 	ft_get_topipe(cmd);
	// 	apply_cmd(cmd);
	// 	ft_get_frompipe(cmd);
	// }
	else if (cmd->cmd == 0 && ft_ispath(&(cmd->line[cmd->i])))
		ft_get_exe(cmd);
	else if (cmd->cmd == 0 && ft_isvar(&(cmd->line[cmd->i])))
		ft_get_var(cmd);
	else if (cmd->line[cmd->i] == '<' || cmd->line[cmd->i] == '>')
		ft_get_redir(cmd);
	else if (cmd->cmd == 0)
		ft_get_cmd(cmd);
	else
		ft_get_arg(cmd);
	ft_parsing_cmd(cmd);
}

/*
** The prompt is 'name'. For example, it can be 'bash$'. (better in macro?)
** We are in a -pseudo infinite- loop with get_next_line.
** We leave the loop when the command is EXIT.
** Ft_pwd is actually a `ft_putendl_pwd`.
**
*/

void int_handler(int sig)
{
	//int *ret;
	char pwd[41];

	//*ret = 1;
	//ft_bzero(pwd, ft_strlen(pwd));
	//getcwd(pwd, 40);
	printf("pwd == %s", getcwd(pwd, 40));
	if (sig == SIGINT)
	{
		//getcwd(pwd, 40);
		//write(1, pwd, ft_strlen(pwd));
		//write(1, "\nokminishell $ ", 14);
		//return (ret);
	}
}

int		ft_prompt(char *name, t_cmd *cmd)
{
	//ft_pwd(cmd, 1);
	//ft_putstr_fd(name, 1);
	//signal(SIGINT, int_handler);
	while (1)
	{		
		if(!get_next_line(0, &(cmd->line)))
		{
			write(1, "exit", 4);
			break;
		}
		ft_parsing_cmd(cmd);
		// write(1, "\n", 1);
		if (cmd->cmd == EXIT)
			break ;
		ft_pwd(cmd, 1);
		ft_putstr_fd(name, 1);
		free(cmd->line);
		cmd->line = NULL;
		cmd->i = 0;
	}
	ft_reset_cmd(cmd);
	return (0);
}
