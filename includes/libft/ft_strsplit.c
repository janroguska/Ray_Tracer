/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <jroguszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 15:50:30 by jroguszk          #+#    #+#             */
/*   Updated: 2017/12/08 11:04:20 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static	int		count_words(char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s[j] != c && s[j] != '\0')
		i++;
	while (s[j])
	{
		if (s[j] != c && s[j - 1] == c)
			i++;
		j++;
	}
	return (i);
}

static	char	*make_word(char const *s, char c, int *k)
{
	int		i;
	char	*a;

	if ((a = (char*)malloc(sizeof(a) * (ft_strlen(s)))) == NULL)
		return (NULL);
	i = 0;
	while (s[*k] != c && s[*k])
	{
		a[i] = s[*k];
		i++;
		*k += 1;
	}
	a[i] = '\0';
	while (s[*k] == c && s[*k] != '\0')
		*k += 1;
	return (a);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**a;

	if (s == NULL)
		return (NULL);
	i = count_words(s, c);
	j = 0;
	k = 0;
	if ((a = (char**)malloc(sizeof(a) * (i + 2))) == NULL)
		return (NULL);
	while (s[k] == c && s[k])
		k++;
	while (j < i && s[k])
	{
		a[j] = make_word(s, c, &k);
		j++;
	}
	a[j] = NULL;
	return (a);
}
