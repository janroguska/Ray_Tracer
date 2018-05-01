/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <jroguszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:18:03 by jroguszk          #+#    #+#             */
/*   Updated: 2017/12/08 11:03:50 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		j;
	char	*c;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	j = ft_strlen(s);
	c = (char*)malloc(sizeof(char) * (j + 1));
	if (c != NULL)
	{
		while (s[i])
		{
			c[i] = f(i, s[i]);
			i++;
		}
		c[i] = '\0';
		return (c);
	}
	else
		return (NULL);
}
