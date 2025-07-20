/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:15:26 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/11 21:06:53 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "pipex.h"

// int	handle_heredoc(t_pipex *data, int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	char	*result;
// 	int		fd;

// 	fd = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC | 0644);
// 	if (fd == -1)
// 		return (0);
// 	if (creat_pipe(data) == 0)
// 		return (0);
// 	while (1)
// 	{
// 		result = get_next_line(0);
// 		if (!result)
// 			break ;
// 		if (ft_strncmp(result, av[2], ft_strlen(av[2])) == 0 && result[ft_strlen(av[2])] == '\n')
// 		{
// 			free(result);
// 			break ;
// 		}
// 		if (result)
// 			write(fd, result, ft_strlen(result));
// 	}
// 	close(fd);
// 	data->inputfd = open("heredoc_tmp", O_RDONLY);
// 	if (data->inputfd == -1)
// 		return (0);
// 	// launch_all_commands(data, envp, av + 3);
// 	return (1);
// }

// int	check_outfile_herdoc(char **av, int ac)
// {
// 	int	fd;

// 	fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (fd == -1)
// 	{
// 		perror("Error opening outfile");
// 		return (-1);
// 	}
// 	return (fd);
// }

// int	handle_heredoc_prepa(t_pipex *data, int ac, char **av, char **envp)
// {
// 	data->nb_cmds = ac - 4;
// 	data->pids = malloc(sizeof(int) * data->nb_cmds);
// 	if (!data->pids)
// 		return (0);
// 	if (handle_heredoc(data, ac, av, envp) == 0)
// 		return (0);
// 	data->outputfd = check_outfile_herdoc(av, ac);
// 	if (data->outputfd == -1)
// 		return (0);
// 	if (launch_all_commands(data, envp, av) == 0)
// 		return (0);
// 	free_close_pipes(data);
// 	return (1);
// }
