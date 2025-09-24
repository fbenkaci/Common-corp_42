/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:43:02 by leogarci          #+#    #+#             */
/*   Updated: 2025/02/13 13:45:41 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	skip_line(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_uptstrjoin(char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen((char *)s2) + 1);
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_free(ssize_t bytes_read, char *tmp, char *str)
{
	if (!tmp)
	{
		free(str);
		return (NULL);
	}
	if (bytes_read < 0)
	{
		free(tmp);
		free(str);
		return (NULL);
	}
	if (!str)
	{
		free(tmp);
		return (NULL);
	}
	return (NULL);
}

char	*get_a_line(int fd, char *str)
{
	char	*tmp;
	ssize_t	bytes_read;

	bytes_read = 1;
	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (ft_free(bytes_read, tmp, str));
	while (!skip_line(str) && bytes_read > 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free(bytes_read, tmp, str));
		tmp[bytes_read] = '\0';
		str = ft_uptstrjoin(str, tmp);
		if (!str)
			return (ft_free(bytes_read, tmp, str));
	}
	free(tmp);
	if (bytes_read == 0 && !str[0])
	{
		free(str);
		return (NULL);
	}
	return (str);
}

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (0);
// 	while (str[i])
// 		i++;
// 	return (i);
// }
