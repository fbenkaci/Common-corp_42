/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:59:57 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/22 16:48:58 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	initialize_philo(t_philo *philo, t_rules *rules, int id)
{
	philo->id = id;
	philo->last_meal = get_current_time();
	philo->meal_count = 0;
	philo->has_left = 0;
	philo->has_right = 0;
	philo->state = is_thinking;
	philo->rules = rules;
}

int	initialize_rules(t_rules *rules, int ac, char **av)
{
	rules->nb_of_philos = ft_atoi(av[1]);
	rules->nb_forks = rules->nb_of_philos;
	rules->time_to_die = ft_atoi(av[2]);
	rules->time_to_eat = ft_atoi(av[3]);
	rules->time_to_sleep = ft_atoi(av[4]);
	rules->start_time = get_current_time();
	rules->someone_died = 0;
	if (ac == 6)
	{
		rules->nb_meals_required = ft_atoi(av[5]);
		if (rules->nb_meals_required == 0)
		{
			write(2, "Error\nThe philosophers need at least one meal.\n", 48);
			return (1);
		}
	}
	else
		rules->nb_meals_required = -1;
	rules->head_philo = NULL;
	return (0);
}

int	create_threads(t_rules *rules, t_philo *philo)
{
	int	i;

	i = 0;
	rules->thread = malloc(rules->nb_of_philos * sizeof(pthread_t));
	if (!rules->thread)
		return (1);
	while (i < rules->nb_of_philos)
	{
		if (pthread_create(&rules->thread[i], NULL, &routine, &philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	create_nb_of_philos(t_rules *rules, t_philo **philos)
{
	int	i;

	i = 0;
	*philos = malloc(rules->nb_of_philos * sizeof(t_philo));
	if (!*philos)
		return (1);
	while (i < rules->nb_of_philos)
	{
		initialize_philo((*philos) + i, rules, i + 1);
		i++;
	}
	return (0);
}

int	check_all_philos_alive(t_philo *philo)
{
	long long	died_time;
	long long	current_time;
	int			i;

	i = 0;
	while (i < philo->rules->nb_of_philos)
	{
		pthread_mutex_lock(&philo[i].mutex_last_meal);
		current_time = get_current_time();
		died_time = (philo[i].last_meal + philo->rules->time_to_die);
		pthread_mutex_unlock(&philo[i].mutex_last_meal);
		if (current_time >= died_time)
		{
			pthread_mutex_lock(&philo->rules->someone_died_mutex);
			if (!philo->rules->someone_died)
				notify_death(philo, i);
			pthread_mutex_unlock(&philo->rules->someone_died_mutex);
			return (0);
		}
		i++;
	}
	return (1);
}
