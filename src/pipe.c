/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:48:23 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/05 17:22:54 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		daddy_do(t_data *index, int fd[2])
{
	int stdinfd;

	close(fd[1]);
	dup2(fd[0], 0);
	free_t_list(&index->cmd);
	if (!command_line(index))
	{
		index->end_pipe = 1;
		free_t_list(&index->cmd);
		close(fd[0]);
		return (0);
	}
	close(fd[0]);
	return (1);
}

int		child_do(t_data *index, int fd[2])
{
	index->child++;
	close(fd[0]);
	if (index->fd_out > 1)
		dup2(fd[1], index->fd_out);
	else
		dup2(fd[1], 1);
	ft_command(index);
	close(fd[1]);
	exit(0);
}

int		pipe_loop(t_data *index)
{
	int fd[2];
	int id;

	index->child = 1;
	while (index->tokens && index->last_ope[0] == '|')
	{
		if (pipe(fd) == -1)
			return (0);
		id = fork();
		if (id == 0)
		{
			if (!child_do(index, fd))
				return (0);
		}
		else
		{
			if (!daddy_do(index, fd))
				return (0);
		}
	}
	return (1);
}
