/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:16:32 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/12 12:47:16 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execution2(t_pipex *data, char **envp)
{
	int	k;

	if (execve(data->path, data->cmd, envp) == -1)
	{
		ft_putstr_fd("Execution: failed\n", 2);
		perror(data->cmd[0]);
		free(data->path);
		ft_free_array(data->cmd);
		close(data->inputfd);
		close(data->outputfd);
		k = 0;
		while (k < (data->nb_cmds - 1) * 2)
		{
			close(data->pipes[k]);
			k++;
		}
		free(data->pipes);
		exit(126);
	}
}

int	process_command2(t_pipex *data, char **envp)
{
	int	k;

	data->path = command_loc(envp, data->cmd[0]);
	if (!data->path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(data->cmd[0], 2);
		ft_putstr_fd("\n", 2);
		close(data->inputfd);
		close(data->outputfd);
		ft_free_array(data->cmd);
		k = 0;
		while (k < (data->nb_cmds - 1) * 2)
		{
			close(data->pipes[k]);
			k++;
		}
		free(data->pipes);
		free(data->pids);
		exit(127);
	}
	return (1);
}

int	creat_pipe(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds - 1)
	{
		if (pipe(&data->pipes[i * 2]) == -1)
		{
			perror("pipe");
			return (0);
		}
		i++;
	}
	return (1);
}

void	close_unnecessary_pipes(t_pipex *data, int i)
{
	int	k;

	k = 0;
	while (k < data->nb_cmds - 1)
	{
		if (k != i - 1)
			close(data->pipes[k * 2]);
		if (k != i)
			close(data->pipes[k * 2 + 1]);
		k++;
	}
}

void	free_close_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds - 1)
	{
		close(data->pipes[i * 2]);
		close(data->pipes[i * 2 + 1]);
		i++;
	}
	close(data->outputfd);
	close(data->inputfd);
	i = 0;
	while (i < data->nb_cmds)
	{
		waitpid(data->pids[i], NULL, 0);
		i++;
	}
	free(data->pids);
	free(data->pipes);
}
