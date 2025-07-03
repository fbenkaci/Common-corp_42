/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:21:25 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/02 17:50:23 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	open_all_heredocs(t_exec *exec, t_struct **data, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->heredoc)
		{
			tmp->heredoc_fd = heredoc_input(data, tmp->heredoc_delim);
			if (tmp->heredoc_fd < 0)
			{
				if (g_signal_status == 130)
				{
					exec->last_status = 130;
					return (130);
				}
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

// int	execute_single_builtin(t_exec *exec, t_cmd *cmd, t_struct **data)
// {
// 	int	saved_stdin;
// 	int	builtin_status;
// 	int	combined_fd;

// 	saved_stdin = 0;
// 	if (cmd->heredoc && (cmd->infiles || cmd->infile))
// 	{
// 		saved_stdin = dup(STDIN_FILENO);
// 		combined_fd = create_combined_input(cmd);
// 		if (combined_fd >= 0)
// 		{
// 			dup2(combined_fd, STDIN_FILENO);
// 			close(combined_fd);
// 		}
// 	}
// 	else if (cmd->heredoc)
// 	{
// 		saved_stdin = dup(STDIN_FILENO);
// 		dup2(cmd->heredoc_fd, STDIN_FILENO);
// 		close(cmd->heredoc_fd);
// 	}
// 	builtin_status = exec_builtin(exec, *data, cmd);
// 	if (builtin_status == 1)
// 	{
// 		if (cmd->heredoc)
// 		{
// 			if (saved_stdin > 0)
// 			{
// 				dup2(saved_stdin, STDIN_FILENO);
// 				close(saved_stdin);
// 			}
// 			if (cmd->heredoc_delim)
// 				free(cmd->heredoc_delim);
// 		}
// 	}
// 	return (builtin_status);
// }


/* Helper to handle input redirection and heredoc setup */
int setup_input(t_cmd *cmd, int *saved_stdin)
{
    int combined_fd;

    *saved_stdin = 0;
    if (cmd->heredoc && (cmd->infiles || cmd->infile))
    {
        *saved_stdin = dup(STDIN_FILENO);
        combined_fd = create_combined_input(cmd);
        if (combined_fd >= 0)
        {
            dup2(combined_fd, STDIN_FILENO);
            close(combined_fd);
        }
    }
    else if (cmd->heredoc)
    {
        *saved_stdin = dup(STDIN_FILENO);
        dup2(cmd->heredoc_fd, STDIN_FILENO);
        close(cmd->heredoc_fd);
    }
    return (0);
}

/* Helper to restore stdin and cleanup heredoc */
int restore_input(t_cmd *cmd, int saved_stdin)
{
    if (saved_stdin > 0)
    {
        dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdin);
    }
    if (cmd->heredoc_delim)
    {
        free(cmd->heredoc_delim);
    }
    return (0);
}

/* Main execution of a single builtin */
int execute_single_builtin(t_exec *exec, t_cmd *cmd, t_struct **data)
{
    int saved_stdin;
    int builtin_status;

    setup_input(cmd, &saved_stdin);
    builtin_status = exec_builtin(exec, *data, cmd);
    if (builtin_status == 1 && cmd->heredoc)
    {
        restore_input(cmd, saved_stdin);
    }
    return (builtin_status);
}

// int	create_combined_input(t_cmd *cmd)
// {
// 	int		pipe_fd[2];
// 	char	buffer[4096];
// 	ssize_t	bytes_read;
// 	t_redir	*current;
// 	int		input_fd;

// 	if (pipe(pipe_fd) == -1)
// 		return (-1);
	
// 	// D'abord, copier le contenu du heredoc
// 	if (cmd->heredoc)
// 	{
// 		while ((bytes_read = read(cmd->heredoc_fd, buffer, sizeof(buffer))) > 0)
// 			write(pipe_fd[1], buffer, bytes_read);
// 		close(cmd->heredoc_fd);
// 	}
	
// 	// Ensuite, copier le contenu des fichiers d'entrée
// 	if (cmd->infiles)
// 	{
// 		current = cmd->infiles;
// 		while (current)
// 		{
// 			input_fd = open(current->filename, O_RDONLY);
// 			if (input_fd >= 0)
// 			{
// 				while ((bytes_read = read(input_fd, buffer, sizeof(buffer))) > 0)
// 					write(pipe_fd[1], buffer, bytes_read);
// 				close(input_fd);
// 			}
// 			current = current->next;
// 		}
// 	}
// 	else if (cmd->infile)
// 	{
// 		input_fd = open(cmd->infile, O_RDONLY);
// 		if (input_fd >= 0)
// 		{
// 			while ((bytes_read = read(input_fd, buffer, sizeof(buffer))) > 0)
// 				write(pipe_fd[1], buffer, bytes_read);
// 			close(input_fd);
// 		}
// 	}
	
// 	close(pipe_fd[1]);
// 	return (pipe_fd[0]);
// }


// void	setup_redirections(t_struct *data, t_cmd *cmd, t_exec *exec)
// {
// 	int	fd;

// 	fd = 0;
// 	if (cmd->outfiles)
// 	{
// 		if (handle_multiple_outfiles(data, cmd, exec) == -1)
// 			exit(1);  // Seulement exit dans le processus enfant
// 	}
	
// 	// Gérer les redirections d'entrée
// 	if (cmd->heredoc && (cmd->infiles || cmd->infile))
// 	{
// 		// Cas avec heredoc ET redirection d'entrée : combiner les contenus
// 		fd = create_combined_input(cmd);
// 		if (fd >= 0)
// 		{
// 			dup2(fd, STDIN_FILENO);
// 			close(fd);
// 		}
// 	}
// 	else if (cmd->heredoc)
// 	{
// 		// Cas avec seulement heredoc
// 		dup2(cmd->heredoc_fd, STDIN_FILENO);
// 		close(cmd->heredoc_fd);
// 	}
// 	else if (cmd->infiles)
// 	{
// 		// Cas avec seulement des fichiers d'entrée multiples
// 		if (handle_multiple_infiles(data, cmd, exec) == -1)
// 			exit(1);  // Seulement exit dans le processus enfant
// 	}
// 	else if (cmd->infile)
// 	{
// 		// Cas avec un seul fichier d'entrée
// 		fd = open(cmd->infile, O_RDONLY);
// 		if (fd < 0)
// 		{
// 			handle_cmd_error(cmd->infile);
// 			exit(1);
// 		}
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 	}
// }


