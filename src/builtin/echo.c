/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:52:16 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/05 16:14:09 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		option_n(char *token)
{
	int		i;

	i = 1;
	while (token[i])
	{
		if (token[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

char	*echo_token(char *out, t_list *tmp)
{
	char *dup;

	while (tmp)
	{
		if (!out)
			out = ft_strdup((char *)tmp->content);
		else
		{
			dup = out;
			out = ft_strjoin(out, (char *)tmp->content);
			free(dup);
		}
		if (tmp->next)
		{
			dup = out;
			out = ft_strjoin(out, " ");
			free(dup);
		}
		tmp = tmp->next;
	}
	return (out);
}

int		ft_echo(t_data *index)
{
	t_list	*tmp;
	int		option;
	char	*out;
	char	*join;

	tmp = index->cmd->next;
	option = 0;
	out = NULL;
	index->statut = 0;
	while (tmp && ((char *)tmp->content)[0] == '-' \
			&& option_n((char *)tmp->content))
	{
		option = 1;
		tmp = tmp->next;
	}
	out = echo_token(out, tmp);
	if (!option)
	{
		join = out;
		out = ft_strjoin(out, "\n");
		free(join);
	}
	ft_putstr_fd(out, 1);
	free(out);
	return (1);
}
