/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:09:24 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/23 20:21:33 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	release_forks(t_philo *philo)
{
	int	nb_of_philos;
	int	fork_right;
	int	fork_left;

	nb_of_philos = philo->rules->nb_of_philos;
	fork_right = (philo->id + nb_of_philos - 1) % nb_of_philos;
	fork_left = (philo->id + nb_of_philos - 2) % nb_of_philos;
	if (philo->has_left)
	{
		pthread_mutex_unlock(&philo->rules->fork_mutex[fork_left]);
		philo->has_left = 0;
	}
	if (philo->has_right)
	{
		pthread_mutex_unlock(&philo->rules->fork_mutex[fork_right]);
		philo->has_right = 0;
	}
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
			return (safe_release_forks(philo), NULL);
		if (!take_forks(philo))
			return (safe_release_forks(philo), NULL);
		if (!can_eat(philo))
			return (safe_release_forks(philo), NULL);
		release_forks(philo);
		if (!check_all_philos_alive(philo->rules->head_philo))
			return (safe_release_forks(philo), NULL);
		if (!change_state_to_sleep(philo))
			return (safe_release_forks(philo), NULL);
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
		return (run_simulation(rules, philos));
	}
	else
		write(2, "Too many or too less args.Please Enter 5 or 4 args.\n", 53);
	return (0);
}
