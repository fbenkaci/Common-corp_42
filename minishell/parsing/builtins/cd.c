/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:11:03 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/19 11:27:55 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*update_env(char **envp, char *var, char *new_val_var)
{
	char	*new_string;
	int		len_var;
	int		i;

	len_var = ft_strlen(var);
	new_string = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(var, envp[i], len_var) == 0)
		{
			new_string = ft_strjoin(var, new_val_var);
			if (!new_string)
				return (NULL);
			envp[i] = new_string;
			if (ft_strcmp(var, "OLDPWD=") == 0)
				ft_printf("final old_pwd == %s\n", envp[i]);
			else
				ft_printf("final new_pwd == %s\n", envp[i]);
			return (new_string);
		}
		i++;
	}
	return (NULL);
}

char	*get_env_value(char **envp, char *key)
{
	int		len_key;
	char	*str;
	int		i;

	len_key = ft_strlen(key);
	str = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(key, envp[i], len_key) == 0)
		{
			str = envp[i] + len_key;
			return (str);
		}
		i++;
	}
	return (NULL);
}

int	update_pwd_vars(char **envp, char *oldpwd)
{
	char	*new_pwd;
	char	*env_new;
	char	*env_old;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		free(oldpwd);
		return (perror("getcwd"), 0);
	}
	env_old = update_env(envp, "OLDPWD=", oldpwd);
	env_new = update_env(envp, "PWD=", new_pwd);
	if (!env_old || !env_new)
	{
		free_all(new_pwd, oldpwd, env_old, env_new);
		return (ft_putstr_fd("error: PWD or OLDPWD dont exist.\n", 2), 0);
	}
	free_all(new_pwd, oldpwd, NULL, NULL);
	return (1);
}

int	cd_without_arg(char **envp)
{
	char	*home;
	char	*oldpwd;
	char	*new_pwd;

	new_pwd = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("getcwd"), 0);
	home = get_env_value(envp, "HOME=");
	if (!home)
	{
		free(oldpwd);
		return (ft_putstr_fd("cd: HOME not set\n", 2), 0);
	}
	if (chdir(home) == -1)
	{
		free(oldpwd);
		return (perror("chdir"), 0);
	}
	if (!update_pwd_vars(envp, oldpwd))
		return (0);
	return (1);
}

int	ft_cd(char **cmd, char **envp)
{
	if (!cmd[1])
	{
		if (!cd_without_arg(envp))
			return (0);
	}
	else if (!cd_path(envp, cmd[1]))
		return (0);
	return (1);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	**cmd;

// 	cmd = malloc(10000);
// 	(void)ac;
// 	(void)av;
// 	cmd[0] = "cd";
// 	// cmd[1] = "hello/ok";
// 	ft_cd(cmd, envp);
// 	free(cmd);
// 	return (0);
// }

// #include <stdio.h>

// // chdir function is declared
// // inside this header
// #include <unistd.h>

// int	main(void)
// {
// 	char s[100];

// 	// printing current working directory
// 	printf("%s\n", getcwd(s, 100));

// 	// using the command
// 	chdir("/home/fbenkaci/Common-corp_42/minishell");

// 	// printing current working directory
// 	printf("%s\n", getcwd(s, 100));
// 	ft_pwd();
// 	// after chdir is executed
// 	return (0);
// }