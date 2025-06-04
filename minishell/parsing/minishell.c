/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:23:24 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/04 19:22:37 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_struct	*data;
	t_struct	*tmp;
	t_cmd		*cmd;
	t_exec		*exec;

	(void)argv;
	tmp = NULL;
	data = NULL;
	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (1);
	if (argc != 1)
	{
		printf("Error: need only one argument\n");
		return (1);
	}
	data = (t_struct *)malloc(sizeof(t_struct));
	if (!data)
	{
		perror("Error allocating memory");
		return (1);
	}
	if (cpy_env(data, envp) == -1)
		return (-1);
	while (1)
	{
		data->str = readline("💻 minishell > ");
		if (data->str == NULL)
			break ;
		if (ft_strlen(data->str) > 0)
		{
			add_history(data->str);
			if (parsing(data))
			{
				tmp = data->next;
				// while (tmp)
				// {
				// 	printf("{%d -> %s}\n", tmp->type, tmp->str);
				// 	tmp = tmp->next;
				// }
				cmd = create_cmd_from_tokens(&data->next, envp);
				execution(cmd, exec, &data);
			}
		}
		free(data->str);
	}
	free(data);
	return (0);
}
