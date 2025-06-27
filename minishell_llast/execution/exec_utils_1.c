/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:09:40 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/27 20:56:47 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	setup_pipe_redirections(t_exec *exec, int index, t_cmd *cmd)
{
	if (index > 0)
	{
		dup2(exec->pipes[index - 1][0], STDIN_FILENO);
		close(exec->pipes[index - 1][0]);
	}
	if (!cmd->outfile && index < exec->nb_cmds - 1)
	{
		dup2(exec->pipes[index][1], STDOUT_FILENO);
		close(exec->pipes[index][1]);
	}
}

void	free_all_shell(t_struct **data, t_exec *exec, t_cmd *cmd)
{
	free_all_cmd(cmd);
	free_tokens((*data));
	free(*data);
	if (exec->pipes != NULL)
		free(exec->pipes);
	if (exec->path)
		free(exec->path);
	free(exec);
}

void	run_command(t_struct **data, t_exec *exec, t_cmd *cmd)
{
	// if (cmd->argv[0] == "")
	// 	exit
	if (is_builtin(cmd->argv[0]))
	{
		exec_builtin(exec, *data, cmd);
		free_all_shell(data, exec, cmd);
		exit(0);
	}
	else
	{
		if (!command_loc(*data, exec, cmd->argv[0]))
		{
			exec->last_status = 126;
			if (errno == ENOENT)
			{
				exec->last_status = 127;
				free_all_shell(data, exec, cmd);
				exit(127);
			}
			else if (errno == EACCES)
			{
				exec->last_status = 126;
				free_all_shell(data, exec, cmd);
				exit(126);
			}
			exit(exec->last_status);
		}
		execve(exec->path, cmd->argv, (*data)->env);
		handle_cmd_error(cmd->argv[0]);
		if (errno == ENOENT)
		{
			exec->last_status = 127;
			free_all_shell(data, exec, cmd);
			exit(127);
		}
		else if (errno == EACCES)
		{
			exec->last_status = 126;
			free_all_shell(data, exec, cmd);
			exit(126);
		}
		exit(126);
	}
}

void	close_pipes_and_wait(t_exec *exec)
{
	int	i;
	int	status;

	i = 0;
	while (i < exec->nb_cmds - 1)
	{
		close(exec->pipes[i][0]);
		close(exec->pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < exec->nb_cmds)
	{
		waitpid(-1, &status, 0);
		if (i == exec->nb_cmds - 1)
		{
			if (WIFEXITED(status))
				exec->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exec->last_status = 0;
		}
		i++;
	}
}

int	fork_and_execute_commands(t_struct **data, t_exec *exec, t_cmd *cmd)
{
	int	index;

	index = 0;
	while (cmd)
	{
		// if (cmd->argv[0] == NULL)
		// {
		// 	cmd = cmd->next;
		// 	continue ;
		// }
		exec->pids = fork();
		if (exec->pids == -1)
		{
			perror("minishell: fork");
			return (-1);
		}
		if (exec->pids == 0)
		{
			signal(SIGINT, SIG_DFL);  // Comportement par défaut (Terminated)
			signal(SIGQUIT, SIG_DFL); // Comportement par défaut (Quit)
			close_unused_pipes(exec, index);
			if (index > 0 || !cmd->outfile)
				setup_pipe_redirections(exec, index, cmd);
			setup_redirections(cmd);
			run_command(data, exec, cmd);
		}
		index++;
		cmd = cmd->next;
	}
	return (1);
}
