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

char	*creat_last_cmd(t_data *index, t_list *last, char *cmd, int *i)
{
	char	*var;

	var = ft_strdup("");
	cmd = (char *)last->content;
	while (cmd[(*i)])
	{
		if ((!ft_isalpha(cmd[0]) && cmd[0] != '_') || \
			ft_strchr(" @\'\"\\$&|;!", cmd[(*i)]))
		{
			(*i) = 0;
			break ;
		}
		else if (cmd[(*i)] == '=')
			break ;
		var = add_char(var, cmd[(*i)]);
		(*i)++;
	}
	return (var);
}

int		last_cmd(t_data *index)
{
	char	*cmd;
	char	*var;
	t_list	*last;
	int		i;

	last = index->cmd;
	i = 0;
	while (last && last->next)
		last = last->next;
	if (!ft_strncmp((char *)index->cmd->content, "export", 7))
	{
		cmd = (char *)last->content;
		var = creat_last_cmd(index, last, cmd, &i);
	}
	else
		var = ft_strdup("");
	if (i != 0 && var && var[0])
		cmd = ft_strjoin("_=", var);
	else
		cmd = ft_strjoin("_=", (char *)last->content);
	free(var);
	mod_env(index, cmd, 1);
	free(cmd);
	return (1);
}
