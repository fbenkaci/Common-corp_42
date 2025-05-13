/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 01:13:33 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/13 07:57:11 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	utils_token(t_struct *data, int i)
{
	while (data->str[i] && data->str[i] != '\'' && data->str[i] != '\"'
		&& data->str[i] != '(' && data->str[i] != ')' && data->str[i] != '|'
		&& data->str[i] != ' ' && data->str[i] != '<')
	{
		data->type = WORD;
		i++;
	}
	i--;
	return (i);
}

void	is_token(t_struct *data)
{
	int	i;

	i = -1;
	while (++i, data->str[i])
	{
		if (data->str[i] == '\'')
			data->type = S_QUOTE;
		else if (data->str[i] == '\"')
			data->type = D_QUOTE;
		else if (data->str[i] == '(' || data->str[i] == ')')
			data->type = PARENTHESIS;
		else if (data->str[i] == '|')
			data->type = PIPE;
		else if (data->str[i] == ' ')
			data->type = SPACES;
		else if (data->str[i] == '>')
		{
			if (ft_strlen(&data->str[0]) > 1 && data->str[1] == '>')
				data->type = APPEND;
		}
		else if (data->str[i] == '<')
		{
			if (ft_strlen(&data->str[0]) > 1 && data->str[1] == '<')
				data->type = HEREDOC;
			else
				data->type = REDIR_IN;
		}
		else if(data->str[i] == '>')
			data->type = REDIR_OUT;
		else
			i = utils_token(data, i);
	}
}

void	parsing(t_struct *data)
{
	if (!data || !data->str)
		return ;
	data->type = NONE;
	is_token(data);
	parse_error_pipe(data);
	parse_redir(data);
	token_append(data);
	parsing_quote(data);
}
