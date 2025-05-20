/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:23:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/20 11:43:12 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(char **cpy_envp)
{
	int	i;

	i = 0;
	while (cpy_envp[i])
	{
		if (ft_strncmp(cpy_envp[i], "_=", 2) != 0)
			ft_printf("declare -x %s\n", cpy_envp[i]);
		i++;
	}
}

void	sorted_export(char **cpy_envp, int len)
{
	int		sorted;
	char	*tmp;
	int		i;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (i < len - 1)
		{
			if (ft_strcmp(cpy_envp[i], cpy_envp[i + 1]) > 0)
			{
				tmp = cpy_envp[i];
				cpy_envp[i] = cpy_envp[i + 1];
				cpy_envp[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

int	export_without_args(char **envp)
{
	char	**cpy_envp;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (envp[len])
		len++;
	cpy_envp = malloc(sizeof(char *) * (len + 1));
	if (!cpy_envp)
		return (0);
	while (envp[i])
	{
		cpy_envp[i] = ft_strdup(envp[i]);
		if (!cpy_envp)
			return (ft_free_array(cpy_envp), 0);
		i++;
	}
	cpy_envp[i] = NULL;
	sorted_export(cpy_envp, len);
	print_export(cpy_envp);
	ft_free_array(cpy_envp);
	return (1);
}

// int	is_valid_export(char *cmd)
// {
// 	int flag;
// 	int	i;

// 	flag = 0;
// 	if (!cmd || (!ft_isalpha(cmd[0]) && cmd[0] != '_'))
// 		return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
// 	i = 1;
// 	while (cmd[i])
// 	{
// 		//gere quand ya des espaces
// 		if (cmd[i] == '=' && !flag)
// 		{
// 			flag = 1;
// 			if (cmd[i + 1] == '=')
// 				return (ft_putstr_fd("export: bad assignement\n", 2), 0);
// 		}
// 		// if (cmd[i] == ' ')
// 		// 	return (ft_putstr_fd("export: bad assignement\n", 2), 0);
// 		else if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
// 			return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
// 		i++;
// 	}
// 	return (1);
// }

int	is_valid_export(char *cmd)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
	while (cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]))
			return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
		i++;
	}
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			return (ft_putstr_fd("export: bad assignement\n", 2), 0);
		// if (cmd[i] == '=' && !flag)
		// {
		// 	flag = 1;
		// 	if (cmd[i + 1] == '=' && cmd[i + 2])
		// 		return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
		// }
		i++;
	}
	return (1);
}

int	update_or_add_env(char **envp, char *cmd)
{
	char	*var_name;
	int		len;
	int		i;

	// char	**cpy_envp;
	// char	*tmp;
	len = 0;
	i = 0;
	while (envp[i])
		len++;
	var_name = ft_substr(cmd, 0, len);
	if (!var_name)
		return (0);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0)
		{
			// free(envp[i]);
			// envp[i] = var_name;
		}
		i++;
	}
	// cpy_envp = malloc(sizeof(char *) * (i + 1));
	// if (!cpy_envp)
	// 	return (0);
	// i = 0;
	// while (envp[i])
	// {
	// 	cpy_envp[i] = ft_strdup(envp[i]);
	// 	if (!cpy_envp[i])
	// 		return (0);
	// 	i++;
	// }
	// i = 0;
	// while (cpy_envp[i])
	// {
	// 	j = 0;
	// 	while (cpy_envp[i][j] != '=')
	// 		j++;
	// 	if (ft_strncmp(&cmd[i], cpy_envp[i], j) == 0)
	// 	{
	// 		tmp = cpy_envp[i];
	// 		cpy_envp[i] = &cmd[i];
	// 		cmd[i] = *tmp;
	// 	}
	// 	ft_printf("%s\n", cpy_envp[i]);
	// 	i++;
	// }
	return (1);
}

int	ft_export(char **cmd, char **envp)
{
	int	i;

	i = 1;
	if (!cmd[1])
		export_without_args(envp);
	else
	{
		while (cmd[i])
		{
			if (!is_valid_export(cmd[i]) && cmd[i])
				i++;
			// Si la premiere commande est invalide et que la deuxieme est valide sa creer quand meme la deuxieme
			if (!update_or_add_env(envp, cmd[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	**cmd;

	(void)ac;
	(void)av;
	cmd = malloc(1000);
	cmd[0] = "export";
	cmd[1] = "q=b";
	cmd[2] = "a=";
	cmd[3] = "c=";
	ft_export(cmd, envp);
	free(cmd);
	return (0);
}
