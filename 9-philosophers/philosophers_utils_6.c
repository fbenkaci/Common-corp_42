/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils_6.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:41:31 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/23 19:41:58 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	lock_left_fork_even(t_philo *philo, int fork_right, int fork_left)
{
	pthread_mutex_lock(&philo->rules->fork_mutex[fork_left]);
	philo->has_left = 1;
	if (!check_someone_died(philo))
	{
		pthread_mutex_unlock(&philo->rules->fork_mutex[fork_left]);
		pthread_mutex_unlock(&philo->rules->fork_mutex[fork_right]);
		philo->has_left = 0;
		philo->has_right = 0;
		return (0);
	}
	if (!print_fork_taken(philo))
	{
		pthread_mutex_unlock(&philo->rules->fork_mutex[fork_left]);
		pthread_mutex_unlock(&philo->rules->fork_mutex[fork_right]);
		philo->has_left = 0;
		philo->has_right = 0;
		return (0);
	}
	return (1);
}

int	take_even_forks(t_philo *philo, int fork_right, int fork_left)
{
	if (!lock_right_fork_even(philo, fork_right))
		return (0);
	if (!lock_left_fork_even(philo, fork_right, fork_left))
		return (0);
	return (1);
}

int	lock_left_fork_odd(t_philo *philo, int fork_left)
{
	pthread_mutex_lock(&philo->rules->fork_mutex[fork_left]);
	philo->has_left = 1;
	if (!check_someone_died(philo))
	{
		pthread_mutex_unlock(&philo->rules->fork_mutex[fork_left]);
		philo->has_left = 0;
		return (0);
	}
	if (!print_fork_taken(philo))
	{
		pthread_mutex_unlock(&philo->rules->fork_mutex[fork_left]);
		philo->has_left = 0;
		return (0);
	}
	return (1);
}

int	lock_right_fork_odd(t_philo *philo, int fork_right, int fork_left)
{
	pthread_mutex_lock(&philo->rules->fork_mutex[fork_right]);
	philo->has_right = 1;
	if (!check_someone_died(philo))
	{
		pthread_mutex_unlock(&philo->rules->fork_mutex[fork_right]);
		pthread_mutex_unlock(&philo->rules->fork_mutex[fork_left]);
		philo->has_right = 0;
		philo->has_left = 0;
		return (0);
	}
	if (!print_fork_taken(philo))
	{
		pthread_mutex_unlock(&philo->rules->fork_mutex[fork_right]);
		pthread_mutex_unlock(&philo->rules->fork_mutex[fork_left]);
		philo->has_right = 0;
		philo->has_left = 0;
		return (0);
	}
	return (1);
}

int	take_odd_forks(t_philo *philo, int fork_right, int fork_left)
{
	if (!lock_left_fork_odd(philo, fork_left))
		return (0);
	if (!lock_right_fork_odd(philo, fork_right, fork_left))
		return (0);
	return (1);
}
