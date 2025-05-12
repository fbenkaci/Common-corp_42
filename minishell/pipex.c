/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:17:22 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/12 18:56:48 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc_input(char *limiter)
{
	char	*line;
	int		fds[2];

	if (pipe(fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fds[1], line, ft_strlen(line));
		free(line);
	}
	close(fds[1]);
	return (fds[0]);
}

int	setup_fds(t_pipex *data, char **av, int ac)
{
	int	i;

	if (data->here_doc)
		data->inputfd = here_doc_input(av[2]);
	else
		data->inputfd = open(av[1], O_RDONLY);
	if (data->inputfd < 0)
	{
		perror("open input");
		i = 0;
		while (i < data->nb_cmds - 1)
		{
			if (data->pipes[i * 2] > 0)
				close(data->pipes[i * 2]);
			if (data->pipes[i * 2 + 1] > 0)
				close(data->pipes[i * 2 + 1]);
			i++;
		}
		if (data->inputfd > 0)
			close(data->inputfd);
		free(data->pids);
		free(data->pipes);
		return (0);
	}
	if (data->here_doc)
		data->outputfd = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		data->outputfd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->outputfd < 0)
	{
		perror("open output");
		i = 0;
		while (i < data->nb_cmds - 1)
		{
			if (data->pipes[i * 2] > 0)
				close(data->pipes[i * 2]);
			if (data->pipes[i * 2 + 1] > 0)
				close(data->pipes[i * 2 + 1]);
			i++;
		}
		if (data->inputfd > 0)
			close(data->inputfd);
		if (data->outputfd > 0)
			close(data->outputfd);
		free(data->pids);
		free(data->pipes);
		return (0);
	}
	return (1);
}

int	setup_redirections(t_pipex *data, int i)
{
	if (i == 0)
	{
		if (dup2(data->inputfd, 0) == -1)
			return (0);
		if (dup2(data->pipes[1], 1) == -1)
			return (0);
	}
	else if (i == data->nb_cmds - 1)
	{
		if (dup2(data->pipes[(i - 1) * 2], 0) == -1)
			return (0);
		if (dup2(data->outputfd, 1) == -1)
			return (0);
	}
	else
	{
		if (dup2(data->pipes[(i - 1) * 2], 0) == -1)
			return (0);
		if (dup2(data->pipes[i * 2 + 1], 1) == -1)
			return (0);
	}
	return (1);
}

int	launch_all_commands(t_pipex *data, char **envp, char **av)
{
	int		i;
	int		j;
	pid_t	pid;

	i = 0;
	if (data->here_doc)
		j = 3;
	else
		j = 2;
	while (i < data->nb_cmds)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Fork failed");
			return (0);
		}
		if (pid == 0)
		{
			close_unnecessary_pipes(data, i);
			data->cmd = ft_split(av[j], ' ');
			if (!data->cmd)
				exit(1);
			if (!process_command2(data, envp))
				exit(127);
			if (!setup_redirections(data, i))
				exit(1);
			free(data->pids);
			execution2(data, envp);
		}
		data->pids[i] = pid;
		i++;
		j++;
	}
	return (1);
}

int	handle_pipex(t_pipex *data, int ac, char **av, char **envp)
{
	if (ft_strcmp(av[1], "here_doc") == 0)
		data->here_doc = 1;
	else
		data->here_doc = 0;
	if (data->here_doc == 1)
		data->nb_cmds = ac - 4;
	else
		data->nb_cmds = ac - 3;
	data->pids = malloc(sizeof(int) * data->nb_cmds);
	if (!data->pids)
		return (0);
	data->pipes = malloc(sizeof(int) * 2 * (data->nb_cmds - 1));
	if (!data->pipes)
	{
		free(data->pids);
		return (0);
	}
	if (creat_pipe(data) == 0)
		return (0);
	if (!setup_fds(data, av, ac))
		return (0);
	if (!launch_all_commands(data, envp, av))
		return (0);
	free_close_pipes(data);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	data;

	if (ac < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 ... file2\n", 2);
		return (1);
	}
	if (!handle_pipex(&data, ac, av, envp))
		return (1);
	return (0);
}
