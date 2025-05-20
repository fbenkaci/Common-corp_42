/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:33:46 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/20 12:33:41 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int ft_unset(char **envp, char **cmd)
// {
//     char *new_env;
//     char *name;
//     int len;
//     int i;

//     len = 0;
//     i = 0;
//     if (!cmd[1])
//         return (1);
//     while (envp[len])
//         len++;
//     new_env = malloc(sizeof(char *) * (len + 1));;
//     if (!new_env)
//         return (0);
//     while (envp[i])
//     {
//         if (ft_strcmp())
//         {

//         }

//         i++;
//     }

//     return (1);
// }


int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	unset_variable(envp, "a=");

	return (0);
}