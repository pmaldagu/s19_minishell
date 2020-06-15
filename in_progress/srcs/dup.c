/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossuin <agossuin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:29:44 by agossuin          #+#    #+#             */
/*   Updated: 2020/04/09 16:38:23 by agossuin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Gets a dupped value of of the variable 'str' we need.
*/

char	*ft_vardup(char *str, t_list *list, unsigned int size)
{
	char *dup;

	dup = NULL;
	while (list)
	{
		if (list->content && !ft_strncmp(list->content, str, size))
			return (ft_strdup(&(((char*)list->content)[size + 1])));
		list = list->next;
	}
	return (dup);
}

/*
** Ft_translate is used for this formatting: '${var}'.
*/

char	*ft_translate(t_cmd *cmd)
{
	char	*res;
	t_list	*tmp;
	int		size;

	size = 0;
	cmd->i++;
	if (cmd->line[cmd->i] == '{')
		cmd->i++;
	while (ft_isalnum(cmd->line[cmd->i + size]))
		size++;
	if (!(res = ft_vardup(&(cmd->line[cmd->i]), cmd->env, size)))
		res = ft_vardup(&(cmd->line[cmd->i]), cmd->vars, size);
	if (res)
		cmd->i += size;
	return (res);
}

/*
** Basicdup is when we have no quotes.
** Translates '$' variables.
** Considers the '\' escape sequence.
** If no '\', stops when meeting any of : " \f\n\r\t\v\'\"|;<>$"
*/

char	*ft_basicdup(t_cmd *cmd)
{
	char	tmp[1000];
	char	*var;
	int		j;

	ft_bzero(tmp, 1000);
	j = 0;
	if (cmd->line[cmd->i] == '$' && ft_isvar_call(cmd))
	{
		var = ft_translate(cmd);
		j += ft_strlen(var);
		ft_strlcat(tmp, var, 1000);
		free(var);
	}
	else if (!cmd->i)
		tmp[j++] = cmd->line[cmd->i++];
	while (cmd->line[cmd->i] && (cmd->line[cmd->i - 1] == '\\' ||
		!ft_isinset(cmd->line[cmd->i], " \f\n\r\t\v\'\"|;<>$")))
	{
		if (cmd->line[cmd->i] == '\\' && cmd->line[cmd->i + 1] == '\\')
			tmp[j++] = cmd->line[cmd->i++];
		else if (cmd->line[cmd->i] != '\\')
			tmp[j++] = cmd->line[cmd->i];
		cmd->i++;
	}
	return (ft_strdup(tmp));
}

/*
** Weakdup is used when we have double quotes.
** Translates '$' variables.
** Considers the '\' escape sequence.
*/

char	*ft_weakdup(t_cmd *cmd)
{
	char	tmp[1000];
	char	*var;
	int		j;

	cmd->i++;
	ft_bzero(tmp, 1000);
	j = 0;
	while (cmd->line[cmd->i] && (cmd->line[cmd->i - 1] == '\\' ||
		cmd->line[cmd->i] != '"'))
	{
		if (cmd->line[cmd->i] == '\\'
			&& ft_isinset(cmd->line[cmd->i + 1], "$\\\""))
			tmp[j++] = cmd->line[cmd->i++];
		else if (cmd->line[cmd->i] == '$' && ft_isvar_call(cmd))
		{
			var = ft_translate(cmd);
			j += ft_strlen(var);
			ft_strlcat(tmp, var, 1000);
			free(var);
		}
		else
			tmp[j++] = cmd->line[cmd->i];
		cmd->i++;
	}
	return (ft_strdup(tmp));
}

/*
** Strongdup is used when we have single quotes.
** Simply write back what is written between the single quotes.
*/

char	*ft_strongdup(t_cmd *cmd)
{
	int		start;
	char	*dup;

	dup = NULL;
	start = cmd->i++;
	while (cmd->line[cmd->i] && (cmd->line[cmd->i] != '\''))
		cmd->i++;
	dup = ft_substr(cmd->line, start + 1, cmd->i - start - 1);
	if ((cmd->line[cmd->i] == '\''))
		cmd->i++;
	return (dup);
}

/*
** Calls the upper functions.
** Notice the exit status if no error. (i can't remember why...)
*/

char	*ft_minidup(t_cmd *cmd)
{
	char *var;
	char *tmp;
	char *tmp2;

	var = NULL;
	while (ft_isspace(cmd->line[cmd->i]))
		cmd->i++;
	while (cmd->line[cmd->i] && !ft_isspace(cmd->line[cmd->i])
		&& !ft_isinset(cmd->line[cmd->i], "|;<>"))
	{
		tmp = var;
		if (cmd->line[cmd->i] == '\'')
			tmp2 = ft_strongdup(cmd);
		else if (cmd->line[cmd->i] == '\"')
			tmp2 = ft_weakdup(cmd);
		else
			tmp2 = ft_basicdup(cmd);
		if (cmd->exit_status != 0 && !cmd->error)
			cmd->error = ft_strdup(tmp2);
		var = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
	}
	return (var);
}
