/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:59:01 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/12 15:44:15 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_status = 130;
	write(1, "\n", 1);
	rl_on_new_line(); // Indique à readline qu'on passe à une nouvelle ligne.
	rl_replace_line("", 1); // Efface la ligne actuellement tapée par l'utilisateur
	rl_redisplay(); // Redisplay = réaffiche le prompt proprement avec la ligne vide
}

// ctr+\ il faut le faire dans les child, la sortie sera Quit (core dumped)
void	handle_sigint_exec(int sig)
{
	(void)sig;
	write(1, "\n", 1);
    g_signal_status = 130;
}
