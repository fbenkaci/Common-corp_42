/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:37:17 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/09/20 19:16:50 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_verif(t_data data)
{
	if (map_error(data.map) == 1 && map_error_sides(data.map) == 1
		&& verif_path(data.map) == 1 && verif_path2(data.map) == 1
		&& map_things(&data) == 1 && file_things(&data) == 1
		&& check_top_line(data.map) == 1 && check_bottom_line(data.map) == 1)
		return (1);
	else
		return (0);
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
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
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

	total_players = map_count(data, 'W') + map_count(data, 'N')
		+ map_count(data, 'S') + map_count(data, 'E');
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
