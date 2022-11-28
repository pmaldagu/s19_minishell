/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 21:28:09 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/03 19:22:42 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*if_previous(t_data *index, t_list *tmp, t_list *previous)
{
	previous->next = tmp->next->next;
	free(tmp->next->content);
	free(tmp->next);
	free(tmp->content);
	free(tmp);
	return (previous);
}

t_list	*no_previous(t_data *index, t_list *tmp)
{
	index->cmd = tmp->next->next;
	free(tmp->next->content);
	free(tmp->next);
	free(tmp->content);
	free(tmp);
	return (index->cmd);
}

t_list	*no_ultra_next(t_data *index, t_list *tmp, t_list *previous)
{
	free(tmp->next->content);
	free(tmp->next);
	tmp->next = NULL;
	free(tmp->content);
	if (previous)
	{
		free(tmp);
		previous->next = NULL;
	}
	else
		tmp->content = ft_strdup("");
	return (tmp);
}

t_list	*remove_direction(t_data *index)
{
	t_list	*tmp;
	t_list	*previous;

	previous = NULL;
	tmp = index->cmd;
	while (tmp)
	{
		if (ft_strchr("<>", (((char *)tmp->content)[0])))
		{
			if (!tmp->next->next)
				return (no_ultra_next(index, tmp, previous));
			if (!previous && tmp->next && tmp->next->next)
				return (no_previous(index, tmp));
			else if (previous->next && tmp->next && tmp->next->next)
				return (if_previous(index, tmp, previous));
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (tmp);
}
