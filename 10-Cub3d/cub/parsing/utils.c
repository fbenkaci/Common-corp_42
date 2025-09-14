/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:27:29 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/09/12 09:35:39 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*gnl_img(char *str)
{
	char	*map_line;
	char	*map;
	char	*tmp;
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (NULL);
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
	close(fd);
	free(map_line);
	if (!validate_file_format(map))
	{
		free(map);
		return (NULL);
	}
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

int is_empty_line_in_map(char *str, int pos)
{
    if (str[pos] != '\n')
        return (0);
    
    int i = pos + 1;

    while (str[i] && str[i] != '\n')
    {
        if (str[i] != ' ' && str[i] != '\t')
            return (0);
        i++;
    }
    
    return (1);
}

int	validate_file_format(char *str)
{
	int	i;
	int	in_map_section;

	i = 0;
	in_map_section = 0;
	while (str[i])
	{
		if (!in_map_section && (i == 0 || str[i - 1] == '\n'))
		{
			if (is_map_line(str, i))
				in_map_section = 1;
		}
		if (in_map_section && is_empty_line_in_map(str, i))
		{
			printf("Error\nEmpty line in map section\n");
			return (0);
		}
		if (in_map_section && (i == 0 || str[i - 1] == '\n'))
		{
			if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W' ||
				str[i] == 'E' || str[i] == 'F' || str[i] == 'C')
			{
				printf("Error\nTexture definition after map\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	free_char_tab(char **tab)
{
    int	i = 0;
    if (!tab)
        return;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

// int	test_map(char **map)
// {
// 	int i;

// 	i = 0;
// 	if (!map)
// 		return (0);
// 	while (map[i] != NULL)
// 	{
// 		if (ft_strlen(map[i]) == 0)
// 		{
// 			printf("Error\nEmpty line in map\n");
// 			return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }