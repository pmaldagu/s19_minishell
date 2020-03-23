/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 18:07:44 by pmaldagu          #+#    #+#             */
/*   Updated: 2020/03/23 18:31:36 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_acces(void)
{
	char buf[1001];
	char *path;

	ft_bzero(buf, 1001);
	path = getcwd(buf, 1000);
	write(0, path, ft_strlen(path));
	write(0, "> ", 2);
}

int	ft_pwd(void)
{
	char buf[1001];
	char *path;

	ft_bzero(buf, 1001);
	path = getcwd(buf, 1000);
	write(0, path, ft_strlen(path));
	write(0, "\n", 1);
	return (1);
}
