/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:09:24 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/22 17:42:35 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	can_eat(t_philo *philo)
{
	long long	stop_eating;

	if (!update_eating_state(philo, &stop_eating))
		return (0);
	if (!print_eating_message(philo))
		return (0);
	if (!wait_and_finish_eating(philo, stop_eating))
		return (0);
	return (1);
}

int	take_forks(t_philo *philo)
{
	int	nb_of_philos;
	int	fork_right;
	int	fork_left;

	if (!check_someone_died(philo))
		return (0);
	nb_of_philos = philo->rules->nb_of_philos;
	fork_right = (philo->id + nb_of_philos - 1) % nb_of_philos;
	fork_left = (philo->id + nb_of_philos - 2) % nb_of_philos;
	if (philo->id % 2 == 0)
	{
		if (!take_even_forks(philo, fork_right, fork_left))
			return (0);
	}
	else
	{
		if (!take_odd_forks(philo, fork_right, fork_left))
			return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(1000);
	while (1)
	{
		if (!check_someone_died(philo))
		{
			if (philo->has_left || philo->has_right)
				release_forks(philo);
			return (NULL);
		}
		if (!take_forks(philo))
		{
			if (philo->has_left || philo->has_right)
				release_forks(philo);
			return (NULL);
		}
		if (!can_eat(philo))
		{
			if (philo->has_left || philo->has_right)
				release_forks(philo);
			return (NULL);
		}
		release_forks(philo);
		if (!check_all_philos_alive(philo->rules->head_philo))
		{
			if (philo->has_left || philo->has_right)
				release_forks(philo);
			return (NULL);
		}
		if (!change_state_to_sleep(philo))
		{
			if (philo->has_left || philo->has_right)
				release_forks(philo);
			return (NULL);
		}
		if (check_can_philo_eat_more(philo) == 0)
			return (NULL);
		change_state_to_thinking(philo);
		usleep(2000);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_rules	*rules;
	t_philo	*philos;
	int		i;

	philos = NULL;
	if (ac == 5 || ac == 6)
	{
		rules = malloc(sizeof(t_rules));
		if (!rules)
			return (1);
		if (initialize_rules(rules, ac, av) != 0)
			return (free(rules->thread), free(rules), 1);
		if (create_nb_of_philos(rules, &philos) != 0)
		{
			write(2, "Error\nCreation of philo failed\n", 32);
			return (free(philos), free(rules->thread), free(rules), 1);
		}
		if (rules->nb_of_philos == 1)
		{
			if (handle_one_philo(rules, philos) == 1)
			{
				free(philos);
				free(rules);
				return (1);
			}
			free(philos);
			free(rules);
			return (0);
		}
		rules->head_philo = philos;
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
	}
	else
		write(2, "Too many or too less args.Please Enter 5 or 4 args.\n", 53);
	return (0);
}
