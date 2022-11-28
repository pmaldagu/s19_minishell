/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <pmaldagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 08:30:51 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/05 17:19:16 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*redir_var(t_data *index, char *token, char *path, int *i)
{
	char	*var_name;
	char	*tmp;

	var_name = get_var_name(index, token, i);
	tmp = get_var_value(index, var_name);
	if (ft_strchr(tmp, ' '))
	{
		index->statut = ft_error_u(NULL, token, 1, \
			"ambiguous redirect");
		free(var_name);
		free(path);
		free(tmp);
		return (NULL);
	}
	free(var_name);
	var_name = path;
	path = ft_strjoin(path, tmp);
	free(tmp);
	free(var_name);
	return (path);
}

char	*path_redir(t_data *index, char *token)
{
	int		i;
	char	*path;

	i = 0;
	path = ft_strdup("");
	while (token[i])
	{
		if (ft_strchr("\\\'\"", token[i]))
			path = trad_specials(index, path, token, &i);
		else if (token[i] == '$' && (ft_isalpha(token[i + 1]) || \
			token[i] == '_'))
		{
			if (!(path = redir_var(index, token, path, &i)))
				return (NULL);
		}
		else
			path = add_char(path, token[i]);
		if (token[i])
			i++;
	}
	return (path);
}

int		new_fd(t_data *index, t_list *tmp, int fd, char *path)
{
	int		flags;

	flags = O_RDONLY;
	if (ft_errdirect(index, tmp->next))
		return (-1);
	if (tmp->next && !ft_strncmp(((char *)tmp->content), ">>", 2))
		flags = O_RDWR | O_CREAT | O_APPEND;
	else if (tmp->next && ((char *)tmp->content)[0] == '>')
		flags = O_RDWR | O_CREAT | O_TRUNC;
	else if (tmp->next && ((char *)tmp->content)[0] == '<')
	{
		if (fd > 0 && index->fd_in != 0)
			close(index->fd_in);
	}
	if (!(path = path_redir(index, (char *)tmp->next->content)))
		return (-1);
	fd = open(path, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		ft_errexec(index, (char *)tmp->next->content);
		index->statut = 1;
	}
	free(path);
	return (fd);
}

int		switch_redir(t_data *index, t_list *tmp, int fd)
{
	if (tmp->next && ((char *)tmp->content)[0] == '>')
	{
		if (index->fd_out > 1)
			close(index->fd_out);
		index->fd_out = fd;
	}
	else
		index->fd_in = fd;
	return (0);
}

int		ft_redirection(t_data *index)
{
	t_list	*tmp;
	int		fd;

	tmp = index->cmd;
	while (tmp)
	{
		if (((char *)tmp->content)[0] && ft_strchr("<>", \
			(((char *)tmp->content)[0])))
		{
			if ((fd = new_fd(index, tmp, fd, NULL)) < 0)
				return (0);
			switch_redir(index, tmp, fd);
			tmp = remove_direction(index);
		}
		if (tmp)
			tmp = tmp->next;
	}
	fd = dup(0);
	dup2(index->fd_out, 1);
	dup2(index->fd_in, 0);
	return (1);
}
