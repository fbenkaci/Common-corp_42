/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:09:40 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/01 16:44:43 by wlarbi-a         ###   ########.fr       */
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
	if (cmd)
		free_all_cmd(cmd);
	if (*data)
	{
		// Dans les processus enfants,libérer tout car ils ont leur propre copie après fork()
		if ((*data)->env)
			ft_free_array((*data)->env);
		if ((*data)->str)
			free((*data)->str);
		// Libérer complètement le token pool car le processus enfant a sa propre copie
		if ((*data)->token_pool)
			free_token_pool((*data)->token_pool);
		free(*data);
	}
	if (exec)
	{
		if (exec->pipes != NULL)
			free(exec->pipes);
		if (exec->path)
			free(exec->path);
		free(exec);
	}
}

// Fonction pour libérer tout depuis le processus parent (inclut le token pool)
void	free_all_shell_parent(t_struct **data, t_exec *exec, t_cmd *cmd)
{
	if (cmd)
		free_all_cmd(cmd);
	if (*data)
	{
		// Libérer le token pool seulement depuis le processus parent
		if ((*data)->token_pool)
			free_token_pool((*data)->token_pool);
		free_tokens((*data));
	}
	if (exec->pipes != NULL)
		free(exec->pipes);
	if (exec->path)
		free(exec->path);
	free(exec);
}

void	run_command(t_struct **data, t_exec *exec, t_cmd *cmd)
{
	int		exit_status;
	t_cmd	*cmd_list;

	cmd_list = exec->cmds;
	if (!cmd->argv[0] || cmd->argv[0][0] == '\0')
	{
		exec->last_status = 0;
		free_all_cmd(cmd_list);
		free_all_shell(data, exec, NULL);
		exit(0);
	}
	if (is_builtin(cmd->argv[0]))
	{
		exec_builtin(exec, *data, cmd);
		free_all_cmd(cmd_list);
		free_all_shell(data, exec, NULL);
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
				free_all_cmd(cmd_list);
				free_all_shell(data, exec, NULL);
				exit(127);
			}
			else if (errno == EACCES)
			{
				exec->last_status = 126;
				free_all_cmd(cmd_list);
				free_all_shell(data, exec, NULL);
				exit(126);
			}
			// Clean up memory before exit
			{
				exit_status = exec->last_status;
				free_all_cmd(cmd_list);
				free_all_shell(data, exec, NULL);
				exit(exit_status);
			}
		}
		execve(exec->path, cmd->argv, (*data)->env);
		handle_cmd_error(cmd->argv[0]);
		if (errno == ENOENT)
		{
			exec->last_status = 127;
			free_all_cmd(cmd_list);
			free_all_shell(data, exec, NULL);
			exit(127);
		}
		else if (errno == EACCES)
		{
			exec->last_status = 126;
			free_all_cmd(cmd_list);
			free_all_shell(data, exec, NULL);
			exit(126);
		}
		// exec->last_status = 1;
		exit(126);
	}
}

void	close_pipes_and_wait(t_exec *exec)
{
	int	i;
	int	status;
	int	sig;

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
			{
				sig = WTERMSIG(status);
				if (sig == SIGQUIT)
				{
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
					exec->last_status = 128 + sig;
				}
			}
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
		exec->pids = fork();
		if (exec->pids == -1)
			return (perror("minishell: fork"), -1);
		if (exec->pids == 0)
		{
			signal(SIGINT, SIG_DFL);  // Comportement par défaut (Terminated)
			signal(SIGQUIT, SIG_DFL); // Comportement par défaut (Quit)
			close_unused_pipes(exec, index);
			if (index > 0 || !cmd->outfile)
				setup_pipe_redirections(exec, index, cmd);
			if (cmd->outfile && index < exec->nb_cmds - 1)
				close(exec->pipes[index][1]);
			setup_redirections(*data, cmd, exec);
			run_command(data, exec, cmd);
		}
		index++;
		cmd = cmd->next;
	}
	return (1);
}

void	complete_cleanup_and_exit(t_struct **data, t_exec *exec, t_cmd *cmd,
		int exit_code)
{
	t_struct	*token_ptr;
	t_struct	*next_token;

	// Free command structure
	if (cmd)
		free_all_cmd(cmd);
	// Complete token cleanup - ensure ALL token memory is freed
	if (data && *data && (*data)->next)
	{
		token_ptr = (*data)->next;
		while (token_ptr)
		{
			next_token = token_ptr->next;
			if (token_ptr->str)
			{
				free(token_ptr->str);
				token_ptr->str = NULL;
			}
			free(token_ptr);
			token_ptr = next_token;
		}
		(*data)->next = NULL;
	}
	// Free main data structure
	if (data && *data)
	{
		if ((*data)->env)
			ft_free_array((*data)->env);
		if ((*data)->str)
		{
			free((*data)->str);
			(*data)->str = NULL;
		}
		free(*data);
		*data = NULL;
	}
	// Free exec structure
	if (exec)
	{
		if (exec->pipes)
			free(exec->pipes);
		if (exec->path)
			free(exec->path);
		free(exec);
	}
	exit(exit_code);
}
