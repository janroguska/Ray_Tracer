/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <jroguszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:15:10 by jroguszk          #+#    #+#             */
/*   Updated: 2017/12/08 11:00:06 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static	int		check_num(char str)
{
	if ((str == '\n') || (str == '\t') || (str == ' ')
			|| (str == '\v') || (str == '\f') || (str == '\r'))
		return (1);
	else
		return (0);
}

static	int		check_negative(char str)
{
	if (str == '-')
		return (-1);
	else
		return (1);
}

int				ft_atoi(const char *str)
{
	int		i;
	int		nbr;
	int		temp;
	long	j;

	i = 0;
	temp = 0;
	nbr = 1;
	j = 0;
	while (check_num(str[i]) == 1)
		i++;
	nbr = check_negative(str[i]);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] >= 48 && str[i] <= 57) && str[i])
	{
		j = ((j * 10) + str[i]) - 48;
		if ((temp > j) && (nbr == 1))
			return (-1 * nbr);
		else if ((temp > j) && (nbr == -1))
			return (0);
		temp = j;
		i++;
	}
	return (nbr * j);
}
