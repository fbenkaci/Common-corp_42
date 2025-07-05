/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:33:46 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/18 16:34:26 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	copy_env_excluding(t_struct *data, char **new_env, char *var_name)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(var_name);
	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (!(ft_strncmp(data->env[i], var_name, len) == 0
				&& data->env[i][len] == '='))
			new_env[j++] = data->env[i];
		else
			free(data->env[i]);
		i++;
	}
	new_env[j] = NULL;
	free(data->env);
	data->env = new_env;
}

int	ft_unset(t_exec *exec, t_struct *data, char **cmd)
{
	char	*var_name;
	char	**new_env;
	int		len;
	int		i;

	i = 1;
	if (!cmd || !*cmd)
		return (0);
	while (cmd[i])
	{
		len = 0;
		var_name = cmd[i];
		while (data->env[len])
			len++;
		new_env = malloc(sizeof(char *) * (len + 1));
		if (!new_env)
			return (0);
		copy_env_excluding(data, new_env, var_name);
		i++;
	}
	exec->last_status = 0;
	return (1);
}

int	cpy_env(t_struct *data, char **envp)
{
	char *cwd;
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (!envp || !*envp)
	{
		cwd = getcwd(NULL, 0);
		len = 3;
		data->env = malloc(sizeof(char *) * (len + 1));
		if (!data->env)
			return (-1);
		data->env[i] = ft_strjoin("PWD=", cwd);
		if (!data->env[i])
			return (ft_free_array(data->env), -1);
		i++;
		data->env[i] = ft_strdup("SHLVL=1");
		if (!data->env[i])
			return (ft_free_array(data->env), -1);
		i++;
		data->env[i] = ft_strdup("_=/usr/bin/env");
		if (!data->env[i])
			return (ft_free_array(data->env), -1);
		data->env[len] = NULL;
		free(cwd);
		return (1);
	}
	while (envp[len])
		len++;
	data->env = malloc(sizeof(char *) * (len + 1));
	if (!data->env)
		return (-1);
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
			return (ft_free_array(data->env), -1);
		i++;
	}
	data->env[len] = NULL;
	return (1);
}

