/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <jroguszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 09:20:27 by jroguszk          #+#    #+#             */
/*   Updated: 2017/12/08 11:00:54 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static	char	make_itoa(int i, int n, char *c)
{
	c[i] = '\0';
	while (i)
	{
		i--;
		c[i] = n % 10 + '0';
		n /= 10;
	}
	return (*c);
}

static	void	check_neg(int *nbr, int *n)
{
	if (*n < 0)
	{
		*n *= -1;
		*nbr = 1;
	}
}

char			*ft_itoa(int n)
{
	int		i;
	int		nbr;
	int		temp;
	char	*c;

	i = 1;
	nbr = 0;
	temp = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	check_neg(&nbr, &n);
	while (temp /= 10)
		i++;
	i += nbr;
	c = (char*)malloc(sizeof(char) * (i + 1));
	if (c == NULL)
		return (NULL);
	else
		make_itoa(i, n, c);
	if (nbr == 1)
		c[0] = '-';
	return (c);
}
