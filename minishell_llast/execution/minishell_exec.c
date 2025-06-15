/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:27:28 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/15 14:52:37 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	execution(t_cmd *cmd, t_exec *exec, t_struct **data)
{
	if (open_all_heredocs(data, cmd) == -1)
		return (ft_putstr_fd("Error opening heredoc\n", 2), -1);
	if (caculate_nb_cmd(exec, cmd) == -1)
		return (ft_putstr_fd("Error calculating number of commands\n", 2), -1);
	if (exec->nb_cmds == 1 && is_builtin(cmd->argv[0]) && !cmd->outfile
		&& !cmd->infile)
	{
		if (execute_single_builtin(cmd, data) == -1)
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
	close_pipes_and_wait(exec);
	return (1);
}
