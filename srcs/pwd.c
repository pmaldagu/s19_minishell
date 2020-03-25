/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 18:07:44 by pmaldagu          #+#    #+#             */
/*   Updated: 2020/03/25 09:53:27 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_acces(t_data *pars)
{
	char buf[1001];

	ft_bzero(buf, 1001);
	pars->path = ft_strdup(getcwd(buf, 1000));
	write(1, pars->path, ft_strlen(pars->path));
	write(1, "> ", 2);
}

int	ft_pwd(t_data *pars)
{
	write(1, pars->path, ft_strlen(pars->path));
	write(1, "\n", 1);
	return (1);
}
