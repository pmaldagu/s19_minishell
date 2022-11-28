/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <pmaldagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:46:01 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/08 11:56:28 by edessain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int		ft_command(t_data *index)
{
	if (!index->cmd)
		return (0);
	else if (!ft_strncmp((char*)index->cmd->content, "echo", 5))
		return (ft_echo(index));
	else if (!ft_strncmp((char*)index->cmd->content, "export", 7))
		return (ft_export(index));
	else if (!ft_strncmp((char*)index->cmd->content, "env", 4))
		return (ft_env(index));
	else if (!ft_strncmp((char*)index->cmd->content, "pwd", 4))
		return (ft_pwd(index));
	else if (!ft_strncmp((char*)index->cmd->content, "unset", 6))
		return (ft_unset(index));
	else if (!ft_strncmp((char*)index->cmd->content, "cd", 3))
		return (ft_cd(index));
	else if (!ft_strncmp((char*)index->cmd->content, "exit", 5))
		return (ft_exit(index));
	else if (!((char *)index->cmd->content)[0])
		return (1);
	else if (exec(index))
		return (1);
	else
		return (index->statut = ft_error_u((char *)index->cmd->content, \
			NULL, 127, "command not found"));
}

void	signal_handler(int signum)
{
	t_data *index;

	index = creat_struct();
	index->signum = signum;
	if (signum == SIGQUIT && index->child <= 1)
		ft_putstr_fd("Quit (core dumped)", 2);
	ft_putstr_fd("\n", 1);
	close(0);
	dup(0);
}

int		ft_prompt(t_data *index)
{
	char *line;

	line = NULL;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		write(1, "minishell >", 11);
		if (!get_next_line(0, &line) && index->signum == 0)
		{
			write(1, "exit", 4);
			free_t_data(index);
			free(line);
			free(index->home);
			free(index->last_ope);
			return (0);
		}
		ft_parser(line, index);
		ft_lexer(index);
		ft_free_prompt(index, line);
		index->signum = 0;
	}
	free_t_data(index);
	free(index->home);
	return (0);
}

int		list_env(char **envp, t_data *index)
{
	int		i;
	char	*pwd;
	char	*tmp;

	i = 0;
	tmp = getcwd(NULL, 0);
	while (envp[i])
	{
		ft_lstadd_back(&index->mnsh_env, \
				ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	index->home = get_var_value(index, "HOME");
	pwd = ft_strjoin("PWD=", tmp);
	mod_env(index, pwd, 3);
	inc_shell_lvl(index);
	free(pwd);
	free(tmp);
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	t_data	*index;
	int		i;

	i = 0;
	index = creat_struct();
	index->tokens = NULL;
	index->mnsh_env = NULL;
	index->cmd = NULL;
	index->home = NULL;
	index->statut = 0;
	index->signum = 0;
	index->last_ope = NULL;
	list_env(envp, index);
	if (argc > 2 && !ft_strncmp(argv[1], "-c", 3))
	{
		index->statut = 0;
		ft_parser(argv[2], index);
		ft_lexer(index);
		free_t_data(index);
		return (index->statut);
	}
	ft_prompt(index);
	free_t_data(index);
	return (index->statut);
}
