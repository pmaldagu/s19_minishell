/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:09:20 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/03 18:39:30 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		only_space(char *value)
{
	int		i;

	i = 0;
	while (value && value[i] && value[i] == ' ')
		i++;
	if (value && !value[i] && i > 0)
		return (1);
	else
		return (0);
}

void	end_list(t_data *index, char *value, char *old_cont, t_list *next)
{
	char	*tmp;
	int		i;

	i = 0;
	while (value[i])
		i++;
	if (i > 0)
		i -= 1;
	tmp = (char *)index->tmp->content;
	if (value && (value[i] != ' ' || \
		(only_space(value) && !((char *)index->tmp->content)[0])))
	{
		index->i = ft_strlen(tmp);
		index->tmp->content = ft_strjoin((char *)index->tmp->content, old_cont);
		free(tmp);
		index->tmp->next = next;
	}
	else if (old_cont[0] && value[0])
	{
		index->tmp->next = ft_lstnew(ft_strdup(old_cont));
		index->tmp->next->next = next;
	}
	else
		index->tmp->next = next;
}

void	var_tokens(t_data *index, char *value, char *trad_token)
{
	char	**split;
	int		j;

	j = 0;
	split = ft_split(value, ' ');
	if ((value && value[0] != ' ') || (value && !trad_token[0]))
		j++;
	while (split && split[0] && !only_space(split[0]) && split[j])
	{
		index->tmp->next = ft_lstnew(ft_strdup(split[j]));
		index->tmp = index->tmp->next;
		j++;
		index->i = ft_strlen((char *)index->tmp->content);
	}
	free_tab(&split);
}

void	new_content(t_data *index, char *trad_token, char *value, int *i)
{
	char	*tmp;
	int		begin;
	int		end;

	begin = 0;
	while (value[begin] && value[begin] == ' ')
		begin++;
	end = begin;
	while (value[end] && value[end] != ' ')
		end++;
	free(index->tmp->content);
	if (value && !trad_token[0] || (value && value[0] != ' '))
	{
		tmp = ft_substr(value, begin, end - begin);
		index->tmp->content = ft_strjoin(trad_token, tmp);
		(*i) = ft_strlen(trad_token) + ft_strlen(tmp);
		free(tmp);
	}
	else
	{
		index->tmp->content = ft_strdup(trad_token);
		(*i) = ft_strlen(trad_token);
	}
	index->i = (*i);
	var_tokens(index, value, trad_token);
}

char	*parse_var(t_data *index, char *trad_token, char *token, int *i)
{
	t_list	*next;
	char	*value;
	char	*tmp;
	char	*old_cont;

	tmp = get_var_name(index, token, i);
	value = get_var_value(index, tmp);
	free(tmp);
	next = index->tmp->next;
	index->tmp->next = NULL;
	old_cont = ft_strdup(&token[(*i) + 1]);
	new_content(index, trad_token, value, i);
	if (index->tmp->next)
	{
		while (index->tmp->next)
			index->tmp = index->tmp->next;
		index->i = ft_strlen((char *)index->tmp->content);
	}
	free(trad_token);
	end_list(index, value, old_cont, next);
	(*i) = index->i - 1;
	trad_token = ft_substr((char *)index->tmp->content, 0, (*i) + 1);
	free(old_cont);
	free(value);
	return (trad_token);
}
