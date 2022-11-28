/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:32:24 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/01/29 10:32:26 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	eof_error(char *cmd, int error)
{
	char	*to_match;

	to_match = ft_strjoin("unexpected EOF while looking for matching `", cmd);
	ft_putstr_fd(to_match, 2);
	ft_putendl_fd("\'", 2);
	free(to_match);
	return (error);
}

int	print_identifier_error(char *arg, int error)
{
	char	*identifier;

	identifier = ft_strjoin("`", arg);
	ft_putstr_fd(identifier, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	free(identifier);
	return (error);
}

int	print_syntax_error(char *cmd, int error)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd("'", 2);
	return (error);
}

int	print_global_error(int error, char *msg)
{
	if (msg && error != 13 && error != 2)
		ft_putendl_fd(msg, 2);
	if (error == 13)
		ft_putendl_fd("Permission denied", 2);
	else if (error == 2)
		ft_putendl_fd("No such file or directory", 2);
	return (error);
}

int	ft_error_u(char *cmd, char *arg, int error, char *msg)
{
	if (!cmd || (cmd && ft_strncmp(cmd, "env", 4)))
		ft_putstr_fd("minishell: ", 2);
	if (cmd && ft_strchr("><;|", cmd[0]))
		return (print_syntax_error(cmd, error));
	if (cmd && ft_strchr("\'\"", cmd[0]))
		return (eof_error(cmd, error));
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg && !ft_strncmp(msg, "not a valid identifier", 23))
		return (print_identifier_error(arg, error));
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	return (print_global_error(error, msg));
}
