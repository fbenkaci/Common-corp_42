/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:15:20 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/19 15:23:31 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	ft_lstsize_bis(t_cmd *cmd)
{
	int	nbr_element;

	if (!cmd)
		return (-1);
	nbr_element = 0;
	while (cmd)
	{
		nbr_element++;
		cmd = cmd->next;
	}
	return (nbr_element);
}

void	close_pipes(t_exec *data, int index, int i, int j)
{
	int	should_close;

	should_close = 0;
	if (index == 0)
	{
		should_close = (i != index || j != 1); // Sa c'est quand je suis sur la 1ere cmd donc si index == 0 je veux fermer tout sauf data->pipe[0][1] prcq je vais ecrire dessus
	}
	else if (index == data->nb_cmds - 1)
	{
		should_close = (i != index - 1 || j != 0); // Sa c'est quand je suis sur la derniere cmd donc si c'est la derniere commande je veux fermer tout sauf data->pipe[index - 1][0]
	}											   // (c'est le dernier pipes) prcq je vais lire dessus
	else
	{
		should_close = ((i != index - 1 || j != 0) && (i != index || j != 1)); // Sa c'est quand je suis sur les cmd du millieux, je veux tout fermer sauf la partie lecture du pipe precedent  
	}																		  // (pipe[index -1][0]) prcq je vais lire desssus et la partie ecriture du pipe courant (pipe[index][1]) prcq j'ecris dessus
	if (should_close && data->pipes[i][j] != -1)
	{
		close(data->pipes[i][j]);
		data->pipes[i][j] = -1; // Je met a -1 pour eviter de le fermer 2 fois 
	}
}

void	close_unused_pipes(t_exec *data, int index)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_cmds - 1)
	{
		j = 0;
		while (j < 2)
		{
			close_pipes(data, index, i, j);
			j++;
		}
		i++;
	}
}

int	caculate_nb_cmd(t_exec *data, t_cmd *cmd)
{
	if (!cmd)
		return (-1);
	data->nb_cmds = ft_lstsize_bis(cmd);
	return (1);
}
