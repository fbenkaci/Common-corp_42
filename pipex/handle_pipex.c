/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:12:04 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/07 16:31:21 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_outfile_exist2(char **av, int ac)
{
	int	fd;

	fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening outfile");
		return (-1);
	}
	return (fd);
}

int	handle_pipex(t_pipex *data, int ac, char **av, char **envp)
{
	int	nb_cmds = ac - 3;
	int	pids[nb_cmds];
	int	i;
	int	pipes[2 * (nb_cmds - 1)][2];
	int	j;
	// int	status = 0;
	int	k;
	// data->inputfd = 0;
	// data->outputfd = 0;
	i = 0;
	while (i < nb_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
			return (1);
		i++;
	}
	i = 0;
	j = 2;
	data->inputfd = check_infile_exist(av);
	if (data->inputfd == -1)
		return (1);
	data->outputfd = check_outfile_exist2(av, ac);
	if (data->outputfd == -1)
		return (1);
	while (i < nb_cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (1);
		if (pids[i] == 0)
		{
			// Close pipes
			k = 0;
			while (k < nb_cmds - 1)
			{
				if (k != i)
					close(pipes[k][1]);
				if (k != i - 1)
					close(pipes[k][0]);
				k++;	
			}
			// Close pipes
			
			data->cmd = ft_split(av[j], ' ');
			if (!data->cmd)
				return (1);
			process_command(data, av, envp);
			if (!data->path)
				return (1);
			if (i == 0)
			{
				if (dup2(data->inputfd, STDIN_FILENO) == -1 || dup2(pipes[0][1],
						STDOUT_FILENO) == -1)
					return (1);
				close(data->inputfd);
				close(pipes[0][1]);
				close(data->outputfd);
			}
			else if (i == nb_cmds - 1)
			{
				if (dup2(pipes[i - 1][0], 0) == -1 || dup2(data->outputfd, 1) ==
					-1)
					return (1);
				close(pipes[i - 1][0]);
				close(data->outputfd);
				close(data->inputfd);
			}
			else
			{
				if (dup2(pipes[i - 1][0], 0) == -1 || dup2(pipes[i][1], 1) ==
					-1)
					return (1);
				close(pipes[i - 1][0]);
				close(pipes[i][1]);
				close(data->inputfd);
				close(data->outputfd);
			}
			if (execve(data->path, data->cmd, envp) == 1)
			{
				perror("Execution: failed");
				free(data->path);
				close(data->inputfd);
				return (1);
			}
		}
		i++;
		j++;
	}
	i = 0;
	while (i < nb_cmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	close(data->outputfd);
	close(data->inputfd);
	i = 0;
	while (i < nb_cmds - 1)
		waitpid(pids[i++], NULL, 0);
	
	return (0);
}
