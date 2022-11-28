/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:07:14 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/05 15:44:15 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_errunset(t_data *index, char *ident, int i)
{
	char	*tmp;

	if (!ident[0])
	{
		index->statut = ft_error_u("unset", ident, 1, "not a valid identifier");
		return (1);
	}
	while (ident[i])
	{
		if (ft_strchr(" =\\;&@|!$\"\'", ident[i]))
		{
			index->statut = \
				ft_error_u("unset", ident, 1, "not a valid identifier");
			return (1);
		}
		i++;
	}
	return (0);
}

int	unset_token(t_data *index, t_list *cmd, t_list *mod)
{
	int		i;
	t_list	*tmp;
	t_list	*previous;

	tmp = mod;
	i = 0;
	previous = tmp;
	while (!ft_errunset(index, (char *)cmd->content, 0) && tmp)
	{
		if (!ft_strncmp((char*)tmp->content, \
			cmd->content, ft_strlen(cmd->content)))
		{
			if (i == 0)
				index->mnsh_env = tmp->next;
			else
				previous->next = tmp->next;
			free(tmp->content);
			free(tmp);
			break ;
		}
		i++;
		previous = tmp;
		tmp = tmp->next;
	}
	return (1);
}

int	ft_unset(t_data *index)
{
	t_list	*cmd;

	if (index->child)
		return (0);
	cmd = index->cmd->next;
	while (cmd)
	{
		unset_token(index, cmd, index->mnsh_env);
		cmd = cmd->next;
	}
	return (1);
}
