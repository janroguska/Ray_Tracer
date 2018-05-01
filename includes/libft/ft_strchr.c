/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <jroguszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 10:09:33 by jroguszk          #+#    #+#             */
/*   Updated: 2017/12/08 11:02:52 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (((char)c != (char)s[i]) && ((char)s[i]))
		i++;
	if ((char)c == (char)s[i])
		return ((char*)s + i);
	else
		return (0);
}
