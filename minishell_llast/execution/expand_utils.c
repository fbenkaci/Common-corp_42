/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:12:39 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/19 15:04:32 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"
#include <stddef.h>

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*get_env_value_2(char *var_name, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (&envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

// Fonction pour extraire le nom de variable après $
char	*extract_var_name(char *str, int start)
{
	int		i;
	int		len;
	char	*var_name;

	i = start;
	len = 0;
	// Calculer la longueur du nom de variable
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		len++;
		i++;
	}
	if (len == 0)
		return (NULL);
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, &str[start], len);
	var_name[len] = '\0';
	return (var_name);
}

int	calculate_new_length(char *str, char *var_name, char *var_value)
{
	int	original_len;
	int	var_name_len;
	int	var_value_len;
	int	new_len;

	original_len = ft_strlen(str);
	var_name_len = ft_strlen(var_name);
	if (var_value)
		var_value_len = ft_strlen(var_value);
	else
		var_value_len = 0;
	new_len = original_len - var_name_len - 1 + var_value_len;
	return (new_len);
}

int	copy_before_dollar(char *new_str, char *str, char dollar_pos)
{
	int	i;

	i = 0;
	while (i < dollar_pos)
	{
		new_str[i] = str[i];
		i++;
	}
	return (i);
}

int	copy_variable_value(char *var_value, char *new_str, int start_pos)
{
	int	i;
	int	j;

	i = start_pos;
	j = 0;
	if (var_value)
	{
		while (var_value[j])
		{
			new_str[i] = var_value[j];
			i++;
			j++;
		}
	}
	return (i);
}
// Fonction pour remplacer une variable dans une chaîne
char	*replace_variable(char *str, int dollar_pos, char *var_name,
		char *var_value)
{
	char	*new_str;
	int		i;
	int		j;
	int		new_len;
	int		var_name_len;

	new_len = calculate_new_length(str, var_name, var_value);
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	i = copy_before_dollar(new_str, str, dollar_pos);
	// Copier la valeur de la variable (si elle existe)
	i = copy_variable_value(var_value, new_str, i);
	var_name_len = ft_strlen(var_name);
	// Copier la partie après la variable
	j = dollar_pos + var_name_len + 1; // +1 pour le $
	while (str[j])
	{
		new_str[i] = str[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}
