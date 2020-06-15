/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossuin <agossuin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:30:06 by agossuin          #+#    #+#             */
/*   Updated: 2020/04/09 17:36:49 by agossuin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <dirent.h>
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include "../libft/libft.h"

enum			e_error
{
	BAD_SUBSTITUTION = 1,
	MALLOC_FAIL = 12,
	COMMAND_NOT_FOUND = 127,
};

enum			e_cmd
{
	ERROR = -1,
	NOCMD,
	EXEC,
	ECHO,
	ECHON,
	ENV,
	CD,
	PWD,
	EXPORT,
	UNSET,
	EXIT,
};

/*
** line			-> entire line of command.
** i			-> current position in the line.
** cmd			-> index of the current command from 'enum e_cmd'.
** args			-> current arguments.
** env			-> t_list with entire env.
** vars			-> variables not exported to the env. (we can use them)
** fd_output	-> default is 1.
** fd_append	-> only used when writing in a file.
** fd_input		-> default is 0.
** exit_status	-> well... this is what it is.
** error		-> string of explanation in case of error.
*/

typedef struct	s_cmd
{
	char		*line;
	int			i;
	int			cmd;
	t_list		*args;
	t_list		*env;
	t_list		*vars;
	int			fd_output;
	int			fd_append;
	int			fd_input;
	int			exit_status;
	char		*error;
}				t_cmd;

/*
** CMD
*/

void			ft_echo(t_cmd *cmd, int fd);
void			ft_cd(t_cmd *cmd, int res);
void			ft_pwd(t_cmd *cmd, int fd);
void			ft_export(t_cmd *cmd);
void			ft_unset_from(t_list *list, t_cmd *cmd);
void			ft_unset(t_cmd *cmd);

/*
** DUP
*/

char			*ft_vardup(char *str, t_list *list, unsigned int size);
char			*ft_translate(t_cmd *cmd);
char			*ft_basicdup(t_cmd *cmd);
char			*ft_weakdup(t_cmd *cmd);
char			*ft_strongdup(t_cmd *cmd);
char			*ft_minidup(t_cmd *cmd);

/*
** ENV
*/

t_list			*ft_lstenv(char **envp);
void			ft_putenv(t_list *env, int fd);
int				ft_var_to_lst(t_list *lst, const char *var);

/*
** EXEC
*/

/*
** GET_REDIR
*/

void			ft_get_append(t_cmd *cmd);
void			ft_get_output(t_cmd *cmd);
void			ft_get_input(t_cmd *cmd);
void			ft_get_redir(t_cmd *cmd);

/*
** GET
*/

void			ft_get_exe(t_cmd *cmd);
void			ft_get_var(t_cmd *cmd);
void			ft_get_echo(t_cmd *cmd);
void			ft_get_cmd(t_cmd *cmd);
void			ft_get_arg(t_cmd *cmd);

/*
** IS_TYPE
*/

int				ft_isvar_call(t_cmd *cmd);
int				ft_ispath(char *line);
int				ft_isvar(char *line);

/*
** MINISHELL
*/

void			banner(void);

/*
** PROMPT
*/

void			ft_reset_cmd(t_cmd *cmd);
void			ft_puterror(t_cmd *cmd);
void			apply_cmd(t_cmd *cmd);
void			ft_parsing_cmd(t_cmd *cmd);
int				ft_prompt(char *name, t_cmd *cmd);

#endif
