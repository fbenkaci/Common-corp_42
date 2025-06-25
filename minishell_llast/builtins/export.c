/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:23:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/21 17:24:47 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_after_equal(char **cpy_env, int i, int j, int *flag)
{
	ft_printf("declare -x ");
	while (cpy_env[i][j] != '\0')
	{
		if (cpy_env[i][j] == '=' && *flag == 0)
		{
			*flag = 1;
			ft_printf("=\"");
		}
		else
			ft_printf("%c", cpy_env[i][j]);
		j++;
	}
}

void	sorted_export(char **cpy_env)
{
	int		sorted;
	char	*tmp;
	int		i;
	int		len_env;

	len_env = 0;
	while (cpy_env[len_env])
		len_env++;
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

void	print_export(t_exec *exec, char **cpy_env)
{
	int	flag;
	int	flag2;
	int	j;
	int	i;

	i = 0;
	sorted_export(cpy_env);
	while (cpy_env[i] != NULL)
	{
		flag2 = 0;
		if (ft_strncmp(cpy_env[i], "_=", 2) != 0)
		{
			flag2 = 1;
			flag = 0;
			j = 0;
			print_after_equal(cpy_env, i, j, &flag);
			if (flag == 1)
				ft_printf("\"");
		}
		if (flag2 == 1)
			ft_printf("\n");
		i++;
	}
	exec->last_status = 0;
}

int	is_valid_export(char *cmd)
{
	int	i;

	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(&cmd[0], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (0);
	}
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(&cmd[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export(t_exec *exec, t_struct *data, char **cmd)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (!cmd[1])
		return (print_export(exec, data->env), 1);
	else
	{
		while (cmd[i])
		{
			if (is_valid_export(cmd[i]))
			{
				if (!add_or_replace_env_var(data, cmd[i]))
					return (exec->last_status = 1, 0);
			}
			else
				actualize_last_status(exec, &flag);
			i++;
		}
	}
	if (!flag)
		exec->last_status = 0;
	return (1);
}
