/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:27:29 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/09/20 19:19:04 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*read_all_lines(int fd)
{
	char	*map_line;
	char	*map;
	char	*tmp;

	map_line = get_next_line(fd);
	if (!map_line)
		exit(0);
	map = ft_strdup("");
	while (map_line)
	{
		tmp = map;
		map = ft_strjoin((const char *)map, (const char *)map_line);
		free(tmp);
		free(map_line);
		map_line = get_next_line(fd);
	}
	free(map_line);
	return (map);
}

char	*gnl_img(char *str)
{
	char	*map;
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = read_all_lines(fd);
	close(fd);
	return (map);
}

int	is_map_line(char *str, int start)
{
	int	j;
	int	found_map_char;

	j = start;
	found_map_char = 0;
	while (str[j] && str[j] == ' ')
		j++;
	while (str[j] && str[j] != '\n')
	{
		if (str[j] == '1' || str[j] == '0')
			found_map_char = 1;
		else if (str[j] != ' ' && str[j] != '1' && str[j] != '0')
			return (0);
		j++;
	}
	return (found_map_char && (j - start) > 10);
}

int	is_empty_line_in_map(char *str, int pos)
{
	int	i;

	if (str[pos] != '\n')
		return (0);
	i = pos + 1;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	is_texture_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'F'
		|| c == 'C');
}
