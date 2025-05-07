/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:12:04 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/07 17:28:18 by fbenkaci         ###   ########.fr       */
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
	int	i;
	int	j;
	int	k;

	data->nb_cmds = ac - 3;
	data->pids = malloc(sizeof(int) * data->nb_cmds);
	if (!data->pids)
		return (1);
	data->pipes = malloc(sizeof(int *) * (2 * (data->nb_cmds - 1)));
	if (!data->pipes)
		return (1);
	i = 0;
	while (i < data->nb_cmds - 1)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		if (!data->pipes[i])
		{
			while (i < data->nb_cmds - 1)
			{
				free(data->pipes[i]);
				i--;
			}
			free(data->pipes);
			free(data->pids);
			return (1);
		}
		if (pipe(data->pipes[i]) == -1)
		{
			while (i >= 0)
				free(data->pipes[i--]);
			free(data->pipes);
			free(data->pids);
			return (1);
		}
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
	while (i < data->nb_cmds)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			return (1);
		if (data->pids[i] == 0)
		{
			k = 0;
			while (k < data->nb_cmds - 1)
			{
				if (k != i)
					close(data->pipes[k][1]);
				if (k != i - 1)
					close(data->pipes[k][0]);
				k++;
			}
			data->cmd = ft_split(av[j], ' ');
			if (!data->cmd)
				return (1);
			process_command(data, av, envp);
			if (!data->path)
				return (1);
			if (i == 0)
			{
				if (dup2(data->inputfd, STDIN_FILENO) == -1
					|| dup2(data->pipes[0][1], STDOUT_FILENO) == -1)
					return (1);
				close(data->inputfd);
				close(data->pipes[0][1]);
				close(data->outputfd);
			}
			else if (i == data->nb_cmds - 1)
			{
				if (dup2(data->pipes[i - 1][0], 0) == -1 || dup2(data->outputfd,
						1) == -1)
					return (1);
				close(data->pipes[i - 1][0]);
				close(data->outputfd);
				close(data->inputfd);
			}
			else
			{
				if (dup2(data->pipes[i - 1][0], 0) == -1
					|| dup2(data->pipes[i][1], 1) == -1)
					return (1);
				close(data->pipes[i - 1][0]);
				close(data->pipes[i][1]);
				close(data->inputfd);
				close(data->outputfd);
			}
			free(data->pids);
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
	while (i < data->nb_cmds - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		free(data->pipes[i]);
		i++;
	}
	free(data->pipes);
	close(data->outputfd);
	close(data->inputfd);
	i = 0;
	while (i < data->nb_cmds - 1)
		waitpid(data->pids[i++], NULL, 0);
	free(data->pids);
	return (0);
}
