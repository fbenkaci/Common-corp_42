/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:21:25 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/19 15:35:25 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	open_all_heredocs(t_exec *exec, t_struct **data, t_cmd *cmd)
{
	t_cmd	*tmp;
	// int		heredoc_status;
	(void)exec;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->heredoc)
		{
			// heredoc_status = heredoc_input(data, tmp->heredoc_delim);
			// if (heredoc_status == 130)
			// {
			// 	exec->last_status = 130;
			// 	return (130);
			// }
			tmp->heredoc_fd = heredoc_input(data, tmp->heredoc_delim);
			if (tmp->heredoc_fd < 0)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	execute_single_builtin(t_exec *exec, t_cmd *cmd, t_struct **data)
{
	int	saved_stdin;
	int builtin_status;

	saved_stdin = 0;
	if (cmd->heredoc)
	{
		saved_stdin = dup(STDIN_FILENO);
		dup2(cmd->heredoc_fd, STDIN_FILENO);
		close(saved_stdin);
		free(cmd->heredoc_delim);
	}
	builtin_status = exec_builtin(exec, *data, cmd->argv);
	if (builtin_status == 1)
	{
		if (cmd->heredoc)
		{
			close(cmd->heredoc_fd);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
			free(cmd->heredoc_delim);
		}
	}
	else
	{
		handle_cmd_error(cmd->argv[0]);
		// ft_putstr_fd("minishell: ", STDERR_FILENO);
		// ft_putstr_fd("Command not found\n", STDERR_FILENO);
		// exec->last_status = 127;
	}
	return (builtin_status);
}

void	handle_outfile(t_cmd *cmd)
{
	int	fd2;

	fd2 = 0;
	if (cmd->outfile)
	{
		if (cmd->append)
			fd2 = open(cmd->outfile, O_APPEND | O_CREAT | O_WRONLY, 0644);
		else
			fd2 = open(cmd->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
		if (fd2 < 0)
		{
			if (errno == EACCES) // Error Access
			{
				ft_putstr_fd("minishell: Permission denied\n", STDERR_FILENO);
				free_all_cmd(cmd);
				// free_token(data);
				// faut que rajoute t_struct a ton prototype
				exit(127);
			}
			ft_putstr_fd("minishell: Error opening file\n", STDERR_FILENO);
			exit(1);
		}
		dup2(fd2, STDOUT_FILENO);
		close(fd2);
	}
}

void	setup_redirections(t_cmd *cmd)
{
	int	fd;

	fd = 0;
	// d) Redirection “outfile” si existant
	if (cmd->heredoc)
	{
		dup2(cmd->heredoc_fd, STDIN_FILENO);
		free(cmd->heredoc_delim);
		close(cmd->heredoc_fd);
	}
	// c) Redirection “infile” si existant
	if (cmd->infile && !cmd->heredoc)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->infile, STDERR_FILENO);
			ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
		}
		close(fd);
	}
	if (cmd->outfile)
		handle_outfile(cmd);
}
