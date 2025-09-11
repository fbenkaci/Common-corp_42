/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:39:24 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/08/19 16:48:05 by wlarbi-a         ###   ########.fr       */
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

void	map(t_data *data)
{
	int		i;
	int		j;
	int		map_start;
	int		texture;
	char	first_char;

	texture = 0;
	i = 0;
	while (data->file[i])
	{
		first_char = get_first_non_space_char(data->file[i]);
		if (first_char == 'N' || first_char == 'S' || first_char == 'W' ||
			first_char == 'E' || first_char == 'F' || first_char == 'C')
		{
			texture++;
		}
		else if (first_char != '\0')
		{
			break ;
		}
		i++;
	}
	data->file2 = malloc(sizeof(char *) * (texture + 1));
	j = 0;
	while (j < texture)
	{
		data->file2[j] = ft_strdup(data->file[j]);
		j++;
	}
	data->file2[texture] = NULL;
	map_start = texture;
	map_start = i;
	j = 0;
	while (data->file[i + j])
		j++;
	data->map = malloc(sizeof(char *) * (j + 1));
	if (!data->map)
		return ;
	j = 0;
	while (data->file[map_start + j])
	{
		data->map[j] = ft_strdup(data->file[map_start + j]);
		j++;
	}
	data->map[j] = NULL;
}

int	map_error_top_bottom(char **map)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map[0][j] != '\0')
	{
		if (map[0][j] != '1' && map[0][j] != ' ')
		{
			printf("%s", "Error\nMap has to be surrounded by walls\n");
			return (0);
		}
		j++;
	}
	j = 0;
	while (map[i] != NULL)
		i++;
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
				return (0);
		}
		i++;
	}
	return (1);
}

int	flood_fill(t_data *data, int x, int y, char **copy_map)
{
	if (y < 0 || x < 0)
		return (0);
	if (copy_map[x][y] == 'F' || copy_map[x][y] == '1' || copy_map[x][y] == ' ')
		return (0);
	copy_map[x][y] = 'F';
	flood_fill(data, x - 1, y, copy_map);
	flood_fill(data, x + 1, y, copy_map);
	flood_fill(data, x, y - 1, copy_map);
	flood_fill(data, x, y + 1, copy_map);
	return (1);
}

int	verif_path(char **map)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0')
			{
				if ((i > 0 && map[i - 1][j] == ' ') ||
					(map[i + 1] && map[i + 1][j] == ' ') ||
					(j > 0 && map[i][j - 1] == ' ') ||
					(j < (int)ft_strlen(map[i]) - 1 && map[i][j + 1] == ' '))
				{
					printf("error space near floor\n");
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_verif(t_data data)
{
	if (map_error_top_bottom(data.map) == 1 && map_error(data.map) == 1
		&& map_error_sides(data.map) == 1 && verif_path(data.map) == 1
		&& map_things(&data) == 1 && file_things(&data) == 1)
	{
		printf("good map");
	}
	else
	{
		printf("error");
	}
}

void	coordinates(t_data *data, char **map)
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
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
			{
				data->player.x = i;
				data->player.y = j;
			}
			j++;
		}
		i++;
	}
}

int	map_count(t_data *data, char obj)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (data->map[i] != NULL)
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] == obj)
			{
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

int	map_things(t_data *data)
{
	int	total_players;

	total_players = map_count(data, 'W') + map_count(data, 'N') +
		map_count(data, 'S') + map_count(data, 'E');
	if (total_players != 1)
	{
		printf("Error\nMap must have exactly one player (W, N, S, or E)\n");
		return (0);
	}
	return (1);
}

int	get_first_non_space_index(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

int	file_things(t_data *data)
{
	int		i;
	char	first_char;
	int		index;
	char	next_char;

	i = 0;
	while (data->file2[i] != NULL)
	{
		if (data->file2[i])
		{
			index = get_first_non_space_index(data->file2[i]);
			first_char = data->file2[i][index];
			next_char = data->file2[i][index + 1];
			if (!((first_char == 'N' && next_char == 'O') || (first_char == 'S'
						&& next_char == 'O') || (first_char == 'W'
						&& next_char == 'E') || (first_char == 'E'
						&& next_char == 'A') || (first_char == 'F'
						&& next_char == ' ') || (first_char == 'C'
						&& next_char == ' ') ||
					first_char == '\0'))
			{
				printf("error, file2 not good\n");
				return (0);
			}
            if (!validate_texture_line(data->file2[i]))
                return (0);
		}
		i++;
	}
	return (1);
}
