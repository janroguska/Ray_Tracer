/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <jroguszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 11:49:18 by jroguszk          #+#    #+#             */
/*   Updated: 2017/12/08 11:03:41 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while ((dst[i]) && i < size)
		i++;
	j = i;
	if (i < size)
	{
		while ((src[k]) && i < size - 1)
		{
			dst[i] = src[k];
			i++;
			k++;
		}
	}
	if (j < size)
		dst[i] = '\0';
	return (j + ft_strlen(src));
}
