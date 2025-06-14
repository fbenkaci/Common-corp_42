/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:15:20 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/14 16:01:36 by fbenkaci         ###   ########.fr       */
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

// char *get_env_value23(char *var_name)
// {
//     char *value = getenv(var_name);
//     if (!value)
//         return ("");
//     return (value);
// }

// // Fonction pour expander les variables dans une ligne
// char *expand_variables_heredoc(char *line)
// {
//     char *result;
//     // char *expanded;
//     int i, j, k;
//     char var_name[256];
//     char *var_value;
//     int result_len;
    
//     // Calculer la taille approximative nécessaire
//     result_len = ft_strlen(line) * 2; // Estimation large
//     result = malloc(result_len);
//     if (!result)
//         return (NULL);
    
//     i = 0;
//     j = 0;
//     while (line[i])
//     {
//         if (line[i] == '$' && line[i + 1] && (ft_isalnum(line[i + 1]) || line[i + 1] == '_'))
//         {
//             // Début d'une variable
//             i++; // Passer le '$'
//             k = 0;
            
//             // Extraire le nom de la variable
//             while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
//             {
//                 var_name[k++] = line[i++];
//             }
//             var_name[k] = '\0';
            
//             // Obtenir la valeur de la variable
//             var_value = get_env_value23(var_name);
//             // Copier la valeur dans le résultat
//             k = 0;
//             while (var_value[k])
//             {
//                 if (j >= result_len - 1)
//                 {
//                     result_len *= 2;
//                     result = realloc(result, result_len);
//                     if (!result)
//                         return (NULL);
//                 }
//                 result[j++] = var_value[k++];
//             }
//         }
//         else
//         {
//             // Caractère normal
//             if (j >= result_len - 1)
//             {
//                 result_len *= 2;
//                 result = realloc(result, result_len);
//                 if (!result)
//                     return (NULL);
//             }
//             result[j++] = line[i++];
//         }
//     }
//     result[j] = '\0';
//     return (result);
// }

// int heredoc_input(char *delimiter)
// {
// 	char buffer[1024];
// 	char *line;
// 	int fd[2];
// 	int line_nb;
// 	int i;
// 	char c;
// 	int bytes_read;
// 	char *expanded_line;
	
// 	line_nb = 1;
// 	if (pipe(fd) == -1)
// 	{
// 		perror("pipe");
// 		return (-1);
// 	}
// 	while (1)
// 	{
// 		write(1, "> ", 2);
// 		i = 0;
// 		while (1)
// 		{
// 			bytes_read = read(0, &c, 1);
// 			if (bytes_read == 0)
// 			{
// 				if (i == 0)
// 				{
// 					ft_putstr_fd("\nminishell: warning: here-document at line ", 2);
// 					ft_putnbr_fd(line_nb, 2);
// 					ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
// 					ft_putstr_fd(delimiter, 2);
// 					ft_putstr_fd("')\n", 2);
// 					close(fd[1]);
// 					return (fd[0]);
// 				}
// 				else
// 					continue;
// 			}
// 			if (bytes_read == -1)
// 			{
// 				perror("read");
// 				close(fd[1]);
// 				close(fd[0]);
// 				return (-1);
// 			}
// 			buffer[i++] = c;
// 			if (c == '\n')
// 			{
// 				buffer[i] = '\0';
// 				break;
// 			}
// 			if (i >= 1023)
// 			{
// 				buffer[i] = '\0';
// 				break;
// 			}
			
// 		}
// 		line = buffer;
// 		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 && line[ft_strlen(delimiter)] == '\n')
// 		{
// 			break;
// 		}
// 		expanded_line = expand_variables_heredoc(line);
// 		write(fd[1], expanded_line, ft_strlen(expanded_line));
// 		free(expanded_line);
// 		line_nb++;
// 	}
// 	close(fd[1]);
// 	return (fd[0]);
// }

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