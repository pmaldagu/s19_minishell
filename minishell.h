#ifndef MINISHELL_H
# define MINISHELL_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./libft/libft.h"

typedef struct	s_data
{
	char	*logname;
	char	*path;
	char	*result;
}		t_data;
/*
** gnl
int	ft_strlen_end(char const *s);
int	ft_strchr_pos(const char *s, int c);
int	get_next_line(char **line);
*/
/*
** parsing
*/
int	ft_pars(char *line, t_data *pars, char **envp);
int	no_cmd(char *line);

int	ft_echo(char *line, char **envp);
int	echo_env(char *line, char **envp);

int	ft_pwd(t_data *line);
void	ft_acces(t_data *pars);

int	wrong_path(char *line);
int	ft_cd(char *line, t_data *pars);
int	cd_back(char *line, t_data *pars);
void	remove_dir(t_data *pars);

void	banner(void);
void	logname(char **envp);

int	ft_env(char **envp);

int	ft_export(char *line, char **envp);

#endif
