/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:23:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/22 16:17:43 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_export(char **cpy_env)
{
	int	i;

	i = 0;
	while (cpy_env[i])
	{
		if (ft_strncmp(cpy_env[i], "_=", 2) != 0)
			ft_printf("declare -x %s\n", cpy_env[i]);
		i++;
	}
}

void	sorted_export(char **cpy_env, int len_env)
{
	int		sorted;
	char	*tmp;
	int		i;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (i < len_env - 1)
		{
			if (ft_strcmp(cpy_env[i], cpy_env[i + 1]) > 0)
			{
				tmp = cpy_env[i];
				cpy_env[i] = cpy_env[i + 1];
				cpy_env[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

int	is_valid_export(char *cmd)
{
	int	i;

	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd("`", 2);
		ft_putstr_fd(&cmd[0], 2);
		ft_putstr_fd("': ", 2);
		return (ft_putstr_fd("not a valid identifier\n", 2), 0);
	}
	i = 1;
	while (!cmd && cmd[i] != '=')
	{
		ft_printf("%c\n", cmd[i]);
		if (!ft_isalnum(cmd[i]))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd("`", 2);
			ft_putstr_fd(&cmd[i], 2);
			ft_putstr_fd("': ", 2);
			return (ft_putstr_fd("not a valid identifier\n", 2), 0);
		}
		i++;
	}
	return (1);
}

int	export_without_args(t_struct *data)
{
	char	**cpy_env;
	int		len_env;
	int		i;

	i = 0;
	len_env = 0;
	while (data->env[len_env])
		len_env++;
	cpy_env = malloc(sizeof(char *) * (len_env + 1));
	if (!cpy_env)
		return (0);
	while (data->env[i])
	{
		cpy_env[i] = ft_strdup(data->env[i]);
		if (!cpy_env[i])
			return (ft_free_array(cpy_env), 0);
		i++;
	}
	cpy_env[len_env] = NULL;
	sorted_export(cpy_env, len_env);
	print_export(cpy_env);
	ft_free_array(cpy_env);
	return (1);
}

int	ft_export(t_struct *data, char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[1])
	{
		if (export_without_args(data))
			return (1);
		return (0);
	}
	else
	{
		while (cmd[i])
		{
			if (is_valid_export(cmd[i]))
			{
				if (!add_or_replace_env_var(data, cmd[i]))
					return (0);
			}
			i++;
		}
	}
	return (1);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_struct	*data;
// 	char		**cmd;
// 	int			i;
// 	int			nb;

// 	// int			len;
// 	// int			i;
// 	(void)ac;
// 	(void)av;
// 	data = malloc(sizeof(t_struct));
// 	if (!data)
// 		return (0);
// 	cmd = malloc(50);
// 	cmd[0] = "export";
// 	// cmd[1] = "VAR5=2";
// 	// cmd[2] = "VAR5";
// 	// cmd[3] = "VAR5=3";
// 	// cmd[4] = "VAR2=3";
// 	cmd[1] = NULL;
// 	// cmd[2] = "=";
// 	// cmd[3] = "3=";
// 	// cmd[3] = "c=";
// 	if (cpy_env(data, envp) == 0)
// 		return (0);
// 	i = 0;
// 	// while (data->env[i])
// 	// {
// 	// 	ft_printf("%s\n", data->env[i]);
// 	// 	i++;
// 	// }
// 	nb = ft_export(data, cmd);
// 	// i = 0;
// 	// while (data->env[i])
// 	// {
// 	// 	ft_printf("%s\n", data->env[i]);
// 	// 	i++;
// 	// }
// 	free(cmd);
// 	ft_free_array(data->env);
// 	free(data);
// 	return (0);
// }
