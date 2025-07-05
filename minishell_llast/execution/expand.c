/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:57:47 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/05 12:57:47 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	process_variable_expansion(t_struct **cur, char *str, char **envp, int i)
{
	char *var_name;
	char *var_value;
	char *new_str;

	var_name = extract_var_name(str, i + 1);
	if (!var_name)
		return (-1);
	var_value = get_env_value_2(var_name, envp);
	if (!var_value)
	{
		new_str = replace_variable(str, i, var_name, "");
		if (!new_str)
			return (free(var_name), -1);
		free(var_name);
		return (update_current_string(cur, str, new_str));
	}
	new_str = replace_variable(str, i, var_name, var_value);
	if (!new_str)
	{
		free(var_name);
		return (-1);
	}
	free(var_name);
	return (update_current_string(cur, str, new_str));
}

// Fonction pour gérer l'expansion de $?
static int	handle_exit_status_expansion(t_struct **cur, char *current_str,
		int i)
{
	char *exit_status_str;
	char *new_str;
	int result;

	exit_status_str = ft_itoa((*cur)->exec->last_status);
	if (!exit_status_str)
		return (-1);
	new_str = replace_variable(current_str, i, "?", exit_status_str);
	if (!new_str)
	{
		free(exit_status_str);
		return (-1);
	}
	free(exit_status_str);
	result = update_current_string(cur, current_str, new_str);
	return (result);
}

// Fonction pour gérer l'expansion des variables normales
static int	handle_normal_variable_expansion(t_struct **cur, char *current_str,
		char **envp, int i)
{
	int result;

	result = process_variable_expansion(cur, current_str, envp, i);
	return (result);
}

// Fonction pour traiter une position spécifique dans la chaîne
static int	process_char_at_position(t_struct **cur, char **current_str,
		char **envp, int *i)
{
	int result;

	if ((*current_str)[*i] == '$' && (*current_str)[*i + 1] == '?')
	{
		result = handle_exit_status_expansion(cur, *current_str, *i);
		if (result != 0)
			return (result);
		*current_str = (*cur)->str;
		*i = 0;
		return (0);
	}
	if ((*current_str)[*i] == '$' && (*current_str)[*i + 1]
		&& (ft_isalpha((*current_str)[*i + 1]) || (*current_str)[*i
			+ 1] == '_'))
	{
		result = handle_normal_variable_expansion(cur, *current_str, envp, *i);
		if (result != 0)
			return (result);
		*current_str = (*cur)->str;
		*i = 0;
		return (0);
	}
	(*i)++;
	return (0);
}

// Fonction principale d'expansion des variables
int	expand_variable(t_struct **cur, char *str, char **envp)
{
	char *current_str;
	int i;
	int result;

	current_str = str;
	i = 0;
	while (current_str[i])
	{
		result = process_char_at_position(cur, &current_str, envp, &i);
		if (result != 0)
			return (result);
	}
	return (0);
}
