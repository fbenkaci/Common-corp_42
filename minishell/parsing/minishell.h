#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
// #include "../pipex/pipex.h"

/* types de tokens */
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
	SPACES
}					t_token;

/* liste chaînée de tokens */
typedef struct s_pipex
{
	int				nb_cmds;
	char			***cmds;
	char			**in_files;
	char			**out_files;
	int				*modes;
	int				*here_doc;
	int				*pipes;
	pid_t			*pids;
	int				inputfd;
	int				outputfd;
}					t_pipex;

typedef struct s_struct
{
	t_token			type;
	char			*str;
	struct s_struct	*next;
	char			**env;
	char			**paths;
}					t_struct;

/*------------------builtin-----------------*/
void				ft_env(t_struct *data, char **cmd);
int					ft_echo(char **cmd);
void				ft_pwd(void);
int					ft_cd(t_struct *data, char **cmd);
int					ft_exit(char **cmd);
int					ft_unset(t_struct *data, char *var_name);
int					ft_export(t_struct *data, char **cmd);

// int					exec_builtin(char **cmd, t_pipex *data);
int					is_builtin(char *cmd);

int					add_or_replace_env_var(t_struct *data, char *cmd);
int					add_in_env(t_struct *data, char *cmd);
int					cpy_env(t_struct *data, char **envp);

char				*update_env(t_struct *data, char *var, char *new_val_var);
int					update_pwd_vars(t_struct *data, char *oldpwd);
int					cd_path(t_struct *data, const char *path);

void				free_all(char *new_pwd, char *oldpwd, char *env_old,
						char *env_new);

/*------------------parsing-----------------*/

void				parsing(t_struct *data);
void				is_token(t_struct *data);

/*--------------parsing pipe----------------*/

int					utils_parse_pipe(t_struct *data, int i, int *found_pipe);
void				parse_error_pipe(t_struct *data);

/*--------------parsing redir----------------*/

void				parse_redir(t_struct *data);
int					utils_parse_redir(t_struct *data, int i, int *found_redir);
int					handle_redir(t_struct *data, int i, int *found_redir);

/*---------------parsing quote---------------*/

void				parsing_quote(t_struct *data);

/*---------------special tokens-------------*/
void				token_append(t_struct *data);
/* parsing principal : renvoie tête de liste de tokens */

void				free_tokens(t_struct *tokens);
void				free_paths(char **paths);

/* utilitaires */
char				**ft_split(const char *s, char c);
size_t				ft_strlen(const char *s);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strdup(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

int					build_from_tokens(t_pipex *data, t_struct *tok);
int					handle_pipex_tokens(t_pipex *data, char **envp);
int					creat_pipe(t_pipex *data);
int					here_doc_input(char *limiter);
char				*command_loc(char **envp, char *cmd);
void				free_close_pipes(t_pipex *data);
void				free_pipex(t_pipex *data);
#endif // MINISHELL_H