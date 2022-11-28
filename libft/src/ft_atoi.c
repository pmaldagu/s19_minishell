/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edessain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:41:35 by edessain          #+#    #+#             */
/*   Updated: 2021/02/03 15:32:48 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_long(int signe)
{
	if (signe == -1)
		return (0);
	else
		return (-1);
}

static int	ft_return(unsigned long long result, int signe)
{
	if (signe == -1 && (result - 1) == 9223372036854775807)
		return (result * signe);
	if (result > 9223372036854775807)
		return (ft_long(signe));
	return (result * signe);
}

long long	ft_atoi(const char *str)
{
	int					i;
	int					signe;
	unsigned long long	result;

	result = 0;
	signe = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (ft_return(result, signe));
}
