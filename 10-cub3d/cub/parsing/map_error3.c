/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:46:59 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/09/20 19:25:59 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	i = -1;
	while (++i, map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0')
			{
				if ((i > 0 && (j >= (int)ft_strlen(map[i - 1]) || map[i
								- 1][j] == ' ')) ||
					(map[i + 1] && (j >= (int)ft_strlen(map[i + 1]) || map[i
								+ 1][j] == ' ')) ||
					(j > 0 && map[i][j - 1] == ' ') ||
					(j < (int)ft_strlen(map[i]) - 1 && map[i][j + 1] == ' '))
					return (printf("Error: space near floor\n"), 0);
			}
			j++;
		}
	}
	return (1);
}

int	verif_path2(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (++i, map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				if ((i > 0 && (j >= (int)ft_strlen(map[i - 1]) || map[i
								- 1][j] == ' ')) ||
					(map[i + 1] && (j >= (int)ft_strlen(map[i + 1]) || map[i
								+ 1][j] == ' ')) ||
					(j > 0 && map[i][j - 1] == ' ') ||
					(j < (int)ft_strlen(map[i]) - 1 && map[i][j + 1] == ' '))
					return (printf("Error: space near player\n"), 0);
			}
			j++;
		}
	}
	return (1);
}

int	is_valid_texture_prefix(char first_char, char next_char)
{
	if ((first_char == 'N' && next_char == 'O') || (first_char == 'S'
			&& next_char == 'O') || (first_char == 'W' && next_char == 'E')
		|| (first_char == 'E' && next_char == 'A') || (first_char == 'F'
			&& next_char == ' ') || (first_char == 'C' && next_char == ' ')
		|| first_char == '\0')
		return (1);
	return (0);
}

void	count_texture_identifiers(t_data *data, int *counts)
{
	int		i;
	int		index;
	char	first_char;
	char	next_char;

	i = 0;
	while (data->file2[i] != NULL)
	{
		index = get_first_non_space_index(data->file2[i]);
		first_char = data->file2[i][index];
		next_char = data->file2[i][index + 1];
		if (first_char == 'N' && next_char == 'O')
			counts[0]++;
		else if (first_char == 'S' && next_char == 'O')
			counts[1]++;
		else if (first_char == 'W' && next_char == 'E')
			counts[2]++;
		else if (first_char == 'E' && next_char == 'A')
			counts[3]++;
		else if (first_char == 'F' && next_char == ' ')
			counts[4]++;
		else if (first_char == 'C' && next_char == ' ')
			counts[5]++;
		i++;
	}
}
