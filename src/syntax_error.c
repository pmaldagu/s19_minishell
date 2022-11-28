/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 21:28:09 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/02/05 15:28:04 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_errdirect(t_data *index, t_list *token)
{
	if (!token || ft_strchr("><|;", ((char *)token->content)[0]))
	{
		index->statut = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
		if (token)
			ft_putstr_fd((char *)token->content, 1);
		else if (!token || !token->content || \
			!((char *)token->content)[0])
		{
			ft_putstr_fd("newline", 1);
		}
		ft_putendl_fd("'", 1);
		return (1);
	}
	return (0);
}

int		switch_return(t_data *index)
{
	index->statut = 2;
	return (1);
}

int		switch_ope(t_data *index, t_list *tok, t_list *previous)
{
	if (!previous && ft_strchr(";|", ((char *)tok->content)[0]))
	{
		return (index->statut = \
			ft_error_u((char *)tok->content, NULL, 2, NULL));
	}
	if (tok->next && ft_strchr(";|", ((char *)tok->next->content)[0]))
	{
		if (tok->next->next && \
			ft_strchr(";|", ((char *)tok->next->next->content)[0]))
		{
			return (index->statut = \
				ft_error_u((char *)tok->next->next->content, NULL, 2, NULL));
		}
		if (ft_strchr("<>", ((char *)tok->content)[0]) || (tok->next->next && \
			ft_strchr("<>;|", ((char *)tok->next->next->content)[0])))
		{
			return (index->statut = \
				ft_error_u((char *)tok->next->content, NULL, 2, NULL));
		}
	}
	if (((char *)tok->content)[0] == '|' && !tok->next)
		return (switch_return(index));
	return (0);
}

int		ft_errope(t_data *index)
{
	t_list	*tok;
	t_list	*previous;

	tok = index->tokens;
	previous = NULL;
	while (tok)
	{
		if (switch_ope(index, tok, previous))
			return (1);
		previous = tok;
		tok = tok->next;
	}
	return (0);
}
