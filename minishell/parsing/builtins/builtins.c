/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:23 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/14 19:32:00 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_pipex *data, char **cmd, char **envp)
{
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(cmd, envp);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(cmd);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(cmd);
	else
		return (0);
	return (1);
}
