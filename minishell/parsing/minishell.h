/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 01:13:09 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/13 01:13:10 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
}					t_token;

typedef struct s_struct
{
	t_token			type;
	char			*str;
	struct s_struct	*next;
	char			**env;
	char			**paths;

}					t_struct;

/*--------------------utils-----------------*/
int					ft_strlen(char *str);
int					ft_strcmp(const char *s1, const char *s2);
char				**ft_split(const char *s, char c);
char				*ft_strchr(char *str, int n);
char				*ft_strdup(char *src);
size_t				ft_strcpy(char *dst, char *src);
size_t				ft_strcat(char *dst, char *src);

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

/*--------------------path------------------*/
char				*find_path(char *cmd, char **paths);
void				free_paths(char **paths);

/*---------------special tokens-------------*/
void				token_append(t_struct *data);

#endif