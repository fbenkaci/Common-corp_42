/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:48:22 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/05/15 12:28:15 by wlarbi-a         ###   ########.fr       */
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
		printf("Syntax error near: unexpected token '|'\n");
		return (0);
	}
	i = utils_parse_pipe(data, i, &found_pipe);
	if (found_pipe > 0)
	{
		printf("Syntax error near: unexpected token '|'\n");
		return (0);
	}
	return (1);
}
