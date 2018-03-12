/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <jroguszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:04:58 by jroguszk          #+#    #+#             */
/*   Updated: 2017/12/08 11:01:52 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*srccpy;
	unsigned char	*dstcpy;

	srccpy = (unsigned char*)src;
	dstcpy = (unsigned char*)dst;
	if (srccpy < dstcpy)
	{
		while (len--)
			dstcpy[len] = srccpy[len];
	}
	else
		ft_memcpy(dstcpy, srccpy, len);
	return (dstcpy);
}
