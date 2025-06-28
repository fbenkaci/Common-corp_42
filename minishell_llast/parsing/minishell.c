/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:23:24 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/27 17:22:39 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

void	free_tokens(t_struct *data)
{
	t_struct	*tmp;
	
	while (data)
	{
		tmp = data->next;
		if (data->env)
				ft_free_array(data->env);
		if (data->str)
			free(data->str);
		free(data);
		data = tmp;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	*data;
	t_cmd		*cmd;
	t_exec		*exec;

	// t_garbage	gc;
	// t_struct	*tmp;
	(void)argv;
	data = NULL;
	// init_garbage(&gc);
	exec = malloc(sizeof(t_exec));
	exec->pipes = 0;
	exec->path = NULL;
	// exec = gc_malloc(sizeof(t_exec), &gc);
	if (!exec)
		return (1);
	if (argc != 1)
	{
		printf("Error: need only one argument\n");
		// free_garbage(&gc);
		return (1);
	}
	data = malloc(sizeof(t_struct));
	if (!data)
	{
		perror("Error allocating memory");
		// free_garbage(&gc);
		free(exec);
		return (1); // Ajoutez cette fonction à la fin du fichier
	}
	data->env = NULL;
	data->str = NULL;
	data->next = NULL;
	if (cpy_env(data, envp) == -1)
	{
		// free_garbage(&gc);
		free(exec);
		free(data);
		return (1);
	}
	data->exec = exec;
	exec->last_status = 0;
	while (1)
	{
		// exec->last_status = g_signal_status;
		g_signal_status = 0;
		signal(SIGINT, handle_sigint);
		// Je remplace le comportement de ctrl+c par le mien
		signal(SIGQUIT, SIG_IGN);
		// je capture le signal quit et je lui dis de l'ignore dans le parent pour éviter le core dumped. Mon shell ne doit pas crasher.
		data->str = readline("💻 minishell > ");
		if (data->str == NULL)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
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
				cmd = create_cmd_from_tokens(&data->next, data->env, exec);
				if (!cmd)
				{
					// free_garbage(&gc)
					free_tokens(data->next);
					free(exec);
					free(data);
					return (1);
				}
				// ft_printf("%d\n", exec->last_status);
				// gc.cmd = cmd;
				// free_tokens(data->next);
				execution(cmd, exec, &data);
				// ft_printf("%d\n", exec->last_status);
				free_all_cmd(cmd);
				// free_tokens(data->next);
				// free(exec->pipes);
			}
		}
	}
	free_tokens(data);
	// free(data);
	// ft_free_array(data->env);
	// free(data->str);
	// data->str = NULL;
	free(exec);
	// free(data);
	// free_garbage(&gc);
	return (0);
}
