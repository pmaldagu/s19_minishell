/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <pmaldagu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:39:09 by pmaldagu          #+#    #+#             */
/*   Updated: 2020/04/09 16:41:27 by agossuin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Generates the 't_list *cmd->env' containing the env.
*/

t_list	*ft_lstenv(char **envp)
{
	int		i;
	t_list	*env;

	i = 0;
	env = ft_lstnew((void *)ft_strdup(envp[i++]));
	while (envp[i])
		ft_lstadd_back(&env, ft_lstnew((void *)ft_strdup(envp[i++])));
	return (env);
}

/*
** Prints the env to the fd.
*/

void	ft_putenv(t_list *env, int fd)
{
	while (env)
	{
		ft_putendl_fd(env->content, fd);
		env = env->next;
	}
}

/*
** Adds a var of the form 'hello=john' to a t_list*.
** The t_list* are 'cmd->vars' and 'cmd->env'
*/

int		ft_var_to_lst(t_list *env, const char *var)
{
	t_list	*cpy_env;
	int		size;

	cpy_env = env;
	size = 0;
	while (var[size] && var[size] != '=')
		size++;
	size++;
	while (env)
	{
		if (env->content && !ft_strncmp(env->content, var, size - 1))
		{
			free(env->content);
			env->content = ft_strdup(var);
			return (0);
		}
		env = env->next;
	}
	ft_lstadd_back(&cpy_env, ft_lstnew((void*)ft_strdup(var)));
	return (0);
}
