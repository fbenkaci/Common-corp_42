/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:25:55 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/13 19:33:14 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int				mails = 0;
pthread_mutex_t	mutex;

void	*say_hello(void)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&mutex);
	while (i < 10000000)
	{
		mails++;
		i++;
	}
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t thread, thread_2;
	pthread_mutex_init(&mutex, NULL);
	// Crée un thread qui exécute la fonction say_hello
	pthread_create(&thread, NULL, say_hello, NULL);
	pthread_create(&thread_2, NULL, say_hello, NULL);
	// On attend que le thread se termine
	pthread_join(thread, NULL);
	pthread_join(thread_2, NULL);
	printf("Number of mail: %d\n", mails);
	pthread_mutex_destroy(&mutex);
	return (0);
}

// #include <stdio.h>
// #include <sys/time.h>
// #include <unistd.h> // pour usleep()

// // Fonction qui retourne le temps actuel en millisecondes
// long long	get_time_in_ms(void)
// {
// 	struct timeval	time;

// 	gettimeofday(&time, NULL);
// 	return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000));
// }

// int	main(void)
// {
// 	long long	start;
// 	long long	end;

// 	start = get_time_in_ms(); // temps avant l'attente
// 	usleep(500000);           // pause de 500000 microsecondes = 0.5 seconde
// 	end = get_time_in_ms();   // temps après l'attente
// 	printf("usleep a duré environ %lld ms\n", end - start);
// 	return (0);
// }
