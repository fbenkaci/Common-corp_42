/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:44:19 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/22 16:17:27 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_printf("%s\n", cwd);
		free(cwd);
	}
	else
		perror("getcwd");
}
