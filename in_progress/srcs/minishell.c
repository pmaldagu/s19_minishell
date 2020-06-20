/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossuin <agossuin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:30:02 by agossuin          #+#    #+#             */
/*   Updated: 2020/06/20 16:50:21 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** This is just too beautiful.
*/
char *pwd = NULL;

void	banner(void)
{
	size_t	i;
	size_t	len;
	char	*banner;
	char	*sign;

	i = 0;
	len = 1;
	sign = "by pmaldagu agossuin";
	banner = "\n                                                                       ____                         \n      .'. .`.       | |..          | |             ..'''' |         | |            |        |       \n    .'   `   `.     | |  ``..      | |          .''       |_________| |______      |        |       \n  .'           `.   | |      ``..  | |       ..'          |         | |            |        |       \n.'               `. | |          ``| | ....''             |         | |___________ |_______ |_______\n";
	while (banner[len] != '\n')
		len++;
	len -= ft_strlen(sign) + 1;
	write(1, banner, ft_strlen(banner));
	while (i < len)
	{
		write(1, " ", 1);
		i++;
	}
	write(1, sign, ft_strlen(sign));
	write(1, "\n\n\n", 3);
}

/*
** We use One big struct 't_cmd *cmd'.
** We immediately init 'cmd->env' and an empty 'cmd->var'.
**
** Ft_prompt is where the magic happens !
**
** After that, we free all and quit.
*/

int		main(int argc, char const *argv[], char **envp)
{
	t_cmd	*cmd;

	//signal(SIGQUIT, SIG_IGN);
	//signal(SIGINT, int_handler);
	if (!(cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		return (MALLOC_FAIL);
	ft_bzero(cmd, sizeof(t_cmd));
	cmd->env = (t_list *)ft_lstenv(envp);
	cmd->vars = ft_lstnew(NULL);
	cmd->fd_output = 1;
	//banner();
	ft_prompt("minishell $ ", cmd);
	ft_lstclear(&(cmd->env), free);
	ft_lstclear(&(cmd->vars), free);
	free(cmd);
	return (0);
}
