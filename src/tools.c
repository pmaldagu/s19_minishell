/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <pmaldagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:36:25 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/08 12:02:03 by edessain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	*creat_struct(void)
{
	static t_data index;

	return (&index);
}

void	ft_free_prompt(t_data *index, char *line)
{
	if (line)
		free(line);
	free(index->cmd);
	free(index->tokens);
}

char	*add_char(char *str, char a)
{
	char	*new_str;
	char	*tmp;

	tmp = NULL;
	new_str = NULL;
	if (!(tmp = ft_calloc(1, 2)))
		return (NULL);
	tmp[0] = a;
	new_str = ft_strjoin(str, tmp);
	free(tmp);
	free(str);
	return (new_str);
}

char	**lsttoa(t_list *lst)
{
	int		i;
	t_list	*tmp;
	char	**tab;

	tmp = lst;
	i = 0;
	if ((tab = malloc(sizeof(char *) * (ft_lstsize(lst) + 1))))
	{
		while (tmp)
		{
			tab[i] = tmp->content;
			tmp = tmp->next;
			i++;
		}
		tab[i] = NULL;
		return (tab);
	}
	return (NULL);
}

void	print_t_list(t_list *tokens)
{
	t_list	*tmp;

	tmp = tokens;
	while (tmp)
	{
		write(1, "content = ", 10);
		ft_putendl_fd((char *)tmp->content, 1);
		tmp = tmp->next;
	}
}
