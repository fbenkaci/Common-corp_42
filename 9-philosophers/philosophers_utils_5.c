/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils_5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:23:53 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/22 17:25:06 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	update_eating_state(t_philo *philo, long long *stop_eating)
{
	long long	start_eating;

	if (!check_someone_died(philo))
		return (0);
	start_eating = get_current_time();
	*stop_eating = start_eating + philo->rules->time_to_eat;
	if (philo->rules->nb_meals_required != -1)
	{
		pthread_mutex_lock(&philo->mutex_meal_count);
		philo->meal_count++;
		pthread_mutex_unlock(&philo->mutex_meal_count);
	}
	pthread_mutex_lock(&philo->mutex_state);
	philo->state = is_eating;
	pthread_mutex_unlock(&philo->mutex_state);
	return (1);
}

int	print_eating_message(t_philo *philo)
{
	if (!check_someone_died(philo))
		return (0);
	pthread_mutex_lock(&philo->rules->printf_mutex);
	if (!check_someone_died(philo))
	{
		pthread_mutex_unlock(&philo->rules->printf_mutex);
		return (0);
	}
	printf("%lld %d is eating\n", get_current_time() - philo->rules->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->rules->printf_mutex);
	return (1);
}

int	wait_and_finish_eating(t_philo *philo, long long stop_eating)
{
	while (get_current_time() < stop_eating)
	{
		if (!check_all_philos_alive(philo->rules->head_philo))
		{
			release_forks(philo);
			return (0);
		}
		usleep(1000);
	}
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	return (1);
}
