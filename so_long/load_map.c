/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:29:26 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/02/27 16:56:17 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	verif_filename(char *str)
{
	int	j;
	int	i;

	i = ft_strlen(str) - 1;
	if (str == NULL)
	{
		ft_printf("Error\nchaîne NULL\n");
		return (1);
	}
	j = 0;
	while (i >= 0 && str[i] != '.')
		i--;
	if (i < 4 || ft_strcmp(".ber", &str[i]) != 0)
	{
		ft_printf("Error\nMauvais nom, ne lit que les fichier '.ber'\n");
		return (1);
	}
	return (0);
}

void	join(char **map_a, char *map_line, int fd)
{
	char	*tmp;

	while (map_line)
	{
		tmp = *map_a;
		*map_a = ft_strjoin(*map_a, map_line);
		if (!(*map_a))
		{
			free(map_line);
			free(tmp);
			return ;
		}
		free(tmp);
		free(map_line);
		map_line = get_next_line(fd);
	}
	return ;
}

char	*gnl(char *str)
{
	char	*map_line;
	char	*map_a;
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nFichier non valide\n");
		return (0);
	}
	map_line = get_next_line(fd);
	if (map_line == NULL)
	{
		close(fd);
		return (NULL);
	}
	map_a = ft_strdup("");
	if (!map_a)
		close(fd);
	join(&map_a, map_line, fd);
	close(fd);
	return (map_a);
}

int	init_grid(t_data *img, char **av)
{
	img->str = gnl(av[1]);
	if (!img->str)
		return (1);
	if (ft_strnstr(img->str, "\n\n", ft_strlen(img->str)) != NULL)
	{
		ft_printf("Error.\nMap non valide.\n");
		free(img->str);
		return (1);
	}
	img->grid = ft_split((const char *)img->str, '\n');
	if (!img->grid)
	{
		free(img->str);
		return (1);
	}
	img->cpy_grid = ft_split((const char *)img->str, '\n');
	if (!img->cpy_grid)
	{
		free(img->str);
		free_map(img->grid);
		return (1);
	}
	free(img->str);
	return (0);
}

int	load_map(t_data *map)
{
	if (!check_map_rectangle(map) || !check_map_objects(map)
		|| !check_map_borders(map) || !check_valid_path(map))
		return (1);
	return (0);
}
