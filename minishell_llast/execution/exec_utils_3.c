/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:10:18 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/25 20:26:05 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	split_path(t_exec *exec, char *path, char *cmd)
{
	char	**dossier;
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	dossier = ft_split(path, ':');
	if (!dossier)
		return (0);
	while (dossier[i])
	{
		tmp = ft_strjoin(dossier[i], "/");
		if (!tmp)
			return (ft_free_array(dossier), 0);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (ft_free_array(dossier), 0);
		if (access(full_path, X_OK) == 0)
		{
			exec->path = full_path;
			ft_free_array(dossier);
			return (1);
		}
		free(full_path);
		i++;
	}
	ft_free_array(dossier);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (0);
}

char	*search_path(char **env)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5;
			break ;
		}
		i++;
	}
	return (path);
}

int	is_path(char *cmd)
{
	return (ft_strchr(cmd, '/') != NULL);
}

int	command_loc(t_struct *data, t_exec *exec, char *cmd)
{
	char		*path;
	struct stat	sb;

	exec->path = NULL;
	if (is_path(cmd))
	{
		if (stat(cmd, &sb) == -1)
		{
			handle_cmd_error(cmd);
			return (0);
		}
		if (S_ISDIR(sb.st_mode))
		{
			errno = EISDIR;
			handle_cmd_error(cmd);
			return (0);
		}
		if (access(cmd, F_OK) == -1 || access(cmd, X_OK) == -1)
		{
			handle_cmd_error(cmd);
			exec->last_status = 126;
			return (0);
		}
		exec->path = ft_strdup(cmd);
		if (!exec->path)
			return (0);
		return (1);
	}
	path = search_path(data->env);
	if (!path)
	{
		errno = ENOENT;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (0);
	}
	if (!split_path(exec, path, cmd))
		return (0);
	return (1);
}

void	handle_cmd_error(char *cmd)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (errno == EISDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
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
	data->pipes = malloc((data->nb_cmds - 1) * sizeof(int[2]));
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
