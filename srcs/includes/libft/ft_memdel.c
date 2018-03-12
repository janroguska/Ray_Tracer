/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <jroguszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 16:09:14 by jroguszk          #+#    #+#             */
/*   Updated: 2017/12/08 11:01:48 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_memdel(void **ap)
{
	size_t	i;

	i = 0;
	if (ap != NULL)
	{
		free(*ap);
		while (i < sizeof(*ap))
		{
			((char*)ap)[i] = 0;
			i++;
		}
	}
}
