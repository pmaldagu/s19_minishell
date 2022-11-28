/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:51:24 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/03 18:46:55 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*format_number(char *statut)
{
	char		*formated;
	char		*tmp;
	int			i;

	i = 1;
	formated = ft_strdup("");
	formated = add_char(formated, statut[0]);
	while ((!ft_isdigit(statut[0]) || statut[0] == '0') && statut[i] == '0')
		i++;
	if (statut[i])
	{
		tmp = formated;
		formated = ft_strjoin(formated, &statut[i]);
		free(tmp);
	}
	else if (ft_strlen(statut) > 1)
		formated = add_char(formated, '0');
	return (formated);
}

int		overflow(char *statut)
{
	long long	nb;

	nb = ft_atoll(statut);
	if ((nb == -1 || nb == 0) && ft_strlen(statut) > 5)
	{
		return (1);
	}
	return (0);
}

int		num_err_arg(t_data *index, char *statut, int i, int nb)
{
	t_list		*tmp;

	tmp = index->cmd;
	while (statut[i])
	{
		if (ft_isdigit(statut[0]) && !ft_isdigit(statut[i]) && \
			!ft_strchr(" \t", statut[i]))
		{
			return ((index->statut = ft_error_u(tmp->content, \
				tmp->next->content, 255, "numeric argument required")));
		}
		if (statut[i] == '-' || statut[i] == '+')
		{
			return ((index->statut = ft_error_u(tmp->content, \
				tmp->next->content, 255, "numeric argument required")));
		}
		if (ft_isdigit(statut[i++]))
			nb++;
	}
	if ((!nb && !ft_isdigit(statut[0])) || overflow(statut) || statut[0] == '_')
	{
		return ((index->statut = ft_error_u(tmp->content, \
			tmp->next->content, 255, "numeric argument required")));
	}
	return (0);
}

int		ft_exit(t_data *index)
{
	t_list			*tmp;
	long long		statut;
	char			*str;

	tmp = index->cmd;
	if (tmp->next)
		str = format_number((char *)tmp->next->content);
	if (!tmp->next || num_err_arg(index, str, 1, 0))
	{
		free_t_data(index);
		exit(index->statut);
	}
	if (tmp->next->next)
	{
		index->statut = ft_error_u(index->cmd->content, NULL, 1, \
			"too many arguments");
		free_t_data(index);
		exit(index->statut);
	}
	else
		statut = ft_atoll(str);
	index->statut = (int)(statut & 0xFF);
	free_t_data(index);
	exit(index->statut);
	return (1);
}
