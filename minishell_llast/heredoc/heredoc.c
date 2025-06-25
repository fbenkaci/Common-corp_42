/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:27:16 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/23 13:27:09 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	check_heredoc_interrupts(int line_nb, char *delimiter, int *fd)
{
	ft_putstr_fd("\nminishell: warning: here-document at line ", 2);
	ft_putnbr_fd(line_nb, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted ", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
	close(fd[1]);
}

int	init_heredoc_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (1);
}

int	read_heredoc_line(char *delimiter, int line_nb, int *fd, char *buffer)
{
	int		bytes_read;
	char	c;
	int		i;

	i = 0;
	while (1)
	{
		bytes_read = read(0, &c, 1);
		if (bytes_read == 0)
		{
			if (i == 0)
				return (check_heredoc_interrupts(line_nb, delimiter, fd), -2);
			else
				continue ;
		}
		if (bytes_read == -1)
			return (perror("read"), close(fd[0]), close(fd[1]), -1);
		buffer[i++] = c;
		if (i >= 1023 || c == '\n')
		{
			buffer[i] = '\0';
			return (0);
		}
	}
	return (1);
}

int	process_heredoc_line(t_struct **data, char *delimiter, int *fd,
		int *line_nb)
{
	char	buffer[1024];
	char	*line;
	char	*expanded_line;
	int		ret;

	write(1, "> ", 2);
	ret = read_heredoc_line(delimiter, *line_nb, fd, buffer);
	if (ret == -1)
		return (-1);
	else if (ret == -2)
		return (-2);
	if (ret == 0)
	{
		line = buffer;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
			return (-2);
		expanded_line = expand_variables_heredoc(data, line);
		if (expanded_line)
		{
			write(fd[1], expanded_line, ft_strlen(expanded_line));
			free(expanded_line);
		}
		(*line_nb)++;
	}
	return (1);
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal_status = 130;
	write(1, "\n", 1);
}

int	heredoc_input(t_struct **data, char *delimiter)
{
	int	fd[2];
	int	line_nb;
	int	ret;

	line_nb = 1;
	if (init_heredoc_pipe(fd) == -1)
		return (-1);
	// Sauvegarder l'ancien handler et installer le nouveau
	signal(SIGINT, handle_sigint_heredoc);
	while (1)
	{
		// Vérifier si Ctrl+C a été reçu
		if (g_signal_status == 130)
		{
			close(fd[0]);
			close(fd[1]);
			// signal(SIGINT, old_sigint);  // Restaurer l'ancien handler
			return (-1);
		}
		ret = process_heredoc_line(data, delimiter, fd, &line_nb);
		if (ret == -1)
		{
			signal(SIGINT, handle_sigint); // Restaurer l'ancien handler
			return (-1);
		}
		else if (ret == -2)
			break ;
	}
	signal(SIGINT, handle_sigint); // Restaurer l'ancien handler
	close(fd[1]);
	return (fd[0]);
}

// int handle_heredoc_signal(char *delimiter)
// {
// 	free(delimiter);
// 	// ft_free_array()
// 	g_signal = 0;
// 	close(0);
// 	return (-1);
// }