/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:53:14 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/23 19:53:57 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	handle_one_philo(t_rules *rules, t_philo *philos)
{
	long long	current_time;

	rules->start_time = get_current_time();
	rules->fork_mutex = malloc(sizeof(pthread_mutex_t) * rules->nb_of_philos);
	if (!rules->fork_mutex)
		return (1);
	pthread_mutex_init(&rules->fork_mutex[0], NULL);
	pthread_mutex_lock(&rules->fork_mutex[0]);
	printf("%lld %d has taken a fork\n", get_current_time() - rules->start_time,
		philos->id);
	usleep(philos->rules->time_to_die * 1000);
	current_time = get_current_time() - rules->start_time;
	printf("%lld %d died\n", current_time, philos->id);
	pthread_mutex_unlock(&rules->fork_mutex[0]);
	pthread_mutex_destroy(&rules->fork_mutex[0]);
	free(rules->fork_mutex);
	return (0);
}

int	init_mutex(t_philo *philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_of_philos)
	{
		if (pthread_mutex_init(&philo[i].mutex_state, NULL) != 0
			|| pthread_mutex_init(&philo[i].mutex_meal_count, NULL) != 0
			|| pthread_mutex_init(&philo[i].mutex_last_meal, NULL) != 0)
			return (1);
		i++;
	}
	rules->fork_mutex = malloc(sizeof(pthread_mutex_t) * rules->nb_of_philos);
	if (!rules->fork_mutex)
		return (1);
	i = 0;
	while (i < rules->nb_of_philos)
	{
		pthread_mutex_init(&rules->fork_mutex[i], NULL);
		i++;
	}
	if (pthread_mutex_init(&rules->printf_mutex, NULL) != 0
		|| pthread_mutex_init(&rules->someone_died_mutex, NULL) != 0)
		return (1);
	return (0);
}

void	destroy_mutex(t_philo *philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_of_philos)
	{
		pthread_mutex_destroy(&philo[i].mutex_state);
		pthread_mutex_destroy(&philo[i].mutex_meal_count);
		pthread_mutex_destroy(&philo[i].mutex_last_meal);
		i++;
	}
	i = 0;
	while (i < rules->nb_of_philos)
	{
		pthread_mutex_destroy(&rules->fork_mutex[i]);
		i++;
	}
	if (rules->fork_mutex)
	{
		free(rules->fork_mutex);
		rules->fork_mutex = NULL;
	}
	pthread_mutex_destroy(&rules->printf_mutex);
	pthread_mutex_destroy(&rules->someone_died_mutex);
}

long long	get_current_time(void)
{
	struct timeval	current_time;
	long long		start_time;

	gettimeofday(&current_time, NULL);
	start_time = (long long)current_time.tv_sec * 1000
		+ (long long)current_time.tv_usec / 1000;
	return (start_time);
}
