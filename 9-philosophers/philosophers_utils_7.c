/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils_7.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:54:40 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/23 20:21:21 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	safe_release_forks(t_philo *philo)
{
	if (philo->has_left || philo->has_right)
		release_forks(philo);
}

int	init_mutex_and_thread(t_philo *philos, t_rules *rules)
{
	if (init_mutex(philos, rules) != 0)
	{
		write(2, "Error\nMutex initialisation failed\n", 35);
		free(philos);
		free(rules->thread);
		free(rules);
		return (1);
	}
	if (create_threads(rules, philos) != 0)
	{
		write(2, "Error\nCreation of thread failed\n", 33);
		destroy_mutex(philos, rules);
		free(philos);
		free(rules->thread);
		free(rules);
		return (1);
	}
	return (0);
}

int	join_and_cleanup(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->nb_of_philos)
	{
		if (pthread_join(rules->thread[i], NULL) != 0)
			return (1);
		i++;
	}
	destroy_mutex(philos, rules);
	free(rules->thread);
	free(rules);
	free(philos);
	return (0);
}

int	run_simulation(t_rules *rules, t_philo *philos)
{
	if (rules->nb_of_philos == 1)
	{
		if (handle_one_philo(rules, philos) == 1)
			return (free(philos), free(rules), 1);
		free(philos);
		free(rules);
		return (0);
	}
	rules->head_philo = philos;
	if (init_mutex_and_thread(philos, rules) == 1)
		return (1);
	if (join_and_cleanup(rules, philos) == 1)
		return (1);
	return (0);
}
