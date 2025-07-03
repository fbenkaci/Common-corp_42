/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:13:31 by marvin            #+#    #+#             */
/*   Updated: 2025/07/03 13:13:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

/* Gère les redirections de sortie */
static void handle_output_redirs(t_struct *data, t_cmd *cmd, t_exec *exec)
{
    if (!cmd->outfiles)
        return;
    if (handle_multiple_outfiles(data, cmd, exec) == -1)
        exit(1);
}

/* Gère le heredoc seul ou combiné */
static void handle_heredoc_redirs(t_cmd *cmd)
{
    int fd;

    if (cmd->infiles || cmd->infile)
    {
        fd = create_combined_input(cmd);
        if (fd >= 0)
        {
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
    }
    else
    {
        dup2(cmd->heredoc_fd, STDIN_FILENO);
        close(cmd->heredoc_fd);
    }
}

/* Gère les fichiers d'entrée simples ou multiples */
static void handle_file_redirs(t_struct *data, t_cmd *cmd, t_exec *exec)
{
    int fd;

    if (cmd->infiles)
    {
        if (handle_multiple_infiles(data, cmd, exec) == -1)
            exit(1);
    }
    else if (cmd->infile)
    {
        fd = open(cmd->infile, O_RDONLY);
        if (fd < 0)
        {
            handle_cmd_error(cmd->infile);
            exit(1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
}

/* Point d'entrée pour configurer toutes les redirections */
void setup_redirections(t_struct *data, t_cmd *cmd, t_exec *exec)
{
    handle_output_redirs(data, cmd, exec);

    if (cmd->heredoc)
        handle_heredoc_redirs(cmd);
    else
        handle_file_redirs(data, cmd, exec);
}
