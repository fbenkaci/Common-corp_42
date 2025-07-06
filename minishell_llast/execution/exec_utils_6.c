/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:23:01 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/06 17:24:17 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	print_cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	handle_cmd_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	if (errno == ENOENT)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (errno == EISDIR)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
}

int	create_pipe(t_exec *data)
{
	int	i;

	i = 0;
	data->pipes = malloc((data->nb_cmds - 1) * sizeof(int [2]));
	if (!data->pipes)
		return (perror("malloc"), -1);
	while (i < data->nb_cmds - 1)
	{
		if (pipe(data->pipes[i]) == -1)
			return (perror("pipe"), -1);
		i++;
	}
	return (1);
}

int	is_path(char *cmd)
{
	return (ft_strchr(cmd, '/') != NULL);
}
