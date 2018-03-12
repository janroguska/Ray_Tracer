/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <jroguszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:58:55 by jroguszk          #+#    #+#             */
/*   Updated: 2017/12/08 11:03:23 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str;

	i = ft_strlen(s1);
	str = (char*)malloc(sizeof(char) * (i + 1));
	if (str != NULL)
	{
		ft_strcpy(str, s1);
		return (str);
	}
	else
		return (NULL);
}
