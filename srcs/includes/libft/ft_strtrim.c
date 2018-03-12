/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <jroguszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 13:23:55 by jroguszk          #+#    #+#             */
/*   Updated: 2017/12/08 11:04:32 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*c;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	j = 0;
	while (s[i - 1] == '\n'
				|| s[i - 1] == '\t' || s[i - 1] == ' ')
		i--;
	if (i <= 0)
		return (ft_strdup(""));
	while (s[j] == '\t'
				|| s[j] == '\n' || s[j] == ' ')
		j++;
	k = (i - j);
	if (i == ft_strlen(s) && j == 0)
		c = ft_strdup(s);
	else
		c = ft_strsub(s, j, k);
	if (c == NULL)
		return (NULL);
	return (c);
}
