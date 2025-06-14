/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:18:51 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/08 12:18:52 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "../parsing/minishell.h"

/*------------------builtin-----------------*/

int		ft_export(t_struct *data, char **cmd);
int		ft_unset(t_struct *data, char **cmd);
int		ft_env(t_struct *data, char **cmd);
int		ft_cd(t_struct *data, char **cmd);
int		ft_echo(char **cmd);
int		ft_exit(char **cmd);
void	ft_pwd(void);

int		exec_builtin(t_struct *data, char **cmd);
int		is_builtin(char *cmd);

int		add_or_replace_env_var(t_struct *data, char *cmd);
int		add_in_env(t_struct *data, char *cmd);
int		cpy_env(t_struct *data, char **envp);

char	*update_env(t_struct *data, char *var, char *new_val_var);
int		update_pwd_vars(t_struct *data, char *oldpwd);
int		cd_path(t_struct *data, const char *path);
void	free_all(char *new_pwd, char *oldpwd, char *env_old, char *env_new);

#endif