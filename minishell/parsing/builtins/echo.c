/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:25:02 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/17 17:27:42 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	ft_echo(char **cmd)
// {
// 	int	flag_n;
// 	int	i;

// 	flag_n = 0;
// 	i = 1;
// 	if (!cmd[1])
// 		return (ft_printf("\n"), 0);
// 	else if (cmd[1][0] == '-')
// 	{
// 		while (cmd[1][i] && cmd[1][i] == 'n')
// 		{
// 			flag_n = 1;
// 			i++;
// 		}
// 		if (cmd[1][i] != '\0' && cmd[1][i] != 'n')
// 			flag_n = 0;
// 		else if (cmd[1][i] == '\0' && !cmd[2])
// 			return (0);
// 	}
// 	if (flag_n)
// 		i = 2;
// 	else
// 		i = 1;
// 	while (cmd[i])
// 	{
// 		ft_printf("%s", cmd[i]);
// 		if (cmd[i + 1])
// 			ft_printf(" ");
// 		i++;
// 	}
// 	if (!flag_n)
// 		ft_printf("\n");
// 	return (1);
// }

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

int	ft_echo(char **cmd)
{
	int	flag_n;
	int	i;

	flag_n = 0;
	i = 1;
	if (!cmd[1])
		return (ft_printf("\n"), 0);
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n' && is_flag_n(cmd[i]))
	{
		flag_n = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[i + 1])
			ft_printf(" ");
		i++;
	}
	if (flag_n == 0)
		ft_printf("\n");
	return (1);
}

// int	main(void)
// {
// 	char **cmd;

// 	cmd = malloc(sizeof(char) * 100);
// 	cmd[0] = "echo";
// 	cmd[1] = "-n";
// 	cmd[2] = "comment";
// 	cmd[3] = "ça";
// 	// cmd[2] = "-nnnnnwn";
// 	// cmd[3] = "-a";
// 	cmd[4] = "va";
// 	ft_echo(cmd);
// }
