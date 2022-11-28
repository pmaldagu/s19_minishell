/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:00:23 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/01/28 17:00:25 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_data *index)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	index->last_cmd = pwd;
	return (1);
}
