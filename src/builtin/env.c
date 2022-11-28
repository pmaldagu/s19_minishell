/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:05:05 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/04 17:47:27 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_data *index)
{
	t_list		*tmp;

	tmp = index->mnsh_env;
	mod_env(index, "_=env", 1);
	while (tmp)
	{
		ft_putendl_fd((char *)tmp->content, 1);
		tmp = tmp->next;
	}
	return (1);
}
