/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:28:44 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/15 15:51:54 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

// Fonction pour extraire le nom de variable
int	extract_var_name_2(char *line, int *i, char *var_name)
{
	int	k;

	(*i)++;
	k = 0;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
	{
		var_name[k++] = line[(*i)++];
	}
	var_name[k] = '\0';
	return (k);
}

// Fonction pour copier la valeur de variable dans le résultat
int	copy_var_value(t_expand_data *data, char *var_value)
{
	int	k;

	k = 0;
	while (var_value[k])
	{
		if (!resize_buffer_if_needed(data))
			return (0);
		data->result[data->j++] = var_value[k++];
	}
	return (1);
}

// Fonction pour traiter une variable trouvée
int	process_variable(t_struct **data2, char *line, int *i, t_expand_data *data)
{
	char	var_name[256];
	char	*var_value;

	extract_var_name_2(line, i, var_name);
	var_value = get_env_value_2(var_name, (*data2)->env);
	if (!copy_var_value(data, var_value))
		return (0);
	return (1);
}

// Fonction pour traiter un caractère normal
int	process_normal_char(char *line, int *i, t_expand_data *data)
{
	if (!resize_buffer_if_needed(data))
		return (0);
	data->result[data->j++] = line[(*i)++];
	return (1);
}

// Fonction principale refactorisée
char	*expand_variables_heredoc(t_struct **data2, char *line)
{
	t_expand_data	data;
	int				i;

	data.result = init_result_buffer(ft_strlen(line));
	if (!data.result)
		return (NULL);
	data.result_len = ft_strlen(line) * 2;
	data.j = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && (ft_isalnum(line[i + 1]) || line[i
					+ 1] == '_'))
		{
			if (!process_variable(data2, line, &i, &data))
				return (NULL);
		}
		else
		{
			if (!process_normal_char(line, &i, &data))
				return (NULL);
		}
	}
	data.result[data.j] = '\0';
	return (data.result);
}

// typedef struct s_var_params
// {
// 	char	*line;
// 	char	*result;
// 	int		i;
// 	int		*j;
// 	int		*result_len;
// }			t_var_params;

// char	*expand_env_variables(t_var_params **par)
// {
// 	char	*var_name;
// 	char	*var_value;
// 	int		k;

// 	k = 0;
// 	if ((*par)->line[(*par)->i] == '$' && (*par)->line[(*par)->i + 1]
// 		&& (ft_isalnum((*par)->line[(*par)->i + 1]) || (*par)->line[(*par)->i
// 			+ 1] == '_'))
// 	{
// 		(*par)->i++; // Passer le '$'
// 		k = 0;
// 		while ((*par)->line[(*par)->i] && (ft_isalnum((*par)->line[(*par)->i])
// 				|| (*par)->line[(*par)->i] == '_'))
// 			var_name[k++] = (*par)->line[(*par)->i++];
// 		var_name[k] = '\0';
// 		var_value = get_env_value_3(var_name);
// 		k = 0;
// 		while (var_value[k])
// 		{
// 			if ((*par)->j >= (*par)->result_len - 1)
// 			{
// 				*(*par)->result_len *= 2;
// 				(*par)->result = realloc((*par)->result, (*par)->result_len);
// 				if (!(*par)->result)
// 					return (NULL);
// 			}
// 			(*par)->result[*(*par)->j++] = var_value[k++];
// 		}
// 	}
// }

// Fonction pour expander les variables dans une ligne
// char	*expand_variables_heredoc(char *line)
// {
// 	char	*result;
// 	char	var_name[256];
// 	char	*var_value;
// 	int		result_len;
// 	int		i;
// 	int		j;
// 	int		k;

// 	// char *expanded;
// 	// Calculer la taille approximative nécessaire
// 	result_len = ft_strlen(line) * 2; // Estimation large
// 	result = malloc(result_len);
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '$' && line[i + 1] && (ft_isalnum(line[i + 1]) || line[i
// 				+ 1] == '_'))
// 		{
// 			// Début d'une variable
// 			i++; // Passer le '$'
// 			k = 0;
// 			// Extraire le nom de la variable
// 			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
// 			{
// 				var_name[k++] = line[i++];
// 			}
// 			var_name[k] = '\0';
// 			// Obtenir la valeur de la variable
// 			var_value = get_env_value_3(var_name);
// 			// Copier la valeur dans le résultat
// 			k = 0;
// 			while (var_value[k])
// 			{
// 				if (j >= result_len - 1)
// 				{
// 					result_len *= 2;
// 					result = realloc(result, result_len);
// 					if (!result)
// 						return (NULL);
// 				}
// 				result[j++] = var_value[k++];
// 			}
// 		}
// 		else
// 		{
// 			// Caractère normal
// 			if (j >= result_len - 1)
// 			{
// 				result_len *= 2;
// 				result = realloc(result, result_len);
// 				if (!result)
// 					return (NULL);
// 			}
// 			result[j++] = line[i++];
// 		}
// 	}
// 	result[j] = '\0';
// 	return (result);
// }

// // Gère l'extraction du nom de variable
// static int	extract_var_name_heredoc(char *line, int i, char *var_name)
// {
// 	int	k;

// 	k = 0;
// 	i++; // Passer le '$'
// 	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
// 	{
// 		var_name[k] = line[i];
// 		k++;
// 		i++;
// 	}
// 	var_name[k] = '\0';
// 	return (i);
// }

// // // Copie la valeur de la variable dans le résultat
// static int	copy_var_value(char *result, char *var_value, int j,
// 		int *result_len)
// {
// 	int	k;

// 	k = 0;
// 	while (var_value[k])
// 	{
// 		if (j >= *result_len - 1)
// 		{
// 			*result_len *= 2;
// 			result = realloc(result, *result_len);
// 			if (!result)
// 				return (-1);
// 		}
// 		result[j] = var_value[k];
// 		j++;
// 		k++;
// 	}
// 	return (j);
// }

// // // Copie un caractère normal dans le résultat
// static int	copy_normal_char(char *result, char c, int j, int *result_len)
// {
// 	if (j >= *result_len - 1)
// 	{
// 		*result_len *= 2;
// 		result = realloc(result, *result_len);
// 		if (!result)
// 			return (-1);
// 	}
// 	result[j] = c;
// 	return (j + 1);
// }

// Fonction principale
// Fonction pour initialiser le résultat
// static char *init_result_buffer(char *line)
// {
//     char *result;
//     int result_len;

//     result_len = ft_strlen(line) * 2;
//     result = malloc(result_len);
//     if (!result)
//         return (NULL);
//     return (result);
// }

// Fonction pour traiter une variable
// static int	process_variable(char *line, char *result, int i, int *j,
// 		int *result_len)
// {
// 	char	var_name[256];
// 	char	*var_value;
// 	int		new_i;

// 	new_i = extract_var_name_heredoc(line, i, var_name);
// 	var_value = get_env_value_3(var_name);
// 	*j = copy_var_value(result, var_value, *j, result_len);
// 	if (*j == -1)
// 		return (-1);
// 	return (new_i);
// }

// // Fonction pour traiter un caractère normal
// static int	process_normal_char(char *line, char *result, int i, int *j,
// 		int *result_len)
// {
// 	*j = copy_normal_char(result, line[i], *j, result_len);
// 	if (*j == -1)
// 		return (-1);
// 	return (0);
// }

// // Fonction pour vérifier si c'est une variable
// static int	is_variable_start(char *line, int i)
// {
// 	if (line[i] == '$' && line[i + 1] && (ft_isalnum(line[i + 1]) || line[i
// 			+ 1] == '_'))
// 		return (1);
// 	return (0);
// }

// // Fonction principale
// char	*expand_variables_heredoc(char *line)
// {
// 	char	*result;
// 	int		result_len;
// 	int		i;
// 	int		j;

// 	result_len = ft_strlen(line) * 2;
// 	result = malloc(result_len);
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (line[i])
// 	{
// 		if (is_variable_start(line, i))
// 		{
// 			i = process_variable(line, result, i, &j, &result_len);
// 			if (i == -1)
// 				return (NULL);
// 		}
// 		else
// 		{
// 			if (process_normal_char(line, result, i, &j, &result_len) == -1)
// 				return (NULL);
// 			i++;
// 		}
// 	}
// 	result[j] = '\0';
// 	return (result);
// }

// Fonction pour initialiser le résultat
// static char *init_result_buffer(char *line)
// {
//     char *result;
//     int result_len;

//     result_len = ft_strlen(line) * 2;
//     result = malloc(result_len);
//     if (!result)
//         return (NULL);
//     return (result);
// }

// Structure pour passer les paramètres
// typedef struct s_var_params
// {
// 	char	*line;
// 	char	*result;
// 	int		i;
// 	int		*j;
// 	int		*result_len;
// }			t_var_params;

// // Fonction pour traiter une variable
// static int	process_variable(t_var_params *params)
// {
// 	char	var_name[256];
// 	char	*var_value;
// 	int		new_i;

// 	new_i = extract_var_name_heredoc(params->line, params->i, var_name);
// 	var_value = get_env_value_3(var_name);
// 	*(params->j) = copy_var_value(params->result, var_value, *(params->j),
// 			params->result_len);
// 	if (*(params->j) == -1)
// 		return (-1);
// 	return (new_i);
// }

// // Fonction pour traiter un caractère normal
// static int	process_normal_char(t_var_params *params)
// {
// 	*(params->j) = copy_normal_char(params->result, params->line[params->i],
// 			*(params->j), params->result_len);
// 	if (*(params->j) == -1)
// 		return (-1);
// 	return (0);
// }

// // Fonction pour vérifier si c'est une variable
// static int	is_variable_start(char *line, int i)
// {
// 	if (line[i] == '$' && line[i + 1] && (ft_isalnum(line[i + 1]) || line[i
// 			+ 1] == '_'))
// 		return (1);
// 	return (0);
// }

// // Fonction pour initialiser les paramètres
// static void	init_params(t_var_params *params, char *line, char *result,
// int *j,
// 		int *result_len)
// {
// 	params->line = line;
// 	params->result = result;
// 	params->j = j;
// 	params->result_len = result_len;
// }

// // Fonction pour traiter la boucle principale
// static int	process_line_loop(char *line, t_var_params *params)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (is_variable_start(line, i))
// 		{
// 			params->i = i;
// 			i = process_variable(params);
// 			if (i == -1)
// 				return (-1);
// 		}
// 		else
// 		{
// 			params->i = i;
// 			if (process_normal_char(params) == -1)
// 				return (-1);
// 			i++;
// 		}
// 	}
// 	return (0);
// }

// // Fonction principale
// char	*expand_variables_heredoc(char *line)
// {
// 	char *result;
// 	int result_len;
// 	int j;
// 	t_var_params params;

// 	result_len = ft_strlen(line) * 2;
// 	result = malloc(result_len);
// 	if (!result)
// 		return (NULL);
// 	j = 0;
// 	init_params(&params, line, result, &j, &result_len);
// 	if (process_line_loop(line, &params) == -1)
// 		return (NULL);
// 	result[j] = '\0';
// 	return (result);
// }