/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:55:52 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/22 16:08:46 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	check_philo_is_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_state);
	if (philo->state == is_thinking)
	{
		pthread_mutex_unlock(&philo->mutex_state);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex_state);
	return (0);
}

int	check_someone_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->someone_died_mutex);
	if (philo->rules->someone_died)
	{
		pthread_mutex_unlock(&philo->rules->someone_died_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->rules->someone_died_mutex);
	return (1);
}

int	check_can_philo_eat_more(t_philo *philo)
{
	if (philo->rules->nb_meals_required == -1)
		return (1);
	pthread_mutex_lock(&philo->mutex_meal_count);
	if (philo->meal_count < philo->rules->nb_meals_required)
	{
		pthread_mutex_unlock(&philo->mutex_meal_count);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex_meal_count);
	return (0);
}
