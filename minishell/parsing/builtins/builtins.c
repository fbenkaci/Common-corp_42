/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:23 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/20 11:40:26 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	exec_builtin(char **cmd, char **envp)
{
	if (ft_strcmp(*cmd, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(*cmd, "cd") == 0)
	{
		if (!ft_cd(cmd, envp))
			return (0);
	}
	else if (ft_strcmp(*cmd, "env") == 0)
		ft_env(cmd, envp);
	else if (ft_strcmp(*cmd, "exit") == 0)
		ft_exit(cmd);
	else if (ft_strcmp(*cmd, "export") == 0)
		ft_export(cmd, envp);
	else if (ft_strcmp(*cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(*cmd, "unset") == 0)
		ft_unset(envp, cmd);
	else
		return (0);
	return (1);
}

// int main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	(void)av;
// 	// t_pipex *data = NULL;
// 	char **cmd = malloc(1000);
	
// 	cmd[0] = "exit";
// 	cmd[1] = "exit";
	
// 	exec_builtin(cmd, envp);
// 	return (0);	
// }
