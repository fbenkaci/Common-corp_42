/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:27:28 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/04 20:33:49 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	create_pipe(t_exec *data)
{
	int	i;

	i = 0;
	data->pipes = malloc((data->nb_cmds - 1) * sizeof(int[2]));
	if (!data->pipes)
		return (perror("malloc"), -1);
	while (i < data->nb_cmds - 1)
	{
		if (pipe(data->pipes[i]) == -1)
			return (perror("pipe"), -1);
		i++;
	}
	return (1);
}

int	execution(t_cmd *cmd, t_exec *exec, t_struct **data)
{
	t_cmd	*tmp;
	int		index;
	int		fd2;
	int		fd;
	int		i;
	int		saved_stdin;

	// int j;
	// int status;
	tmp = cmd;
	index = 0;
	i = 0;
	while (tmp)
	{
		if (tmp->heredoc)
		{
			tmp->heredoc_fd = heredoc_input(tmp->heredoc_delim);
			if (tmp->heredoc_fd < 0)
				return (-1);
		}
		tmp = tmp->next;
	}
	caculate_nb_cmd(exec, cmd);
	if (exec->nb_cmds == 1 && is_builtin(cmd->argv[0]) && !cmd->outfile && !cmd->infile)
	{
		saved_stdin = 0;
		if (cmd->heredoc)
		{
			saved_stdin = dup(STDIN_FILENO);
			dup2(cmd->heredoc_fd, STDIN_FILENO);
			free(cmd->heredoc_delim);
		}
		exec_builtin(*data, cmd->argv);
		if (cmd->heredoc)
		{
			close(cmd->heredoc_fd);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
			free(cmd->heredoc_delim);
		}
		return (1);
	}
	if (create_pipe(exec) == -1)
	{
		// free tout
		return (-1);
	}
	while (cmd)
	{
		exec->pids = fork();
		if (exec->pids == -1)
			return (-1); // free tout
		if (exec->pids == 0)
		{
			// a) Fermer les pipes inutiles
			close_unused_pipes(exec, index);
			// b) Redirection du heredoc (le fils hérite du fd lu par le parent)
			if (cmd->heredoc)
			{
				dup2(cmd->heredoc_fd, STDIN_FILENO);
				free(cmd->heredoc_delim);
				close(cmd->heredoc_fd);
			}
			// c) Redirection “infile” si existant
			if (!cmd->heredoc && cmd->infile)
			{
				fd = open(cmd->infile, O_RDONLY);
				if (fd < 0)
					exit(1);
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			// d) Redirection “outfile” si existant
			if (cmd->outfile)
			{
				if (cmd->append)
				{
					fd2 = open(cmd->outfile, O_APPEND | O_CREAT | O_WRONLY, 0644);
				}
				else
				{
					fd2 = open(cmd->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
				}
				if (fd2 < 0)
					exit(1);
				dup2(fd2, STDOUT_FILENO);
				close(fd2);
			}
			
			// e) Brancher les extrémités de pipe selon index
			if (index > 0)
			{
				dup2(exec->pipes[index - 1][0], STDIN_FILENO);
				close(exec->pipes[index - 1][0]);
			}
			if (index < exec->nb_cmds - 1)
			{
				dup2(exec->pipes[index][1], STDOUT_FILENO);
				close(exec->pipes[index][1]);
			}
			// f) Exécuter le builtin ou l’externe
			if (is_builtin(cmd->argv[0]))
			{
				exec_builtin(*data, cmd->argv);
				exit(0);
			}
			else
			{
				if (!command_loc(*data, exec, cmd->argv[0]))
					exit(0);
				execve(exec->path, cmd->argv, (*data)->env);
				ft_putstr_fd(exec->path, 2);
				ft_putstr_fd(": command not found\n", 2);
				exit(127);
			}
		}
		index++;
		cmd = cmd->next;
	}
	for (i = 0; i < exec->nb_cmds - 1; i++)
	{
		close(exec->pipes[i][0]);
		close(exec->pipes[i][1]);
	}
	for (i = 0; i < exec->nb_cmds; i++)
	{
		waitpid(exec->pids, NULL, 0);
	}
	return (1);
}

// e) Brancher les extrémités de pipe selon index
// if (index == 0)
// {
// 	dup2(exec->pipes[index][1], STDOUT_FILENO);
// 	close(exec->pipes[index][1]);
// }
// if (index == 0)
// {
// 	dup2(exec->pipes[index][1], STDOUT_FILENO);
// 	close(exec->pipes[index][1]);
// }
// if (index == exec->nb_cmds - 1)
// {
// 	dup2(exec->pipes[index - 1][0], STDIN_FILENO);
// 	close(exec->pipes[index - 1][0]);
// }
// else
// {
// 	dup2(exec->pipes[index - 1][0], STDIN_FILENO);
// 	dup2(exec->pipes[index][1], STDOUT_FILENO);
// 	close(exec->pipes[index - 1][0]);
// 	close(exec->pipes[index][1]);
// }