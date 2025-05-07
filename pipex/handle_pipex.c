/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:12:04 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/06 22:34:34 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_pipex(t_pipex *data, int ac, char **av, char **envp)
{
	char	**cmd;
	int		nb_cmds = ac - 3;
	int		pids[nb_cmds];
	int		i;
	int		pipes[2 * (nb_cmds - 1)][2];
	int		j;

	// nb_cmds = ac - 3;
	i = 0;
	while (i < nb_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
			return (1);
		i++;
	}
	i = 0;
	j = 2;
	while (i < nb_cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (1);
		if (pids[i] == 0)
		{
			// Close pipes
			cmd = ft_split(av[j], ' ');
			if (!cmd)
				return (1);
			data->path = command_loc(envp, cmd[0]);
			if (!data->path)
				return (1);
			data->inputfd = check_infile_exist(av);
			if (data->inputfd == -1)
				return (1);
			if (i == 0)
			{
				if (dup2(data->inputfd, 0) == -1 || dup2(pipes[0][1], 1) == -1)
					return (1);
			}
			else
			{
				if (dup2(pipes[i - 1][0], 0) == -1 || dup2(pipes[i][1], 1) == -1)
					return (1);
			}
            if (!data->args)
                return (1);
			if (execve(data->path, cmd, envp) == 1)
			{
				perror("Execution: failed");
				free(data->path);
				close(data->inputfd);
				return (1);
			}
			// Close pipes
		}
		i++;
        j++;
	}
	return (0);
}
