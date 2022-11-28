/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 00:14:15 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/03 14:40:32 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*add_escape(char *str, char *line, int *i)
{
	char	*tmp;
	char	*esc;

	esc = ft_substr(line, (*i), 2);
	(*i)++;
	tmp = str;
	str = ft_strjoin(str, esc);
	free(tmp);
	free(esc);
	return (str);
}

char	*add_operator(char *line, int *i)
{
	int		j;
	int		limit;
	char	c;
	char	*new_str;

	j = 0;
	c = line[(*i)];
	if (line[(*i)] && ft_strchr(";|", line[(*i)]))
		limit = 1;
	else if (line[(*i)] && line[(*i)] == '<')
		limit = 3;
	else
		limit = 2;
	new_str = ft_strdup("");
	while (line[(*i)] && line[(*i)] == c && j < limit)
	{
		new_str = add_char(new_str, line[(*i)]);
		j++;
		(*i)++;
	}
	return (new_str);
}

char	*add_to_token(char *token, char *line, int *i)
{
	if (line[(*i)] == '\\')
		token = add_escape(token, line, i);
	else if (line[(*i)] == '\'')
		token = add_single_quote(token, line, i);
	else if (line[(*i)] == '\"')
		token = add_double_quote(token, line, i);
	else
		token = add_char(token, line[(*i)]);
	return (token);
}

int		ft_parser(char *line, t_data *index)
{
	int		i;
	char	*token;

	i = 0;
	token = NULL;
	while (line[i])
	{
		token = ft_strdup("");
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		while (line[i] && line[i] != ' ' && \
			line[i] != '\t' && !ft_strchr(";|<>", line[i]))
		{
			token = add_to_token(token, line, &i);
			if (line[i] != 0)
				i++;
		}
		if (token[0])
			ft_lstadd_back(&index->tokens, ft_lstnew(token));
		if (line[i] && ft_strchr(";|<>", line[i]))
			ft_lstadd_back(&index->tokens, ft_lstnew((add_operator(line, &i))));
		if (!token[0])
			free(token);
	}
	return (1);
}
