/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:09:11 by vcastilh          #+#    #+#             */
/*   Updated: 2022/12/12 18:35:20 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	n;
	size_t	i;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			n++;
			while (s[i] != c && s[i] != '\0')
			{
				i++;
			}
		}
	}
	return (n);
}

static char	**ft_get_words(char const *s, char c, size_t num_words)
{
	size_t	i;
	size_t	j;
	char	**arr;

	j = 0;
	arr = ft_calloc((num_words + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	while (num_words--)
	{
		i = 0;
		while (*s == c)
			s++;
		while (s[i] != c && s[i] != '\0')
			i++;
		arr[j] = ft_calloc((i + 1), sizeof(char));
		if (!*arr)
			return (NULL);
		i = 0;
		while (*s != c && *s)
			arr[j][i++] = *s++;
		arr[j][i] = '\0';
		j++;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	num_words;
	char	**arr;

	if (!s)
		return (NULL);
	num_words = ft_count_words(s, c);
	arr = ft_get_words(s, c, num_words);
	return (arr);
}
