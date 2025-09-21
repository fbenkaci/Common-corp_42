/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:39:24 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/09/20 16:55:45 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	get_first_non_space_char(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (line[i]);
}

int	check_top_line(char **map)
{
	int	j;

	j = 0;
	if (map[0] == NULL)
		return (0);
	while (map[0][j] != '\0')
	{
		if (map[0][j] != '1' && map[0][j] != ' ')
		{
			printf("%s", "Error\nMap has to be surrounded by walls\n");
			return (0);
		}
		j++;
	}
	return (1);
}

int	check_bottom_line(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
		i++;
	if (i == 0)
		return (0);
	while (map[i - 1][j] != '\0')
	{
		if (map[i - 1][j] != '1' && map[i - 1][j] != ' ')
		{
			printf("%s", "Error\nMap has to be surrounded by walls\n");
			return (0);
		}
		j++;
	}
	return (1);
}

int	map_error(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '1' && map[i][j] != 'N' && map[i][j] != 'S'
				&& map[i][j] != 'E' && map[i][j] != 'W' && map[i][j] != '0'
				&& map[i][j] != ' ')
			{
				printf("%s", "Error\nMap is not good\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	map_error_sides(char **map)
{
	int	i;
	int	len;
	int	start;
	int	end;

	i = 0;
	while (map[i] != NULL)
	{
		len = ft_strlen(map[i]);
		start = 0;
		end = len - 1;
		while (start < len && map[i][start] == ' ')
			start++;
		while (end >= 0 && map[i][end] == ' ')
			end--;
		if (start < len && end >= 0)
		{
			if (map[i][start] != '1' || map[i][end] != '1')
				return (printf("%s",
						"Error\nMap has to be surrounded by walls\n"), 0);
		}
		i++;
	}
	return (1);
}
