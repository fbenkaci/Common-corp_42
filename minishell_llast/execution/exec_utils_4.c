/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:59:27 by marvin            #+#    #+#             */
/*   Updated: 2025/07/03 12:59:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

/* Ouvre un pipe, retourne 0 ou -1 */
int open_pipe(int pipe_fd[2])
{
    if (pipe(pipe_fd) == -1)
        return (-1);
    return (0);
}

/* Lit depuis in_fd et écrit dans out_fd */
void write_fd_to_pipe(int in_fd, int out_fd)
{
    char buffer[4096];
    ssize_t bytes_read;

    while ((bytes_read = read(in_fd, buffer, sizeof(buffer))) > 0)
        write(out_fd, buffer, bytes_read);
}

/* Copie le contenu du heredoc vers le pipe */
void handle_heredoc(t_cmd *cmd, int out_fd)
{
    if (!cmd->heredoc)
        return;
    write_fd_to_pipe(cmd->heredoc_fd, out_fd);
    close(cmd->heredoc_fd);
}

/* Copie le contenu des fichiers d'entrée vers le pipe */
void handle_infiles(t_cmd *cmd, int out_fd)
{
    t_redir *current;
    int input_fd;

    if (cmd->infile)
    {
        input_fd = open(cmd->infile, O_RDONLY);
        if (input_fd >= 0)
        {
            write_fd_to_pipe(input_fd, out_fd);
            close(input_fd);
        }
    }
    current = cmd->infiles;
    while (current)
    {
        input_fd = open(current->filename, O_RDONLY);
        if (input_fd >= 0)
            write_fd_to_pipe(input_fd, out_fd), close(input_fd);
        current = current->next;
    }
}

/* Crée un flux combiné d'entrée */
int create_combined_input(t_cmd *cmd)
{
    int pipe_fd[2];

    if (open_pipe(pipe_fd) == -1)
        return (-1);
    handle_heredoc(cmd, pipe_fd[1]);
    handle_infiles(cmd, pipe_fd[1]);
    close(pipe_fd[1]);
    return (pipe_fd[0]);
}
