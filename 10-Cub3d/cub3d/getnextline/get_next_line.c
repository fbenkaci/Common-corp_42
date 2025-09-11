/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:20:57 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/02/13 12:26:58 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_line_buffer(int fd, char *left_c, char *buffer)
{
	ssize_t	byte_read;
	char	*left_c_old;

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read <= 0)
			break ;
		buffer[byte_read] = '\0';
		left_c_old = left_c;
		if (!left_c)
			left_c = ft_strdup(buffer);
		else
			left_c = ft_strjoin(left_c, buffer);
		free(left_c_old);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (byte_read == -1 || !left_c)
	{
		free(left_c);
		return (NULL);
	}
	return (left_c);
}

char	*set_line(char *line_buffer)
{
	char	*sub_line_buffer;
	int		i;

	i = 0;
	if (line_buffer[i] == '\0')
		return (NULL);
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	sub_line_buffer = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*sub_line_buffer == 0)
	{
		free(sub_line_buffer);
		sub_line_buffer = NULL;
	}
	if (line_buffer[i] == '\n')
		line_buffer[i + 1] = '\0';
	else
		line_buffer[i] = '\0';
	return (sub_line_buffer);
}

char	*get_next_line(int fd)
{
	static char	*left_c;
	char		*buffer;
	char		*line;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
	{
		free(left_c);
		free(buffer);
		left_c = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, left_c, buffer);
	free(buffer);
	if (!line)
	{
		free(left_c);
		left_c = NULL;
		return (NULL);
	}
	left_c = set_line(line);
	return (line);
}
