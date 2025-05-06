/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:12:04 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/05 19:02:13 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_pipex(ac, av, envp)
{
	int	fd[ac - 3][2];
	int	nb_cmds;
	int	i;
	nb_cmds = ac - 3;
    
	int	pipes[2 * (nb_cmds - 1)];
	i = 0;
	while (i < nb_cmds)
	{
		if (pipe(fd[i]) == -1)
			return (1);
		i++;
	}
}
