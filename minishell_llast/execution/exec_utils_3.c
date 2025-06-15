/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:10:18 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/15 15:54:56 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	split_path(t_exec *exec, char *path, char *cmd)
{
	char	**dossier;
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
		free(dossier[i]);
		dossier[i] = tmp;
		exec->path = ft_strjoin(dossier[i], cmd);
		if (!exec->path)
			return (ft_free_array(dossier), 0);
		if (access(exec->path, X_OK) == 0)
			return (ft_free_array(dossier), 1);
		free(exec->path);
		i++;
	}
	ft_free_array(dossier);
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

int	command_loc(t_struct *data, t_exec *exec, char *cmd)
{
	char	*path;

	exec->path = NULL;
	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == -1)
		{
			return (0);
		}
		exec->path = ft_strdup(cmd);
		return (1);
	}
	path = search_path(data->env);
	if (!path)
	{
		return (0);
	}
	if (!split_path(exec, path, cmd))
		return (0);
	return (1);
}

void	handle_cmd_error(char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	}
	else if (ft_strchr(cmd, '/'))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
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
