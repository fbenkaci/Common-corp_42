/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:11:27 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/14 17:08:38 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	expand_variable(t_struct **cur, char *str, char **envp)
{
	char	*current_str;
	char	*new_str;
	char	*var_name;
	char	*var_value;
	int		i;

	current_str = str;
	i = 0;
	while (current_str[i])
	{
		if (current_str[i] == '$' && current_str[i + 1]
			&& (ft_isalpha(current_str[i + 1]) || current_str[i + 1] == '_'))
		{
			// Extraire le nom de la variable
			var_name = extract_var_name(current_str, i + 1);
			if (!var_name)
				return (-1);
			var_value = get_env_value_2(var_name, envp);
			if (!var_value)
			{
				free((*cur)->str);
				(*cur)->str = ft_strdup("");
				return (1);
			}
			// Récupérer la valeur de la variable
			new_str = replace_variable(current_str, i, var_name, var_value);
			// Remplacer la variable dans la chaîne
			if (!new_str)
			{
				free(var_name);
				return (-1);
			}
			// Libérer l'ancienne chaîne si ce n'est pas l'originale
			if (current_str != str)
				free(current_str);
			free((*cur)->str);
			// Mettre à jour la chaîne dans le token
			// ft_printf("nexw ==  [%s]\n", new_str);
			(*cur)->str = ft_strdup(new_str);
			if (!(*cur)->str)
			{
				free(var_name);
				free(new_str);
				return (-1);
			}
			current_str = new_str;
			ft_printf("current_str == [%s]\n", current_str);
			free(var_name);
			// Recommencer depuis le début pour gérer les variables multiples
			i = 0;
			continue ;
		}
		i++;
	}
	// Libérer la chaîne temporaire si elle a été créée
	if (current_str != str)
		free(current_str);
	return (0);
}
