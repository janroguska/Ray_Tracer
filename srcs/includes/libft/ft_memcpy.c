/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <jroguszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 18:04:42 by jroguszk          #+#    #+#             */
/*   Updated: 2017/12/08 11:01:45 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*srccpy;
	char	*dstcpy;

	i = 0;
	if (n == 0 || dst == src)
		return (dst);
	srccpy = (char*)src;
	dstcpy = (char*)dst;
	while (i < n)
	{
		dstcpy[i] = srccpy[i];
		i++;
	}
	return (dstcpy);
}
