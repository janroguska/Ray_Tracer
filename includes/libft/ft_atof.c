/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:11:23 by jroguszk          #+#    #+#             */
/*   Updated: 2018/03/09 13:11:25 by jroguszk         ###   ########.fr       */
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

static	double	check_negative(char str)
{
	if (str == '-')
		return (-1.0);
	else
		return (1.0);
}

static	double	ft_atof_decimal(t_atof *a, const char *str)
{
	int		i;
	int		j;

	a->i++;
	i = a->i;
	j = 1.0;
	while ((str[i] >= 48 && str[i] <= 57) && str[i])
	{
		j *= 10;
		i++;
	}
	return (j);
}

static	void	set_values(t_atof *a)
{
	a->i = 0.0;
	a->temp = 0.0;
	a->nbr = 1.0;
	a->j = 0.0;
	a->k = 1.0;
}

double			ft_atof(const char *str)
{
	t_atof	a;

	set_values(&a);
	while (check_num(str[a.i]) == 1)
		a.i++;
	a.nbr = check_negative(str[a.i]);
	if (str[a.i] == '-' || str[a.i] == '+')
		a.i++;
	while (((str[a.i] >= 48 && str[a.i] <= 57) || str[a.i] == '.') && str[a.i])
	{
		if (str[a.i] == '.' && a.k == 1.0 &&
			(str[a.i - 1] >= 48 && str[a.i - 1] <= 57))
			a.k = ft_atof_decimal(&a, str);
		a.j = ((a.j * 10) + str[a.i]) - 48;
		if ((a.temp > a.j) && (a.nbr == 1))
			return (-1 * a.nbr);
		else if ((a.temp > a.j) && (a.nbr == -1))
			return (0.0);
		a.temp = a.j;
		a.i++;
	}
	return ((a.nbr * a.j) / a.k);
}
