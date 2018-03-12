/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <jroguszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 13:11:03 by jroguszk          #+#    #+#             */
/*   Updated: 2018/01/05 16:53:11 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *dest;
	char *out;

	if (s1 && s2)
	{
		dest = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
		if (dest)
		{
			out = dest;
			while (*s1 != 0)
				*dest++ = *s1++;
			while (*s2 != 0)
				*dest++ = *s2++;
			return (out);
		}
		else
		{
			return (NULL);
		}
	}
	else
		return (NULL);
}
