/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:11:40 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/25 20:00:50 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redir(t_struct *data, int i, int *found_redir)
{
	if (data->str[i] == '>')
	{
		if (*found_redir && (i == 0 || data->str[i - 1] != '<'))
			return (-1);
		if (data->str[i + 1] && data->str[i + 1] == '>')
			i++;
		*found_redir = 1;
		i++;
	}
	else if (data->str[i] == '<')
	{
		if (*found_redir && (!data->str[i + 1] || data->str[i + 1] != '>'))
			return (-1);
		if (data->str[i + 1])
		{
			if (data->str[i + 1] == '<' || data->str[i + 1] == '>')
				i++;
		}
		*found_redir = 1;
		i++;
	}
	return (i);
}

int	utils_parse_redir(t_struct *data, int i, int *found_redir)
{
	while (data->str[i])
	{
		if (data->str[i] == '>' || data->str[i] == '<')
		{
			i = handle_redir(data, i, found_redir);
			if (i == -1)
				return (-1);
		}
		else if (data->str[i] == ' ')
			i++;
		else
		{
			*found_redir = 0;
			while (data->str[i] && data->str[i] != ' ' && data->str[i] != '>'
				&& data->str[i] != '<')
				i++;
		}
	}
	if (*found_redir)
		return (-1);
	return (i);
}

int	parse_redir(t_struct *data)
{
	int	i;
	int	found_redir;

	i = 0;
	found_redir = 0;
	while (data->str[i] && data->str[i] == ' ')
		i++;
	i = utils_parse_redir(data, i, &found_redir);
	if (i == -1)
	{
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
		exit(2);
	}
	return (1);
}
