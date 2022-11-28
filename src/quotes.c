/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 00:20:26 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/04 15:13:58 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*var_in_double(t_data *index, char *trad_token, char *token, int *i)
{
	char	*var;
	char	*tmp;
	char	*value;

	var = get_var_name(index, token, i);
	value = get_var_value(index, var);
	tmp = ft_strjoin(trad_token, value);
	free(trad_token);
	trad_token = tmp;
	free(value);
	free(var);
	return (trad_token);
}

char	*trad_double_quote(t_data *index, char *trad_token, char *token, int *i)
{
	(*i) += 1;
	while (token[(*i)] && token[(*i)] != '"')
	{
		if (token[(*i)] == '$')
			trad_token = var_in_double(index, trad_token, token, i);
		else if (token[(*i)] == '\\' && ft_strchr("\"\\$", token[(*i) + 1]))
		{
			trad_token = add_char(trad_token, token[(*i) + 1]);
			(*i)++;
		}
		else
			trad_token = add_char(trad_token, token[(*i)]);
		(*i)++;
	}
	if (!token[(*i)])
	{
		index->statut = ft_error_u("\"", NULL, 2, NULL);
		free(trad_token);
		return (NULL);
	}
	return (trad_token);
}

char	*trad_single_quote(t_data *index, char *trad_token, char *token, int *i)
{
	(*i) += 1;
	while (token[(*i)] && token[(*i)] != '\'')
	{
		trad_token = add_char(trad_token, token[(*i)]);
		(*i)++;
	}
	if (!token[(*i)])
	{
		index->statut = ft_error_u("\'", NULL, 2, NULL);
		free(trad_token);
		return (NULL);
	}
	return (trad_token);
}

char	*add_single_quote(char *str, char *line, int *i)
{
	char	*new_str;

	new_str = add_char(str, line[(*i)]);
	(*i) += 1;
	while (line[(*i)] && line[(*i)] != '\'')
	{
		new_str = add_char(new_str, line[(*i)]);
		(*i)++;
	}
	new_str = add_char(new_str, line[(*i)]);
	return (new_str);
}

char	*add_double_quote(char *str, char *line, int *i)
{
	char	*new_str;

	new_str = add_char(str, line[(*i)]);
	(*i) += 1;
	while (line[(*i)])
	{
		if (line[(*i)] == '"' && line[(*i) - 1] != '\\')
			break ;
		new_str = add_char(new_str, line[(*i)]);
		(*i)++;
	}
	new_str = add_char(new_str, line[(*i)]);
	return (new_str);
}
