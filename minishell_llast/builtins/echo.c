/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:25:02 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/18 15:25:18 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_flag_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else if (str[i] != 'n' && str[i] != '\0')
			return (0);
	}
	return (1);
}

int	ft_echo(t_exec *exec, char **cmd)
{
	int	flag_n;
	int	i;

	flag_n = 0;
	i = 1;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n' && is_flag_n(cmd[i]))
	{
		flag_n = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] && cmd[i + 1][0] != '\0')
			printf(" ");
		i++;
	}
	if (flag_n == 0)
		printf("\n");
	exec->last_status = 0;
	return (1);
}

// int	main(void)
// {
// 	char **cmd;

// 	cmd = malloc(sizeof(char) * 100);
// 	cmd[0] = "echo";
// 	cmd[1] = "comment";
// 	cmd[2] = "-nnnnnnn";
// 	// cmd[2] = "ça";
// 	// cmd[2] = "-nnnnnwn";
// 	// cmd[3] = "-a";
// 	// cmd[3] = "va";
// 	ft_echo(cmd);
// }
