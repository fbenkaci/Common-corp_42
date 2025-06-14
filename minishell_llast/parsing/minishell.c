/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:23:24 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/14 13:10:12 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_struct *tokens)
{
	t_struct	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->str)
			free(tokens->str);
		free(tokens);
		tokens = tmp;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	*data;
	t_struct	*tmp;
	t_cmd		*cmd;
	t_exec		*exec;

	// int			flag;
	// t_cmd *prev_cmd = NULL;
	(void)argv;
	tmp = NULL;
	data = NULL;
	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (1);
	if (argc != 1)
	{
		printf("Error: need only one argument\n");
		free(exec);
		return (1);
	}
	data = (t_struct *)malloc(sizeof(t_struct));
	if (!data)
	{
		perror("Error allocating memory");
		free(exec);
		return (1);
	}
	if (cpy_env(data, envp) == -1)
	{
		free(exec);
		free(data);
		return (1);
	}
	while (1)
	{
		signal(SIGINT, handle_sigint);
		// signal(SIGQUIT, handle_sigquit);
		// data->str = readline("💻 minishell > ");
		data->str = readline("💻 minishell > ");
		if (data->str == NULL)
		{
			// ft_free_array(data->env);
			// free(exec);
			// free(data);
			break ;
		}
		if (ft_strlen(data->str) > 0)
		{
			add_history(data->str);
			if (parsing(data))
			{
				// tmp = data->next;
				// while (tmp)
				// {
				// 	printf("{%d -> %s}\n", tmp->type, tmp->str);
				// 	tmp = tmp->next;
				// }
				cmd = create_cmd_from_tokens(&data->next, data->env);
				if (!cmd)
				{
					free_tokens(data->next);
					ft_free_array(data->env);
					free(data->str);
					free(exec);
					free(data);
					return (1);
				}
				execution(cmd, exec, &data);
				free_all_cmd(cmd);
				free_tokens(data->next);
				// free(data->str);
			}
		}
	}
	ft_free_array(data->env);
	free(data->str);
	free(exec);
	free(data);
	// free(data);
	return (0);
}
