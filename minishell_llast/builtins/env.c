/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:25:08 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/15 15:52:35 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_struct *data, char **cmd)
{
	int	i;

	if (cmd[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd("‘", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd("‘", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	i = 0;
	while (data->env[i])
	{
		if (ft_strchr(data->env[i], '='))
			ft_printf("%s\n", data->env[i]);
		i++;
	}
	return (1);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_minishell *data = malloc(sizeof(t_minishell));
// 	char	**cmd;

// 	cpy_env(data, envp);
// 	cmd = malloc(sizeof(int) * 100);
// 	cmd[1] = "hello";
// 	(void)av;
// 	(void)ac;
// 	ft_env(data, cmd);
// 	// int i = 0;
// 	// ft_printf("%s", envp[i]);
// 	free(data);
// 	free(cmd);
// 	return (0);
// }
