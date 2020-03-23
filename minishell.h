#ifndef MINISHELL_H
# define MINISHELL_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./libft/libft.h"

typedef struct	s_data
{
	char	*cmd;
	char	*opt;
	char	*path;
	char	*result;
	char	pipe;
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
int	ft_pars(char *line);
int	no_cmd(char *line);

int	ft_echo(char *line);

int	ft_pwd(void);
void	ft_acces(void);

#endif
