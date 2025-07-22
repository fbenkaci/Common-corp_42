/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils_6.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:41:31 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/22 17:43:02 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_fork_taken(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->printf_mutex);
	if (!check_someone_died(philo))
	{
		pthread_mutex_unlock(&philo->rules->printf_mutex);
		return (0);
	}
	printf("%lld %d has taken a fork\n", get_current_time()
		- philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->printf_mutex);
	return (1);
}

int	take_even_forks(t_philo *philo, int fork_right, int fork_left)
{
	pthread_mutex_lock(&philo->rules->fork_mutex[fork_right]);
	if (!check_someone_died(philo))
		return (0);
	philo->has_right = 1;
	if (!print_fork_taken(philo))
		return (0);
	pthread_mutex_lock(&philo->rules->fork_mutex[fork_left]);
	if (!check_someone_died(philo))
		return (0);
	philo->has_left = 1;
	if (!print_fork_taken(philo))
		return (0);
	return (1);
}

int	take_odd_forks(t_philo *philo, int fork_right, int fork_left)
{
	pthread_mutex_lock(&philo->rules->fork_mutex[fork_left]);
	philo->has_left = 1;
	if (!check_someone_died(philo))
		return (0);
	if (!print_fork_taken(philo))
		return (0);
	pthread_mutex_lock(&philo->rules->fork_mutex[fork_right]);
	if (!check_someone_died(philo))
		return (0);
	philo->has_right = 1;
	if (!print_fork_taken(philo))
		return (0);
	return (1);
}
