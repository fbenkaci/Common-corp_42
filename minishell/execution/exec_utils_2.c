/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:10:18 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/04 16:06:02 by fbenkaci         ###   ########.fr       */
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
	ft_putstr_fd(cmd, 2);
	return (ft_putstr_fd(": Command not found\n", 2), 0);
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
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			return (0);
		}
		exec->path = ft_strdup(cmd);
		return (1);
	}
	path = search_path(data->env);
	if (!path)
	{
		ft_putstr_fd(cmd, 2);
		return (ft_putstr_fd(": command not found\n", 2), 0);
	}
	if (!split_path(exec, path, cmd))
		return (0);
	return (1);
}
