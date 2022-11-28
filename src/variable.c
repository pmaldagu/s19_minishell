/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:14:04 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/02 17:15:06 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_var_value(t_data *index, char *name)
{
	t_list	*tmp;
	int		len;

	tmp = index->mnsh_env;
	len = ft_strlen(name);
	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, name, len) && \
				((char *)tmp->content)[len] == '=')
			return (ft_strdup(ft_strchr((char *)tmp->content, '=') + 1));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

char	*get_var_name(t_data *index, char *token, int *i)
{
	char	*name;
	char	*buf;
	char	*value;
	int		start;

	if (!token[(*i) + 1] || ft_strchr(" \"|$,']\\-@:", token[(*i) + 1]))
		return (ft_strdup("$"));
	start = (*i);
	(*i) += 1;
	name = ft_strdup("");
	while (token[(*i)] && !ft_strchr(" \"|$,']\\-@:", token[(*i)]))
	{
		name = add_char(name, token[(*i)]);
		(*i)++;
	}
	(*i)--;
	return (name);
}
