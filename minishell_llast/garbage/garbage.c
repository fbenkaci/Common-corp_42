/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:27:22 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/19 16:38:33 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void free_garbage(t_garbage *gar)
{
    if (gar->cmd)
        free_all_cmd(gar->cmd);
    if (gar->data)
    {
        free_tokens(gar->data);
        free(gar->data);
    }
    if (gar->exec)
    {
        
        free(gar->exec);
    }
}
