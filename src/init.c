/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:57:05 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/03 19:42:19 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*format_lvl(char *value)
{
	char	*tmp;
	int		i;

	i = 0;
	while (ft_isspace(value[i]))
		i++;
	while (value[i] == '0')
		i++;
	tmp = value;
	if (value[i])
		value = ft_strdup(&value[i]);
	else
		value = ft_strdup("0");
	free(tmp);
	return (value);
}

int		ft_errshlvl(t_data *index, int lvl, char *value)
{
	lvl++;
	if (lvl >= 1000)
	{
		value = ft_itoa(lvl);
		ft_putstr_fd("minishell: warning: shell level (", 1);
		ft_putstr_fd(value, 1);
		ft_putendl_fd(") too high, resetting to 1", 1);
		lvl = 1;
		free(value);
	}
	else if (lvl < -1)
		lvl = 0;
	return (lvl);
}

int		inc_shell_lvl(t_data *index)
{
	t_list	*tmp;
	int		lvl;
	char	*value;
	char	*var;

	tmp = index->mnsh_env;
	while (tmp && ft_strncmp((char *)tmp->content, "SHLVL=", 6))
		tmp = tmp->next;
	if (tmp)
	{
		value = ft_strdup(&((char *)tmp->content)[6]);
		value = format_lvl(value);
		lvl = ft_atoll(value);
		lvl = ft_errshlvl(index, lvl, value);
		free(value);
		value = ft_itoa(lvl);
		var = ft_strjoin("SHLVL=", value);
		free(value);
		mod_env(index, var, 5);
		free(var);
	}
	else
		ft_lstadd_back(&index->mnsh_env, ft_lstnew(ft_strdup("SHLVL=1")));
	return (1);
}
