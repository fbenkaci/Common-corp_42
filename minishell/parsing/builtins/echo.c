/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:25:02 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/13 17:34:02 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"

int	ft_echo(char **cmd)
{
	int	flag_n;
	int	i;

	flag_n = 1;
	i = 1;
	if (!cmd[1])
		return (ft_printf("\n"), 0);
	if (ft_strcmp(cmd[1], "-n") == 0 && !cmd[2])
		return (0);
	else if (cmd[1][0] == '-')
	{
		while (cmd[1][i] && cmd[1][i] == 'n' && !cmd[2])
			i++;
		if (cmd[1][i] == '\0')
			return (0);
	}
	if (ft_strcmp(cmd[1], "-n") == 0)
		flag_n = 1;
	else if (cmd[1][0] == '-')
	{
		while (cmd[1][i] && cmd[1][i] == 'n')
		{
			flag_n = 1;
			i++;
		}
		// if (cmd[1][i] == '\0')
		//     flag_n = 0;
	}
	if (flag_n)
		i = 2;
	else
		i = 1;
	while (cmd[i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!flag_n)
		ft_printf("\n");
	return (1);
}

int	main(void)
{
	char	**cmd;

	cmd = malloc(sizeof(char) * 100);
	cmd[0] = "echo";
	cmd[1] = "-nan";
	cmd[2] = "hello";
	// cmd[3] = "hello";
	ft_echo(cmd);
}
