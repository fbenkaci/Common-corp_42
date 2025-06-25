/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:48:22 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/25 20:07:30 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	utils_parse_pipe(t_struct *data, int i, int *found_pipe)
{
	while (data->str[i])
	{
		if (data->str[i] == '|')
		{
			if (*found_pipe)
			{
				*found_pipe = 2;
				return (0);
			}
			*found_pipe = 1;
			i++;
		}
		else if (data->str[i] == ' ')
			i++;
		else
		{
			*found_pipe = 0;
			while (data->str[i] && data->str[i] != ' ' && data->str[i] != '|')
				i++;
		}
	}
	return (i);
}

int	parse_error_pipe(t_struct *data)
{
	int	i;
	int	found_pipe;

	i = 0;
	found_pipe = 0;
	while (data->str[i] && data->str[i] == ' ')
		i++;
	if (data->str[i] == '|')
	{
		ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
		data->exec->last_status = 2;
		return (0);
	}
	i = utils_parse_pipe(data, i, &found_pipe);
	if (found_pipe > 0)
	{
		ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
		data->exec->last_status = 2;
		return (0);
	}
	return (1);
}
