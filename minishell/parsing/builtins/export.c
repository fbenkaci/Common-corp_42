/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:23:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/21 17:38:33 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		{
			ft_free_array(cpy_env);
			return (0);
		}
		i++;
	}
	cpy_env[len_env] = NULL;
	sorted_export(cpy_env, len_env);
	print_export(cpy_env);
	ft_free_array(cpy_env);
	return (1);
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

int	add_in_env(t_struct *data, char *cmd)
{
	char	**cpy_env;
	int		len;
	int		i;

	len = 0;
	while (data->env[len])
		len++;
	cpy_env = malloc(sizeof(char *) * (len + 2));
	if (!cpy_env)
		return (0);
	i = 0;
	while (data->env[i])
	{
		cpy_env[i] = ft_strdup(data->env[i]);
		if (!cpy_env[i])
			return (ft_free_array(cpy_env), 0);
		i++;
	}
	cpy_env[i] = ft_strdup(cmd);
	cpy_env[i + 1] = NULL;
	ft_free_array(data->env);
	data->env = cpy_env;
	return (1);
}

int	add_or_replace_env_var(t_struct *data, char *cmd)
{
	char	*var_name;
	int		len;
	int		i;
	int		flag;

	flag = 0;
	len = 0;
	i = 0;
	while (cmd[len] != '=')
		len++;
	var_name = ft_substr(cmd, 0, len);
	if (!var_name)
		return (0);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var_name, len) == 0)
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(cmd);
			flag = 1;
			break ;
		}
		i++;
	}
	free(var_name);
	if (!flag)
		return (add_in_env(data, cmd));
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

int	main(int ac, char **av, char **envp)
{
	t_struct	*data;
	char		**cmd;
	int			i;
	int			nb;

	// int			len;
	// int			i;
	(void)ac;
	(void)av;
	data = malloc(sizeof(t_struct));
	if (!data)
		return (0);
	cmd = malloc(50);
	cmd[0] = "export";
	cmd[1] = "VAR5=2";
	cmd[2] = "VAR5=3";
	cmd[3] = NULL;
	// cmd[2] = "=";
	// cmd[3] = "3=";
	// cmd[3] = "c=";
	if (cpy_env(data, envp) == 0)
		return (0);
	i = 0;
	// while (data->env[i])
	// {
	// 	ft_printf("%s\n", data->env[i]);
	// 	i++;
	// }
	nb = ft_export(data, cmd);
	i = 0;
	while (data->env[i])
	{
		ft_printf("%s\n", data->env[i]);
		i++;
	}
	free(cmd);
	ft_free_array(data->env);
	free(data);
	return (0);
}
