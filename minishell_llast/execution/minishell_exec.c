/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:27:28 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/27 20:48:19 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	execution(t_cmd *cmd, t_exec *exec, t_struct **data)
{
	int	builtin_ret;
	int	heredoc_status;

	heredoc_status = open_all_heredocs(exec, data, cmd);
	if (heredoc_status == 130)
		return (1);
	if (heredoc_status == -1)
		return (ft_putstr_fd("Error opening heredoc\n", 2), -1);
	if (caculate_nb_cmd(exec, cmd) == -1)
		return (ft_putstr_fd("Error calculating number of commands\n", 2), -1);
	if (exec->nb_cmds == 1 && is_builtin(cmd->argv[0]) && !cmd->outfile
		&& !cmd->infile)
	{
		builtin_ret = execute_single_builtin(exec, cmd, data);
		if (builtin_ret == 0)
			return (-1);
		return (1);
	}
	if (create_pipe(exec) == -1)
	{
		ft_putstr_fd("Error creating pipes\n", 2);
		return (-1);
	}
	if (fork_and_execute_commands(data, exec, cmd) == -1)
	{
		ft_putstr_fd("Error executing commands\n", 2);
		return (-1);
	}
	signal(SIGINT, handle_sigint_exec);
	close_pipes_and_wait(exec);
	if (exec->pipes)
	{
		free(exec->pipes);
		exec->pipes = NULL;
	}
	return (1);
}
