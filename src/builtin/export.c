/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:52:26 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/05 15:32:03 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**sort_env(t_data *index)
{
	char	**sort_env;
	char	*swap;
	int		i;
	int		j;

	sort_env = lsttoa(index->mnsh_env);
	i = 0;
	while (sort_env[i + 1])
	{
		j = i + 1;
		while (sort_env[j])
		{
			if (ft_strncmp(sort_env[i], sort_env[j], ft_strlen(sort_env[i])))
			{
				swap = sort_env[i];
				sort_env[i] = sort_env[j];
				sort_env[j] = swap;
			}
			j++;
		}
		i++;
	}
	return (sort_env);
}

void	declare_x(t_data *index, int i, int j, char *tmp)
{
	char	**env;

	env = sort_env(index);
	while (env[i])
	{
		tmp = ft_strdup("declare -x ");
		j = 0;
		while (env[i][j] != '=')
			tmp = add_char(tmp, env[i][j++]);
		tmp = add_char(tmp, '=');
		tmp = add_char(tmp, '\"');
		j++;
		while (env[i][j])
		{
			if (env[i][j] == '\"' || env[i][j] == '\\' || env[i][j] == '$')
				tmp = add_char(tmp, '\\');
			tmp = add_char(tmp, env[i][j]);
			j++;
		}
		tmp = add_char(tmp, '\"');
		ft_putendl_fd(tmp, 1);
		free(tmp);
		i++;
	}
	free_tab(&env);
}

int		mod_env(t_data *index, char *token, int len)
{
	t_list	*tmp;
	char	*old_content;
	char	*search;

	tmp = index->mnsh_env;
	search = ft_substr(token, 0, len);
	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, search, len) && \
			((char *)tmp->content)[len] == '=')
		{
			old_content = tmp->content;
			tmp->content = ft_strdup(token);
			free(old_content);
			free(search);
			return (0);
		}
		tmp = tmp->next;
	}
	free(search);
	ft_lstadd_back(&index->mnsh_env, ft_lstnew(ft_strdup(token)));
	return (1);
}

int		export_token(t_data *index, char *token)
{
	int		i;

	i = 0;
	while (token[i])
	{
		if ((!ft_isalpha(token[0]) && token[0] != '_') || \
			ft_strchr(" @\'\"\\$&|;!", token[i]))
		{
			index->statut = ft_error_u("export", token, 1, \
				"not a valid identifier");
			return (1);
		}
		if (i > 0 && token[i] == '=')
		{
			mod_env(index, token, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int		ft_export(t_data *index)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = index->cmd->next;
	if (index->child)
		return (0);
	if (!tmp)
		declare_x(index, 0, 0, NULL);
	while (tmp)
	{
		i = 0;
		if (!((char *)tmp->content)[0])
		{
			index->statut = \
				ft_error_u("export", "", 1, "not a valid identifier");
		}
		export_token(index, (char *)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}
