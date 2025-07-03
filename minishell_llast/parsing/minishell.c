/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:23:24 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/02 15:21:24 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t			g_signal_status = 0;


void	free_token_chain(t_struct *tokens)
{
	t_struct	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->str)
		{
			free(tokens->str);
			tokens->str = NULL;
		}
		free(tokens);
		tokens = tmp;
	}
}

void	free_tokens(t_struct *data)
{
	t_struct	*tmp;

	while (data)
	{
		if (data->env)
			ft_free_array(data->env);
		tmp = data->next;
		if (data->str)
			free(data->str);
		free(data);
		data = tmp;
	}
}

void	cleanup_all_data(t_struct *data)
{
	if (data->token_pool)
	{
		reset_token_pool(data->token_pool);
		data->next = NULL;
	}
	if (data->str)
	{
		free(data->str);
		data->str = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	*data;
	t_cmd		*cmd;
	t_exec		*exec;

	(void)argv;
	data = NULL;
	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (1);
	exec->path = NULL;
	exec->pipes = 0;
	exec->cmds = NULL;
	if (argc != 1)
	{
		printf("Error: need only one argument\n");
		free(exec);
		return (1);
	}
	data = malloc(sizeof(t_struct));
	if (!data)
	{
		perror("Error allocating memory");
		free(exec);
		return (1);
	}
	data->token_pool = init_token_pool(100);
	if (!data->token_pool)
	{
		perror("Error allocating token pool");
		free(exec);
		free(data);
		return (1);
	}
	if (cpy_env(data, envp) == -1)
	{
		free_token_pool(data->token_pool);
		free(exec);
		free(data);
		return (1);
	}
	data->exec = exec;
	data->next = NULL;
	exec->last_status = 0;
	while (1)
	{
		g_signal_status = 0;
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		data->str = readline("💻 minishell > ");
		if (data->str == NULL)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			reset_token_pool(data->token_pool);
			data->next = NULL;
			break ;
		}
		if (ft_strlen(data->str) > 0)
		{
			add_history(data->str);
			if (parsing(data))
			{
				cmd = create_cmd_from_tokens(&data->next, data->env, exec);
				if (!cmd)
				{
					// Ne pas sortir du shell pour les erreurs de redirection
					// Juste nettoyer et continuer
					reset_token_pool(data->token_pool);
					data->next = NULL;
				}
				else
				{
					execution(cmd, exec, &data);
					free_all_cmd(cmd);
					reset_token_pool(data->token_pool);
					data->next = NULL;
					if (g_signal_status == 130)
					{
						rl_on_new_line();
						rl_replace_line("", 0);
					}
				}
			}
			else
			{
				reset_token_pool(data->token_pool);
				data->next = NULL;
			}
		}
		else
		{
			reset_token_pool(data->token_pool);
			data->next = NULL;
		}
		free(data->str);
		data->str = NULL;
		data->str = NULL;
	}
	clear_history();
	rl_clear_history();
	if (data)
	{
		if (data->env)
			ft_free_array(data->env);
		if (data->str)
		{
			free(data->str);
			data->str = NULL;
		}
		if (data->token_pool)
			free_token_pool(data->token_pool);
		free(data);
	}
	if (exec)
		free(exec);
	return (0);
}
