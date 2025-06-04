/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:21:49 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/05/23 17:15:17 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_quote(t_struct *data)
{
	int	i;
	int	found_squote;
	int	found_dquote;

	found_squote = 0;
	found_dquote = 0;
	i = -1;
	while (++i, data->str[i])
	{
		if (data->str[i] == '\'')
			found_squote = !found_squote;
		else if (data->str[i] == '\"')
			found_dquote = !found_dquote;
	}
	if (found_squote)
	{
		printf("Syntax error: unclosed single quote\n");
		return (0);
	}
	if (found_dquote)
	{
		printf("Syntax error: unclosed double quote\n");
		return (0);
	}
	return (1);
}
