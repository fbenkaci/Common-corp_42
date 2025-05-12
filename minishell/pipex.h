/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:54:38 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/12 19:12:36 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct pipex
{
	int		outputfd;
	int		inputfd;
	int		fd[2];
	char	*path;
	char	**cmd;
	int		nb_cmds;
	int		*pipes;
	int		*pids;
	int		here_doc;
}			t_pipex;

void		execution2(t_pipex *data, char **envp);
int			process_command2(t_pipex *data, char **envp);
void		free_close_pipes(t_pipex *data);
char		**path_command(char **envp);
int			pipex_bonus(t_pipex *data, int ac, char **av, char **envp);
int			creat_pipe(t_pipex *data);
void		free_close_pipes(t_pipex *data);
int			launch_all_commands(t_pipex *data, char **envp, char **av);
int			handle_heredoc(t_pipex *data, int ac, char **av, char **envp);
int			check_outfile_exist2(char **av, int ac);
void		free_pipes(t_pipex *data, int *i);
void		close_input_output(t_pipex *data);
int			setup_redirections(t_pipex *data, int i);
void		close_unnecessary_pipes(t_pipex *data, int i);
int			handle_pipex(t_pipex *data, int ac, char **av, char **envp);
char		*command_loc(char **envp, char *av);

#endif