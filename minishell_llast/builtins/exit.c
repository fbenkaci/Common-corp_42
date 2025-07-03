/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:29:08 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/01 15:59:09 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	error_msg(char *num)
{
	printf("exit\n");
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(num, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	valid_number(char *num)
{
	long long	i;

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
	long long	exit_code_ll;
	int			exit_code;

	exit_code = 0;
	if (cmd->argv[2])
		return (exec->last_status = 1,
			ft_putstr_fd("minishell: exit: too many arguments\n", 2), 0);
	if (!cmd->argv[1])
	{
		exit_code = exec->last_status;
		printf("exit\n");
		free_all_shell_parent(&data, exec, cmd);
		exit(exit_code);
	}
	if (!valid_number(cmd->argv[1]) || !ft_atoll_safe(cmd->argv[1],
			&exit_code_ll))
	{
		error_msg(cmd->argv[1]);
		free_all_shell_parent(&data, exec, cmd);
		exit(2);
	}
	exit_code = (int)(exit_code_ll % 256);
	printf("exit\n");
	free_all_shell_parent(&data, exec, cmd);
	exit(exit_code);
}
