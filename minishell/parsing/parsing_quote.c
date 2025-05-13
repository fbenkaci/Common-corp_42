/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 01:14:18 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/13 01:14:27 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_quote(t_struct *data)
{
	int	i;
	int	found_squote;
	int	found_dquote;

	found_squote = 0;
	found_dquote = 0;
	i = 0;
	while (data->str[i])
	{
		if (data->str[i] == '\'')
			found_squote = !found_squote;
		else if (data->str[i] == '\"')
			found_dquote = !found_dquote;
		i++;
	}
	if (found_squote)
		printf("Syntax error: unclosed single quote\n");
	if (found_dquote)
		printf("Syntax error: unclosed double quote\n");
}
