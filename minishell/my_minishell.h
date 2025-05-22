#ifndef MY_MINSHELL_H
# define MY_MINSHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
// INCLUE LE .h DE WALID POUR FAIRE L'EXEC

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
	INFILE,
	OUTFILE,
}					t_token;

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
	char			**env;
	char			*str;
	struct s_struct	*next;
}					t_struct;

# include "builtins/builtins.h"

#endif