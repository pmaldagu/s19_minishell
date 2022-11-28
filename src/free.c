/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:36:25 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/03 15:30:51 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		free_tab(char ***tab)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = (*tab);
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	(*tab) = NULL;
	return (1);
}

int		free_t_list(t_list **list)
{
	t_list	*tmp;
	t_list	*first;

	first = (*list);
	while (first)
	{
		free(first->content);
		first->content = NULL;
		tmp = first;
		first = first->next;
		free(tmp);
	}
	(*list) = NULL;
	return (1);
}

int		free_t_data(t_data *index)
{
	free_t_list(&index->tokens);
	free_t_list(&index->cmd);
	free_t_list(&index->mnsh_env);
}
