// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   handle_pipex.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/05 17:12:04 by fbenkaci          #+#    #+#             */
// /*   Updated: 2025/05/11 20:38:20 by fbenkaci         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "pipex.h"

// int	creat_pipe(t_pipex *data)
// {
// 	int	i;

// 	i = 0;
// 	data->pipes = malloc(sizeof(int *) * (data->nb_cmds - 1));
// 	if (!data->pipes)
// 	{
// 		free(data->pids);
// 		return (0);
// 	}
// 	while (i < data->nb_cmds - 1)
// 	{
// 		data->pipes[i] = malloc(sizeof(int) * 2);
// 		if (!data->pipes[i])
// 		{
// 			free_pipes(data, &i);
// 			return (0);
// 		}
// 		if (pipe(data->pipes[i]) == -1)
// 		{
// 			free_pipes(data, &i);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// void	free_close_pipes(t_pipex *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->nb_cmds - 1)
// 	{
// 		close(data->pipes[i][0]);
// 		close(data->pipes[i][1]);
// 		free(data->pipes[i]);
// 		i++;
// 	}
// 	free(data->pipes);
// 	close(data->outputfd);
// 	close(data->inputfd);
// 	i = 0;
// 	while (i < data->nb_cmds - 1)
// 		waitpid(data->pids[i++], NULL, 0);
// 	free(data->pids);
// }

// int	process_command2(t_pipex *data, char **envp, int *i)
// {
// 	data->path = command_loc(envp, data->cmd[0]);
// 	if (!data->path)
// 	{
// 		ft_putstr_fd("Command not found: ", 2);
// 		ft_putstr_fd(data->cmd[0], 2);
// 		ft_putstr_fd("\n", 2);
// 		close_input_output(data);
// 		ft_free_array(data->cmd);
// 		*i = 0;
// 		while (*i < data->nb_cmds - 1)
// 		{
// 			close(data->pipes[*i][0]);
// 			close(data->pipes[*i][1]);
// 			free(data->pipes[*i]);
// 			(*i)++;
// 		}
// 		free(data->pipes);
// 		free(data->pids);
// 		exit(127);
// 	}
// 	return (1);
// }

// void	execution2(t_pipex *data, char **envp, int *i)
// {
// 	if (execve(data->path, data->cmd, envp) == -1)
// 	{
// 		ft_putstr_fd("Execution: failed", 2);
// 		perror(data->cmd[0]);
// 		free(data->path);
// 		ft_free_array(data->cmd);
// 		close_input_output(data);
// 		*i = 0;
// 		while (*i < data->nb_cmds - 1)
// 		{
// 			close(data->pipes[*i][0]);
// 			close(data->pipes[*i][1]);
// 			free(data->pipes[*i]);
// 			(*i)++;
// 		}
// 		free(data->pipes);
// 	}
// 	exit(126);
// }

// int	launch_all_commands(t_pipex *data, char **envp, char **av)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 2;
// 	while (i < data->nb_cmds)
// 	{
// 		data->pids[i] = fork();
// 		if (data->pids[i] == -1)
// 		{
// 			perror("Fork failed");
// 			while (--i >= 0)
// 				kill(data->pids[i], SIGTERM);
// 			i = 0;
// 			while (i < data->nb_cmds - 1)
// 			{
// 				close(data->pipes[i][0]);
// 				close(data->pipes[i][1]);
// 				free(data->pipes[i]);
// 				i++;
// 			}
// 			free(data->pipes);
// 			close(data->outputfd);
// 			close(data->inputfd);
// 			free(data->pids);
// 			return (0);
// 		}
// 		if (data->pids[i] == 0)
// 		{
// 			close_unnecessary_pipes(data, i);
// 			data->cmd = ft_split(av[j], ' ');
// 			if (!data->cmd)
// 			{
// 				i = 0;
// 				while (i < data->nb_cmds - 1)
// 				{
// 					close(data->pipes[i][0]);
// 					close(data->pipes[i][1]);
// 					free(data->pipes[i]);
// 					i++;
// 				}
// 				free(data->pipes);
// 				close(data->outputfd);
// 				close(data->inputfd);
// 				free(data->pids);
// 				exit(1);
// 			}
// 			process_command2(data, envp, &i);
// 			if (setup_redirections(data, i) == 0)
// 			{
// 				perror("Redirection faild.");
// 				i = 0;
// 				while (i < data->nb_cmds - 1)
// 				{
// 					close(data->pipes[i][1]);
// 					close(data->pipes[i][0]);
// 					free(data->pipes[i]);
// 					i++;
// 				}
// 				free(data->pipes);
// 				free(data->path);
// 				ft_free_array(data->cmd);
// 				close_input_output(data);
// 				free(data->pids);
// 				exit(1);
// 			}
// 			free(data->pids);
// 			execution2(data, envp, &i);
// 		}
// 		i++;
// 		j++;
// 	}
// 	return (1);
// }

// int	handle_pipex(t_pipex *data, int ac, char **av, char **envp)
// {
// 	data->nb_cmds = ac - 3;
// 	data->pids = malloc(sizeof(int) * data->nb_cmds);
// 	if (!data->pids)
// 		return (0);
// 	if (creat_pipe(data) == 0)
// 		return (0);
// 	data->inputfd = check_infile_exist(av);
// 	if (data->inputfd == -1)
// 		return (0);
// 	data->outputfd = check_outfile_exist2(av, ac);
// 	if (data->outputfd == -1)
// 		return (0);
// 	if (launch_all_commands(data, envp, av) == 0)
// 		return (0);
// 	free_close_pipes(data);
// 	return (1);
// }
