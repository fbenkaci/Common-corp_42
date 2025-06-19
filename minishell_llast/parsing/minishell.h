/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:54:23 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/18 16:27:10 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef enum e_token
{
	NONE = -1,
	S_QUOTE,
	D_QUOTE,
	PIPE,
	WORD,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	PARENTHESIS,
	SPACES,
	WORD_D_QUOTES,
	WORD_S_QUOTES,
}					t_token;

typedef struct s_cmd
{
	char **argv;   // liste des arguments (avec la commande)
	char *infile;  // nom du fichier en entrée
	char *outfile; // nom du fichier en sortie
	int append;    // 1 si >>, 0 si >
	int heredoc;   // 1 si "<<"
	char			*heredoc_delim;
	int				heredoc_fd;
	// pour stocker le delimeut du heredoc (EOF par exemple)
	// int **pipes;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_exec
{
	int				pids;
	int (*pipes)[2];
	int nb_cmds; // Je vais l'utiliser pour creer le nombre de pipe necessaire
	char			*path;
	int				last_status;
	t_cmd			*cmds;
}					t_exec;

typedef struct s_struct
{
	t_token			type;
	char			*str;
	// int				prev;
	char			**env;
	t_exec          *exec;
	struct s_struct	*next;
}					t_struct;


/*-------------------- EXPAND_HEREDOC -----------------*/
typedef struct s_expand_data
{
	char			*result;
	int				result_len;
	int				j;
}					t_expand_data;

char				*expand_variables_heredoc(t_struct **data, char *line);
char				*get_env_value_3(char *var_name);
char				*init_result_buffer(int line_len);
int					resize_buffer_if_needed(t_expand_data *data);

/*-------------------- EXPAND -----------------*/
void				handle_sigint(int sig);

/*-------------------- EXPAND -----------------*/

int					expand_variable(t_struct **cur, char *str, char **envp);
char				*replace_variable(char *str, int dollar_pos, char *var_name,
						char *var_value);
char				*extract_var_name(char *str, int start);
char				*get_env_value_2(char *var_name, char **envp);

/*-------------------- EXECUTION -----------------*/
int					execution(t_cmd *cmd, t_exec *exec, t_struct **data);
int					open_all_heredocs(t_exec *exec, t_struct **data, t_cmd *cmd);
int					execute_single_builtin(t_exec *exec, t_cmd *cmd, t_struct **data);
void				setup_redirections(t_cmd *cmd);
void				setup_pipe_redirections(t_exec *exec, int index,
						t_cmd *cmd);
void				run_command(t_struct **data, t_exec *exec, t_cmd *cmd);
void				close_pipes_and_wait(t_exec *exec);
int					fork_and_execute_commands(t_struct **data, t_exec *exec,
						t_cmd *cmd);
void				handle_cmd_error(char *cmd);

void				free_all_cmd(t_cmd *cmd);

int					command_loc(t_struct *data, t_exec *exec, char *cmd);

t_cmd				*create_cmd_from_tokens(t_struct **cur, char **env, t_exec *exec);
int					handle_in(t_struct **cur, t_cmd *cmd);
int					handle_out_and_in(t_struct **cur, t_cmd *cmd);
int					handle_word_and_append(t_struct **cur, t_cmd *cmd, int *i,
						char **envp);

int					create_pipe(t_exec *data);
int					caculate_nb_cmd(t_exec *data, t_cmd *cmd);
int					ft_lstsize_bis(t_cmd *cmd);
void				close_unused_pipes(t_exec *data, int index);
void				close_pipes(t_exec *data, int index, int i, int j);
int					heredoc_input(t_struct **data, char *delimiter);

/*--------------------utils-----------------*/
// int					ft_strlen(char *str);
// int					ft_strcmp(const char *s1, const char *s2);
// char				**ft_split(const char *s, char c);
// char				*ft_strchr(char *str, int n);
// char				*ft_strdup(char *src);
// size_t				ft_strcpy(char *dst, char *src);
size_t				ft_strcat(char *dst, char *src);
// size_t				ft_strlcpy(char *dst, char *src, size_t size);

/*------------------parsing-----------------*/

int					parsing(t_struct *data);
void				is_token(t_struct *data);
int					identify_special_token(t_struct *data, int i);
int					identify_redirection(t_struct *data, int i);

/*--------------parsing pipe----------------*/

int					utils_parse_pipe(t_struct *data, int i, int *found_pipe);
int					parse_error_pipe(t_struct *data);

/*--------------parsing redir----------------*/

int					parse_redir(t_struct *data);
int					utils_parse_redir(t_struct *data, int i, int *found_redir);
int					handle_redir(t_struct *data, int i, int *found_redir);

/*---------------parsing quote---------------*/

int					parsing_quote(t_struct *data);

/*--------------------path------------------*/

char				*find_path(char *cmd, char **paths);
void				free_paths(char **paths);

/*---------------special tokens-------------*/

void				free_token_list(t_struct *start);
t_struct			*create_token(const char *str, int len, t_token type);
int					token_init(t_struct *data);
void				tokenize_string(t_struct *data, int i);
void				token_append(t_struct *data);

/*-----------------handle------------------*/

void				handle_space_token(char *s, int *i, t_struct **cur);
void				handle_word_token(char *s, int *i, t_struct **cur);
void				handle_special_tokens(char *s, int *i, t_struct **cur);
void				append_and_advance(t_struct **cur, t_struct *new);
void				handle_redir_token(char *s, int *i, t_struct **cur);
void				handle_quotes(char *s, int *i, t_struct **cur);
/*-----------------word quote------------------*/

void				word_quote(t_struct *data, int *i, t_struct **cur);
void				handle_word_d_quotes(t_struct *data, int *i,
						t_struct **cur);
void				handle_word_s_quotes(t_struct *data, int *i,
						t_struct **cur);

/*-----------------fusion token------------------*/

void				echo_fusion(t_struct *data);

# include "../builtins/builtins.h"

#endif