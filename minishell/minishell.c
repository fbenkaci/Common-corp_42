/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 01:12:37 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/22 17:03:40 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

int	build_from_tokens(t_pipex *data, t_struct *tok)
{
	int			count;
	t_struct	*cur;
	int			i;
	int			idx;
	char		**argv;
	int			argc;
	char		**tmp;
	int			j;

	count = 1; // jcommence à 1 prcq ya minimum une commande
	cur = tok;
	// Tu compte le nombre de commande
	while (cur)
	{
		if (cur->type == PIPE)
			count++;
		cur = cur->next;
	}
	data->nb_cmds = count;
	// la j'alloue dla mémoire pour les structures qui contiendront des info sur chaquie comande
	data->cmds = malloc(sizeof(char **) * count);
	// Contient les arguments pour chaque comment
	data->in_files = malloc(sizeof(char *) * count);
	// Chaque élément représente un fichier d'entrée
	data->out_files = malloc(sizeof(char *) * count);
	// Contient les fichiers de sortie
	data->modes = malloc(sizeof(int) * count);
	// Chque elmt represnt un mode d'ouverture
	data->here_doc = malloc(sizeof(int) * count);
	// sert a savoir si une comande est ui herdoc
	if (!data->cmds || !data->in_files || !data->out_files || !data->modes
		|| !data->here_doc)
		return (0);
	i = 0;
	// la j'init tt pr eviter les pb avec valgrind
	while (i < count)
	{
		data->in_files[i] = NULL;
		data->out_files[i] = NULL;
		data->modes[i] = 0;
		data->here_doc[i] = 0;
		i++;
	}
	cur = tok;
	idx = 0;
	argv = NULL;
	argc = 0;
	// la je parcour les token pour contruire les arguments des commandes
	while (cur)
	{
		// SELON LE TYPE J'EXECUTE UN CODE 
		if (cur->type == WORD)
		{
			tmp = malloc(sizeof(char *) * (argc + 2));
			j = 0;
			while (j < argc)
			{
				tmp[j] = argv[j];
				j++;
			}
			tmp[argc] = strdup(cur->str);
			tmp[argc + 1] = NULL;
			free(argv);
			argv = tmp;
			argc++;
		}
		else if (cur->type == REDIR_IN || cur->type == HEREDOC)
		{
			data->in_files[idx] = strdup(cur->next->str);
			data->modes[idx] = O_RDONLY;
			if (cur->type == HEREDOC)
				data->here_doc[idx] = 1;
		}
		else if (cur->type == REDIR_OUT)
		{
			data->out_files[idx] = strdup(cur->next->str);
			data->modes[idx] = O_CREAT | O_WRONLY | O_TRUNC;
		}
		else if (cur->type == APPEND)
		{
			data->out_files[idx] = strdup(cur->next->str);
			data->modes[idx] = O_CREAT | O_WRONLY | O_APPEND;
		}
		else if (cur->type == PIPE)
		{
			data->cmds[idx] = argv;
			argv = NULL;
			argc = 0;
			idx++;
		}
		cur = cur->next;
	}
	data->cmds[idx] = argv;
	return (1);
}

// LA JE NAVIGUE DANS TES TOKENS ET J'EXECUTE
int	handle_pipex_tokens(t_pipex *data, char **envp)
{
	int		i;
	pid_t	pid;
	int		k;
	char	*path;

	// JE CREE LE NOMBRES PIPES QU'IL FAUT
	if (!creat_pipe(data))
		return (0);
	i = 0;
	while (i < data->nb_cmds)
	{
		// SI C'EST UN HERE_DOC JE LANCE MA FONCTION HERE_DOC// LA FONCTION here_doc n'ext pas prete
		if (data->here_doc[i])
			data->inputfd = here_doc_input(data->in_files[i]);
		// SINON J'OUVRE L'OUTFILE
		else if (data->in_files[i])
			data->inputfd = open(data->in_files[i], data->modes[i], 0644);
		else if (i > 0)
			data->inputfd = data->pipes[(i - 1) * 2];
		else
			data->inputfd = STDIN_FILENO;
		if (i == data->nb_cmds - 1)
		{
			if (data->out_files[i])
				data->outputfd = open(data->out_files[i], data->modes[i], 0644);
			else
				data->outputfd = STDOUT_FILENO;
		}
		else
			data->outputfd = data->pipes[i * 2 + 1];
		// JE CREE LES PROCESSUS ENFANTS
		pid = fork();
		if (pid == 0)
		{
			// FERMETURE DES PIPES NON NECESSAIRE 
			k = 0;
			while (k < (data->nb_cmds - 1) * 2)
			{
				if (k != (i - 1) * 2 && k != i * 2 + 1)
					close(data->pipes[k]);
				k++;
			}
			// CHANGEMENT D'ENTREE ET SORTIT
			dup2(data->inputfd, 0); // IL VA LIRE A PARTIR DE MON INPUT
			dup2(data->outputfd, 1); // LA SORTIE SERA STOCKER DANS L'OUTPUT
			path = command_loc(envp, data->cmds[i][0]); // JE CHERCHE LA COMMANDE POUR POUVOIR L'EXECUTER
			// J'EXECUTE
			execve(path, data->cmds[i], envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		// J'AI FINIS JE FERME LES PIPES QUE J'AI UTILISER
		data->pids[i] = pid;
		if (i > 0)
			close(data->pipes[(i - 1) * 2]);
		if (i < data->nb_cmds - 1)
			close(data->pipes[i * 2 + 1]);
		i++;
	}
	free_close_pipes(data);
	return (1);
}

int	creat_pipe(t_pipex *data)
{
	int	i;

	i = 0;
	data->pipes = malloc(sizeof(int) * (data->nb_cmds - 1) * 2);
	data->pids = malloc(sizeof(pid_t) * data->nb_cmds);
	if (!data->pipes || !data->pids)
		return (0);
	while (i < data->nb_cmds - 1)
	{
		if (pipe(&data->pipes[i * 2]) < 0)
			return (perror("pipe"), 0);
		i++;
	}
	return (1);
}

int	here_doc_input(char *limiter)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) < 0)
		perror("pipe"), exit(EXIT_FAILURE);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || !ft_strncmp(line, limiter, ft_strlen(limiter)))
			break ;
		write(fds[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fds[1]);
	return (fds[0]);
}

char	*command_loc(char **envp, char *cmd)
{
	int		i;
	char	**paths;
	char	*full;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	for (i = 0; paths[i]; i++)
	{
		full = ft_strjoin(paths[i], "/");
		full = ft_strjoin(full, cmd);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
	}
	return (NULL);
}

void	free_close_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < (data->nb_cmds - 1) * 2)
		close(data->pipes[i++]);
	i = 0;
	while (i < data->nb_cmds)
		waitpid(data->pids[i++], NULL, 0);
}

void	free_pipex(t_pipex *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_cmds)
	{
		j = 0;
		while (data->cmds[i][j])
		{
			free(data->cmds[i][j]);
			j++;
		}
		free(data->cmds[i]);
		free(data->in_files[i]);
		free(data->out_files[i]);
		i++;
	}
	free(data->cmds);
	free(data->in_files);
	free(data->out_files);
	free(data->modes);
	free(data->here_doc);
	free(data->pipes);
	free(data->pids);
}

void	free_token(t_struct *token)
{
	t_struct	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->str);
		free(tmp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	*data;
	t_struct	*tmp;
	
	(void)argv;
	if (!cpy_env(data, envp))
		return (ft_putstr_fd("Error: copy of env failed\n", 2), 0);
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
				while (tmp)
				{
					printf("{%d -> '%s'}\n", tmp->type, tmp->str);
					tmp = tmp->next;
				}
			}
			// LA SI C'EST UN BUILTINS J'EXECUTE LES BUILTINS 
			if (is_builtin(data->str))
			{
				// C'EST PAS PRES POUR L'INSTANT
				return (exec_builtin(data, NULL));
			}
			// SINON JE FAIS UNE EXECUTION NORMAL
			else
			{
				// C'EST PAS ENCORE PRES 
				if (build_from_tokens(NULL, NULL))
					handle_pipex_tokens(NULL, NULL);
				
			}
		}
		free(data->str);
	}
	free(data);
	return (0);
}


