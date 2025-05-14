/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:25:08 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/14 19:53:47 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"

void	ft_env(char **cmd, char **envp)
{
	int	i;

	if (cmd[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_printf("%s\n", envp[i]);
		i++;
	}
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	**cmd;

// 	cmd = malloc(sizeof(int) * 100);
// 	// cmd[1] = "hello";
// 	(void)av;
// 	(void)ac;
// 	ft_env(cmd, envp);
// 	// int i = 0;
// 	// ft_printf("%s", envp[i]);
// 	return (0);
// }
