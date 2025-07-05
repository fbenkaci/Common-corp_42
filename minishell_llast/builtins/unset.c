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
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (!envp)
	{
		len = 3;
		data->env = malloc(sizeof(char *) * (len + 1));
		if (!data->env)
			return (-1);
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
		{
			ft_free_array(data->env);
			return (-1);
		}
		i++;
	}
	data->env[len] = NULL;
	return (1);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_struct	*data;
// 	char		**cmd;
// 	int			i;

// 	data = malloc(sizeof(t_struct));
// 	cmd = malloc(100);
// 	cmd[0] = "unset";
// 	cmd[1] = "VAR1";
// 	cmd[2] = "VAR2";
// 	cmd[3] = "VAR3";
// 	cmd[4] = "VAR4";
// 	cmd[5] = NULL;
// 	(void)av;
// 	(void)ac;
// 	if (!cpy_env(data, envp))
// 		return (0);
// 	i = 0;

// 	ft_printf("------------ avant unset ------------\n");
// 	while (data->env[i])
// 	{
// 		ft_printf("%s\n", data->env[i]);
// 		i++;
// 	}
// 	ft_printf("------------ avant unset ------------\n\n\n");
// 	ft_unset(data, cmd);
// 	i = 0;
// 	while (data->env[i])
// 	{
// 		ft_printf("%s\n", data->env[i]);
// 		i++;
// 	}
// 	ft_free_array(data->env);
// 	free(data);
// 	free(cmd);
// 	return (0);
// }
