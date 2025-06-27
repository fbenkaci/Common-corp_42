/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:29:08 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/27 20:26:09 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	error_msg(char *num)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(num, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	valid_number(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-' || num[i] == '+')
		i++;
	if (!num[i])
	{
		i--;
		return (0);
	}
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_exec *exec, t_struct *data, t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->argv[2])
	{
		exec->last_status = 1;
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 0);
	}
	if (!cmd->argv[1])
	{
		exit_code = exec->last_status;
		printf("exit\n");
		free_all_shell(&data, exec, cmd);
		exit(exit_code);
	}
	if (!valid_number(cmd->argv[1]))
	{
		printf("exit\n");
		error_msg(cmd->argv[1]);
		free_all_shell(&data, exec, cmd);
		exit(2);
	}
	exit_code = ft_atoi(cmd->argv[1]);
	free_all_shell(&data, exec, cmd);
	exit(exit_code);
}
