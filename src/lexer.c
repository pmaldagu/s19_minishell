/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <pmaldagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:46:18 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/05 16:47:32 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	lex_cmd_line(t_data *index, t_list *tmp)
{
	tmp = index->tokens;
	free(index->last_ope);
	index->last_ope = ft_strdup((char *)index->tokens->content);
	free(index->tokens->content);
	index->tokens = index->tokens->next;
	free(tmp);
}

int		command_line(t_data *index)
{
	t_list *tmp;

	free_t_list(&index->cmd);
	while (index->tokens && !ft_strchr(";|", \
		((char *)index->tokens->content)[0]))
	{
		ft_lstadd_back(&index->cmd, \
			ft_lstnew(ft_strdup((char *)index->tokens->content)));
		tmp = index->tokens;
		free(index->tokens->content);
		index->tokens = index->tokens->next;
		free(tmp);
	}
	if (index->tokens)
		lex_cmd_line(index, tmp);
	else
	{
		free(index->last_ope);
		index->last_ope = ft_strdup("");
	}
	if (ft_redirection(index) && ft_trad(index))
		return (1);
	return (0);
}

int		mainprocess(t_data *index, int stdoutcpy, int stdincpy)
{
	index->child = 0;
	if (!index->cmd)
	{
		if (!command_line(index))
			index->can_exe = 0;
	}
	if (index->last_ope[0] == '|' && !pipe_loop(index))
		return (0);
	if (index->can_exe)
		ft_command(index);
	dup2(stdoutcpy, 1);
	dup2(stdincpy, 0);
	last_cmd(index);
	return (1);
}

int		ft_free_lexer(t_data *index)
{
	free_t_list(&index->cmd);
	free(index->last_cmd);
	free(index->last_ope);
	return (0);
}

int		ft_lexer(t_data *index)
{
	int		stdoutcpy;
	int		stdincpy;

	stdoutcpy = dup(1);
	stdincpy = dup(0);
	if (ft_errope(index))
		return (0);
	index->can_exe = 1;
	index->last_ope = NULL;
	while (index->tokens)
	{
		index->fd_out = 1;
		index->fd_in = 0;
		index->end_pipe = 0;
		if (!mainprocess(index, stdoutcpy, stdincpy))
			return (ft_free_lexer(index));
		index->end_pipe = 1;
		index->can_exe = 1;
		free_t_list(&index->cmd);
	}
	free(index->last_ope);
	free_t_list(&index->tokens);
	free_t_list(&index->cmd);
	return (1);
}
