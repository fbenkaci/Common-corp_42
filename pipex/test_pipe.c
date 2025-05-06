/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:44:32 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/05 19:24:05 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(void)
{
	int fd[3][2];
	int i;

	i = 0;
	while (i < 3)
	{
		if (pipe(fd[i]) < 0)
			return (1);
		i++;
	}
	int pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		int x;
		if (read(fd[0][0], &x, sizeof(int)) < 0)
			return (3);
		x += 5;
		write(fd[1][1], &x, sizeof(int));
		close(fd[0][0]);
		close(fd[1][1]);
		return (0);
	}
	int pid2 = fork();
	if (pid2 < 0)
		return (4);
	if (pid2 == 0)
	{
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		int x;
		if (read(fd[1][0], &x, sizeof(int)) < 0)
			return (5);
		x += 5;
		write(fd[2][1], &x, sizeof(int));
		close(fd[1][0]);
		close(fd[2][1]);
		return (0);
	}
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][1]);
	int x = 0;
	write(fd[0][1], &x, sizeof(int));
	read(fd[2][0], &x, sizeof(int));
    printf("%d\n", x);
    close(fd[0][1]);
    close(fd[2][0]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    return (0);
}
