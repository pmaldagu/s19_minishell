/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traduction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 00:46:41 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/04 15:18:51 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*trad_specials(t_data *index, char *trad_token, char *token, int *i)
{
	if (token[(*i)] == '\\')
	{
		++(*i);
		trad_token = add_char(trad_token, token[(*i)]);
		return (trad_token);
	}
	else if (token[(*i)] == '\'')
	{
		trad_token = trad_single_quote(index, trad_token, token, i);
		return (trad_token);
	}
	else if (token[(*i)] == '\"')
	{
		trad_token = trad_double_quote(index, trad_token, token, i);
		return (trad_token);
	}
	return (trad_token);
}

char	*switch_trad(t_data *index, char *trad_token, int *i, char *nb)
{
	char *tmp;

	if (ft_strchr("\'\"\\", ((char *)index->tmp->content)[(*i)]))
		trad_token = trad_specials(index, trad_token, \
			(char *)index->tmp->content, i);
	else if (((char *)index->tmp->content)[(*i)] == '$' && \
		(ft_isalpha(((char *)index->tmp->content)[(*i) + 1]) || \
			((char *)index->tmp->content)[(*i) + 1] == '_'))
	{
		trad_token = parse_var(index, trad_token, \
			(char *)index->tmp->content, i);
	}
	else if (((char *)index->tmp->content)[(*i)] == '$' && \
		((char *)index->tmp->content)[(*i) + 1] == '?')
	{
		tmp = trad_token;
		nb = ft_itoa(index->statut);
		trad_token = ft_strjoin(trad_token, nb);
		free(tmp);
		free(nb);
		(*i)++;
	}
	else
		trad_token = add_char(trad_token, ((char *)index->tmp->content)[(*i)]);
	return (trad_token);
}

int		ft_trad(t_data *index)
{
	int		i;
	char	*trad_token;
	char	*nb;

	index->tmp = index->cmd;
	while (index->tmp)
	{
		trad_token = ft_strdup("");
		i = 0;
		while (index->tmp->content && ((char *)index->tmp->content)[i])
		{
			trad_token = switch_trad(index, trad_token, &i, nb);
			if (!trad_token)
				return (0);
			if (i < 0 || ((char *)index->tmp->content)[i] != 0)
				i++;
		}
		free(index->tmp->content);
		index->tmp->content = trad_token;
		index->tmp = index->tmp->next;
	}
	return (1);
}
