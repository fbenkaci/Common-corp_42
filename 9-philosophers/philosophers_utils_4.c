/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils_4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:10:36 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/22 17:11:55 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	change_state_to_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->someone_died_mutex);
	if (philo->rules->someone_died)
	{
		pthread_mutex_unlock(&philo->rules->someone_died_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->rules->someone_died_mutex);
	pthread_mutex_lock(&philo->mutex_state);
	philo->state = is_thinking;
	pthread_mutex_unlock(&philo->mutex_state);
	if (!check_someone_died(philo))
		return (0);
	pthread_mutex_lock(&philo->rules->printf_mutex);
	if (!check_someone_died(philo))
	{
		pthread_mutex_unlock(&philo->rules->printf_mutex);
		return (0);
	}
	printf("%lld %d is thinking\n", get_current_time()
		- philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->printf_mutex);
	if (!check_someone_died(philo))
		return (0);
	return (1);
}

void	notify_death(t_philo *philo, int i)
{
	philo->rules->someone_died = 1;
	pthread_mutex_lock(&philo[i].mutex_state);
	philo[i].state = is_died;
	pthread_mutex_unlock(&philo[i].mutex_state);
	pthread_mutex_lock(&philo->rules->printf_mutex);
	printf("%lld %d died\n", get_current_time() - philo->rules->start_time,
		philo[i].id);
	pthread_mutex_unlock(&philo->rules->printf_mutex);
}

int	check_and_set_sleep_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->someone_died_mutex);
	if (philo->rules->someone_died)
	{
		pthread_mutex_unlock(&philo->rules->someone_died_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->rules->someone_died_mutex);
	pthread_mutex_lock(&philo->mutex_state);
	philo->state = is_sleeping;
	pthread_mutex_unlock(&philo->mutex_state);
	return (1);
}

int	print_sleeping_state(t_philo *philo)
{
	if (!check_someone_died(philo))
		return (0);
	pthread_mutex_lock(&philo->rules->printf_mutex);
	if (!check_someone_died(philo))
	{
		pthread_mutex_unlock(&philo->rules->printf_mutex);
		return (0);
	}
	printf("%lld %d is sleeping\n", get_current_time()
		- philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->printf_mutex);
	return (1);
}

int	change_state_to_sleep(t_philo *philo)
{
	long long	final_time;
	long long	start_time;

	if (!check_and_set_sleep_state(philo))
		return (0);
	start_time = get_current_time();
	final_time = philo->rules->time_to_sleep + start_time;
	if (!print_sleeping_state(philo))
		return (0);
	if (!check_someone_died(philo))
		return (0);
	while (get_current_time() < final_time)
	{
		pthread_mutex_lock(&philo->rules->someone_died_mutex);
		if (philo->rules->someone_died)
		{
			pthread_mutex_unlock(&philo->rules->someone_died_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->rules->someone_died_mutex);
		if (check_all_philos_alive(philo->rules->head_philo) == 0)
			return (0);
		usleep(1000);
	}
	return (1);
}
