/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:14:31 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/15 15:07:44 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**split_path(const char *path)
{
	char	**dest;

	dest = ft_split(path, ':');
	return (dest);
}

char	**path_command(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (strncmp("PATH=", envp[i], 5) == 0)
			return (split_path(envp[i] + 5));
		i++;
	}
	return (NULL);
}

char	*command_loc(char **envp, char *av)
{
	char	*tmp_join;
	char	**dest;
	char	*join;
	int		i;

	if (access(av, F_OK) == 0)
		return (ft_strdup(av));
	dest = path_command(envp);
	if (!dest)
		return (NULL);
	i = -1;
	while (dest[++i])
	{
		tmp_join = ft_strjoin(dest[i], "/");
		join = ft_strjoin(tmp_join, av);
		free(tmp_join);
		if (access(join, F_OK) == 0)
		{
			ft_free_array(dest);
			return (join);
		}
		free(join);
	}
	ft_free_array(dest);
	return (NULL);
}

// int main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	printf("la commande se trouve dans ce dossier %s\n", command_loc(envp,
// av[1]));

// 	return (0);
// }