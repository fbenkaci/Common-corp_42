/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 01:16:09 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/13 01:16:17 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s2[i] == s1[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	strlen_split(const char *s, char c)
{
	int	j;

	j = 0;
	while (*s != c && *s++)
		j++;
	return (j);
}

static int	count_words_split(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if ((*s != c && *(s + 1) == c) || (*s != c && *(s + 1) == '\0'))
			i++;
		s++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	k;
	char	**result;

	i = 0;
	k = 0;
	result = malloc((count_words_split(s, c) + 1) * sizeof(char *));
	if (!result || !s)
		return (free(result), NULL);
	while (*s == c && *s)
		s++;
	while (*s)
	{
		result[k] = malloc(strlen_split(s, c) + 1);
		if (!result[k])
			return (NULL);
		while (*s != c && *s)
			result[k][i++] = *s++;
		result[k++][i] = '\0';
		i = 0;
		while (*s == c && *s)
			s++;
	}
	return (result[k] = NULL, result);
}
