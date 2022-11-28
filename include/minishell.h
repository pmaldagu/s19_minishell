/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edessain <edessain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:28:21 by edessain          #+#    #+#             */
/*   Updated: 2021/02/08 12:02:01 by edessain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct	s_data
{
	t_list		*mnsh_env;
	t_list		*tokens;
	t_list		*cmd;
	t_list		*tmp;
	char		*home;
	char		*last_ope;
	char		*last_cmd;
	int			i;
	int			end_pipe;
	int			fd_out;
	int			fd_in;
	int			can_exe;
	int			statut;
	int			child;
	int			signum;
}				t_data;

int				free_tab(char ***tab);
int				unset_token(t_data *index, t_list *cmd, t_list *mod);
char			*check_dir(char *dir, char *path);
char			*trad_specials(t_data *index, \
					char *trad_token, char *token, int *i);
char			*parse_var(t_data *index, char *trad_token, \
					char *token, int *i);
int				command_line(t_data *index);
char			*var_in_double(t_data *index, char *trad_token, \
					char *token, int *i);
int				pipe_loop(t_data *index);
void			ft_free_prompt(t_data *index, char *line);
t_data			*creat_struct(void);
/*
** TOOLS
*/
char			*add_char(char *str, char a);

/*
** BUILTINS
*/

/*
** parser.c
*/
char			*add_escape(char *str, char *line, int *i);
char			*add_operator(char *line, int *i);
char			*add_single_quote(char *str, char *line, int *i);
char			*add_double_quote(char *str, char *line, int *i);
int				ft_parser(char *line, t_data *index);

/*
** traduction.c
*/
int				ft_trad(t_data *index);
char			*trad_single_quote(t_data *index, char *trad_token, \
					char *token, int *i);
char			*trad_double_quote(t_data *index, char *trad_token, \
					char *token, int *i);
char			*trad_variable(t_data *index, char *trad_token, \
					char *token, int *i);
char			*remove_spaces(char *value, char *token, int start, int end);

/*
** echo.c
*/
int				option_n(char *token);
int				ft_echo(t_data *index);

/*
** tools.c
*/
char			**lsttoa(t_list *lst);
void			print_t_list(t_list *tokens);
int				free_t_list(t_list **list);
int				free_t_data(t_data *index);

/*
** pwd.c
*/
int				ft_pwd(t_data *index);

/*
** lexer.c
*/
int				ft_errdirect(t_data *index, t_list *token);
t_list			*remove_direction(t_data *index);
int				ft_errope(t_data *index);
int				last_cmd(t_data *index);
char			*creat_last_cmd(t_data *index, t_list *last, \
					char *cmd, int *i);

/*
** export.c
*/
int				mod_env(t_data *index, char *token, int len);
int				ft_export(t_data *index);

/*
** unset.c
*/
int				ft_unset(t_data *index);

/*
** variable.c
*/
char			*get_var_name(t_data *index, char *token, int *i);
t_list			*parse_variable(t_data *index, char *trad_token, \
					t_list *tmp, int *i);

/*
** env.c
*/
int				ft_env(t_data *index);
char			*get_var_value(t_data *index, char *name);

/*
** lexer.c
*/
int				ft_lexer(t_data *index);

/*
** exec.c
*/
int				ft_errexec(t_data *index, char *path);
int				files_exist(t_data *index, char *path);
char			*in_path_dir2(t_data *index, char *path, int i, char *value);
int				exec(t_data *index);

/*
** cd.c
*/
int				ft_cd(t_data *index);

/*
** exit.c
*/
int				ft_exit(t_data *index);

/*
** error.c
*/
int				ft_error(t_data *index, char *error, int statut);

/*
** init.c
*/
int				inc_shell_lvl(t_data *index);

/*
** main.c
*/
int				ft_command(t_data *index);
int				ft_prompt(t_data *index);

/*
** new_errno.c
*/
int				print_error(t_data *index, t_list *cmd, int error);

/*
** new_path.c
*/
char			*path_interpreter(char *path);
char			*new_path(t_data *index, char *oldpath);

/*
** ft_atoll.c
*/
long long		ft_atoll(const char *str);

/*
** redirection.c
*/
t_list			*remove_direction(t_data *index);
int				ft_redirection(t_data *index);

/*
** error_u.c
*/
int				ft_error_u(char *cmd, char *arg, int error, char *msg);
#endif
