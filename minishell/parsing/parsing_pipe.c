/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 01:13:56 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/15 13:29:39 by fbenkaci         ###   ########.fr       */
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

void	parse_error_pipe(t_struct *data)
{
	int	i;
	int	found_pipe;

	i = 0;
	found_pipe = 0;
	while (data->str[i] && data->str[i] == ' ')
		i++;
	if (data->str[i] == '|')
	{
		printf("Syntax error near: unexpected token '|'\n");
		return ;
	}
	i = utils_parse_pipe(data, i, &found_pipe);
	if (found_pipe > 0)
		printf("Syntax error near: unexpected token '|'\n");
}
