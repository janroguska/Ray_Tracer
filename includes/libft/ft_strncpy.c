/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <jroguszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 10:04:36 by jroguszk          #+#    #+#             */
/*   Updated: 2017/12/08 15:52:14 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		if (src[i])
			dst[i] = src[i];
		else
			while (i < len)
			{
				dst[i] = '\0';
				i++;
			}
		i++;
	}
	return (dst);
}
