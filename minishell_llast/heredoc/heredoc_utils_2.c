/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 19:04:40 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/05 19:09:29 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	check_buffer_complete(char *buffer, int i, char c)
{
	if (i >= 1023 || c == '\n')
	{
		buffer[i] = '\0';
		return (1);
	}
	return (0);
}

int	handle_read_result(int bytes_read, int i, int line_nb, char *delimiter)
{
	if (bytes_read == 0)
	{
		if (i == 0)
			return (check_heredoc_interrupts(line_nb, delimiter, NULL), -2);
		else
			return (999);
	}
	if (bytes_read == -1)
	{
		if (g_signal_status == 130)
			return (-1);
		return (perror("read"), close(0), close(1), -1);
	}
	return (0);
}

int	read_heredoc_line(char *delimiter, int line_nb, char *buffer)
{
	int		bytes_read;
	char	c;
	int		i;

	i = 0;
	while (1)
	{
		if (g_signal_status == 130)
			return (-1);
		bytes_read = read(0, &c, 1);
		if (handle_read_result(bytes_read, i, line_nb, delimiter) != 0)
			return (handle_read_result(bytes_read, i, line_nb, delimiter));
		buffer[i++] = c;
		if (check_buffer_complete(buffer, i, c) == 1)
			return (0);
	}
	return (1);
}
