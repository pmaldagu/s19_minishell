/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossuin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 11:52:46 by agossuin          #+#    #+#             */
/*   Updated: 2019/08/19 16:52:14 by agossuin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_number_type_changer(const char *str2, int i, int nb, int sign)
{
	while (str2[i] >= '0' && str2[i] <= '9')
	{
		if ((nb > 214748364 && str2[i] > 7) || nb > 2147483647)
		{
			if (sign == -1 && (str2[i] != 8 && nb != 214748364))
				return (0);
			else if (sign == 1)
				return (-1);
		}
		nb *= 10;
		nb += str2[i] - '0';
		i++;
		ft_number_type_changer(str2, i, nb, sign);
	}
	return (nb * sign);
}

int			ft_atoi(const char *str)
{
	int i;
	int sign;
	int nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	nb = ft_number_type_changer(str, i, nb, sign);
	return (nb);
}
