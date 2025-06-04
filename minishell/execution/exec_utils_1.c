/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:15:20 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/03 17:41:18 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../parsing/minishell.h"

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
	// ft_printf("nb_cmd -- %d\n", data->nb_cmds);
	return (1);
}

int heredoc_input(char *delimiter)
{
	char *line;
	int fd[2];
	int line_nb;

	line_nb = 0;
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			ft_putstr_fd("warning: here-document at line ", 2);
			ft_putnbr_fd(line_nb, 2);
			ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("')", 2);
			break;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 && line[ft_strlen(delimiter)] == '\n')
		{
			// ft_printf("\n");
			free(line);
			break;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		line_nb++;
	}
	close(fd[1]);
	return (fd[0]);
}

// if (index == 0)
// {
// 	while (j < 2)
// 	{
// 		if (i != index || j != 1)
// 		{
// 			if (data->pipes[i][j])
// 				close(data->pipes[i][j]);
// 		}
// 		j++;
// 	}
// }
// else if (index == data->nb_cmds - 1)
// {
// 	while (j < 2)
// 	{
// 		if (i != index - 1 || j != 0)
// 		{
// 			if (data->pipes[i][j])
// 				close(data->pipes[i][j]);
// 		}
// 		j++;
// 	}
// }
// else
// {
// 	while (j < 2)
// 	{
// 		if ((i != index - 1 || j != 0) && (i != index || j != 1))
// 		{
// 			if (data->pipes[i][j])
// 				close(data->pipes[i][j]);
// 		}
// 		j++;
// 	}
// }