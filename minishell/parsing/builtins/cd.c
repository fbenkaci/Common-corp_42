/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:11:03 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/15 17:29:16 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void update_env(char **envp, char *var, char *new_val_var)
{
    char *new_string = NULL;
    int len_var;
    int i;
    
    len_var = ft_strlen(var);
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(var, envp[i], len_var) == 0)
        {
            ft_printf("%s\n", envp[i]);
            new_string = ft_strjoin(var, new_val_var);
            break;
        }
        i++;
    }
    envp[i] = new_string;
    ft_printf("%s\n", envp[i]);
}

char	*get_env_value(char **envp, char *key)
{
	char	*str;
	int		len_key;
	int		i;

	str = NULL;
	len_key = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(key, envp[i], len_key) == 0)
		{
			str = envp[i] + len_key;
			break ;
		}
		i++;
	}
	return (str);
}

void	ft_cd(char **cmd, char **envp)
{
	char	*home;
	char	*oldpwd;
	char	*new_pwd;

	home = NULL;
	if (!cmd[1])
	{
		oldpwd = getcwd(NULL, 0);
		if (!oldpwd)
			perror("getcwd");
            
		home = get_env_value(envp, "HOME=");
		if (chdir(home) == -1)
			perror("chdir");
            
        new_pwd = getcwd(NULL, 0);
		if (!new_pwd)
        {
            perror("getcwd");
        }
        update_env(envp, "OLDPWD=", oldpwd);
        update_env(envp, "PWD=", new_pwd);
	}
}

int	main(int ac, char **av, char **envp)
{
	// char	**cmd;

	// cmd = malloc(100);
	(void)ac;
	(void)av;
	// cmd[0] = "cd";
    
	// cmd[1] = "cd";
	update_env(envp, "OLDPWD=","hello");
	// ft_printf("%s\n", str);
	return (0);
}

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