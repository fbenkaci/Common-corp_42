/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:23 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/27 16:01:06 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_exec *exec, t_struct *data, t_cmd *cmd)
{
	if (ft_strcmp(*cmd->argv, "echo") == 0)
		return (ft_echo(exec ,cmd->argv));
	else if (ft_strcmp(*cmd->argv, "cd") == 0)
		return (ft_cd(exec, data, cmd->argv));
	else if (ft_strcmp(*cmd->argv, "env") == 0)
		return (ft_env(exec, data, cmd->argv));
	else if (ft_strcmp(*cmd->argv, "exit") == 0)
		return (ft_exit(exec, data, cmd));
	else if (ft_strcmp(*cmd->argv, "export") == 0)
		return (ft_export(exec, data, cmd->argv));
	else if (ft_strcmp(*cmd->argv, "pwd") == 0)
		return (ft_pwd(exec));
	else if (ft_strcmp(*cmd->argv, "unset") == 0)
		return (ft_unset(exec, data, cmd->argv));
	else
		return (0);
	return (1);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_struct	*data;
// 	char		**cmd;

// 	(void)ac;
// 	(void)av;
// 	data = malloc(sizeof(t_struct));
// 	cmd = malloc(1000);
// 	if (!cpy_env(data, envp))
// 		return (0);
// 	cmd[0] = "cd";
// 	// cmd[1] = "VAR1";
// 	cmd[1] = NULL;

// 	exec_builtin(data, cmd);

// 	ft_free_array(data->env);
// 	free(cmd);
// 	free(data);
// 	return (0);
// }

// -------------- POUR UNSET ---------------

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

// ------------- POUR EXPORT ----------------

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
// 	ft_printf("------------ Avant export ------------\n\n\n");
// 	while (data->env[i])
// 	{
// 		ft_printf("%s\n", data->env[i]);
// 		i++;
// 	}
// 	ft_printf("------------ apres export ------------\n\n\n");
// 	nb = ft_export(data, cmd);
// 	i = 0;

// 	free(cmd);
// 	ft_free_array(data->env);
// 	free(data);
// 	return (0);
// }

// ----------- POUR ECHO ----------
// Avec le "-n" il n'y pas de saut a la ligne a la fin

// int	main(void)
// {
// 	char **cmd;

// 	cmd = malloc(sizeof(char) * 100);
// 	cmd[0] = "echo";
// 	cmd[1] = "-nnnnnnn";
// 	cmd[2] = "comment";
// 	// cmd[2] = "ça";
// 	// cmd[2] = "-nnnnnwn";
// 	// cmd[3] = "-a";
// 	// cmd[3] = "va";
// 	ft_echo(cmd);
// }

// ------------------- POUR ENV ---------------

// int	main(int ac, char **av, char **envp)
// {
// 	t_struct *data = malloc(sizeof(t_struct));
// 	char	**cmd;

// 	cpy_env(data, envp);
// 	cmd = malloc(sizeof(int) * 100);
// 	// cmd[1] = "hello";
// 	(void)av;
// 	(void)ac;
// 	ft_env(data, cmd);
// 	// int i = 0;
// 	// ft_printf("%s", envp[i]);
// 	free(data);
// 	free(cmd);
// 	return (0);
// }

// ---------- POUR PWD -----------

// int main(void)
// {
// 	ft_pwd();

// 	return (0);
// }