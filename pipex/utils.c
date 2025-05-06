/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:14:21 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/04 17:04:13 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	executioon(t_pipex *data, char **envp)
{
	if (execve(data->path, data->args, envp) == 1)
	{
		perror("Execution: failed");
		ft_free_array(data->args);
		free(data->path);
		return (1);
	}
	return (0);
}

int	error_cmd(char **cmd)
{
	if (!cmd)
	{
		perror("Memory allocation failed");
		return (1);
	}
	return (0);
}

void	args_second(t_pipex *data, char **av, char **cmd)
{
	data->args = ft_split(av[3], ' ');
	if (!data->args)
	{
		ft_free_array(data->cmd);
		ft_free_array(cmd);
		free(data->path);
		close(data->fd[1]);
		exit(1);
	}
}

void	process_command(t_pipex *data, char **av, char **envp)
{
	data->path = command_loc(envp, data->cmd[0]);
	if (!data->path)
	{
		perror("Command not found");
		ft_free_array(data->cmd);
		close(data->fd[1]);
		exit(127);
	}
	data->args = ft_split(av[2], ' ');
	if (!data->args)
	{
		ft_free_array(data->cmd);
		close(data->fd[1]);
		exit(1);
	}
}
