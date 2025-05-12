// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   utils_2.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/08 16:16:46 by fbenkaci          #+#    #+#             */
// /*   Updated: 2025/05/11 20:41:48 by fbenkaci         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "pipex.h"

// int	check_outfile_exist2(char **av, int ac)
// {
// 	int	fd;

// 	fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		perror("Error opening outfile");
// 		return (-1);
// 	}
// 	return (fd);
// }

// void	close_unnecessary_pipes(t_pipex *data, int i)
// {
// 	int	k;

// 	k = 0;
// 	while (k < data->nb_cmds - 1)
// 	{
// 		if (k != i)
// 			close(data->pipes[k][1]);
// 		if (k != i - 1)
// 			close(data->pipes[k][0]);
// 		k++;
// 	}
// }

// void	close_input_output(t_pipex *data)
// {
// 	close(data->outputfd);
// 	close(data->inputfd);
// }

// void	free_pipes(t_pipex *data, int *i)
// {
// 	int	j;

// 	j = *i;
// 	while (j >= 0)
// 	{
// 		free(data->pipes[j]);
// 		j--;
// 	}
// 	free(data->pipes);
// 	free(data->pids);
// }

// // int	setup_redirections(t_pipex *data, int i)
// // {
// // 	if (i == 0)
// // 	{
// // 		if (dup2(data->inputfd, 0) == -1 || dup2(data->pipes[0][1], 1) == -1)
// // 			return (0);
// // 		close(data->pipes[0][1]);
// // 		close_input_output(data);
// // 	}
// // 	else if (i == data->nb_cmds - 1)
// // 	{
// // 		if (dup2(data->pipes[i - 1][0], 0) == -1 || dup2(data->outputfd, 1) ==
// // 			-1)
// // 			return (0);
// // 		close(data->pipes[i - 1][0]);
// // 		close_input_output(data);
// // 	}
// // 	else
// // 	{
// // 		if (dup2(data->pipes[i - 1][0], 0) == -1 || dup2(data->pipes[i][1],
// // 				1) == -1)
// // 			return (0);
// // 		close(data->pipes[i - 1][0]);
// // 		close(data->pipes[i][1]);
// // 		close_input_output(data);
// // 	}
// // 	return (1);
// // }
