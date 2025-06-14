/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:29:08 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/08 12:40:44 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// ICI, il faut free tout ce qui a ete malloc et fermer tous les fd

int	ft_exit(char **cmd)
{
	if (!cmd[1])
	{
		ft_printf("exit\n");
		exit(0);
	}
	else
		return (ft_putstr_fd("Error.Enter exit with no args\n", 2), 0);
}
