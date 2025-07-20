/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:09:24 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/20 20:22:17 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		release_forks(t_philo *philo);

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

int	check_all_philos_alive(t_philo *philo)
{
	long long	died_time;
	long long current_time;
	int			i;

	i = 0;
	// Je met un mutex car un autre thread peut etre entrain de modifier l'etat d'un philo et donc lire une valeur pas bonne
	while (i < philo->rules->nb_of_philos)
	{
		pthread_mutex_lock(&philo[i].mutex_last_meal);
		current_time = get_current_time();
		died_time = philo[i].last_meal + philo->rules->time_to_die;
		pthread_mutex_unlock(&philo[i].mutex_last_meal);
		if (current_time >= died_time)
		{
			pthread_mutex_lock(&philo->rules->someone_died_mutex);
			if (!philo->rules->someone_died)
			{
				philo->rules->someone_died = 1;
				pthread_mutex_lock(&philo[i].mutex_state);
				philo[i].state = is_died;
				pthread_mutex_unlock(&philo[i].mutex_state);
				pthread_mutex_lock(&philo->rules->printf_mutex);
				printf("%lld %d died\n", died_time, philo[i].id);
				pthread_mutex_unlock(&philo->rules->printf_mutex);
			}
			pthread_mutex_unlock(&philo->rules->someone_died_mutex);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_can_philo_eat_more(t_philo *philo)
{
	if (philo->rules->nb_meals_required == -1)
		// il n'y a que 5 argument pas nb_max de repas
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

int	can_eat(t_philo *philo)
{
	long long	start_eating;
	long long	stop_eating;

	if (!check_someone_died(philo))
		return (0);
	start_eating = get_current_time();
	stop_eating = start_eating + philo->rules->time_to_eat;
	if (philo->rules->nb_meals_required != -1)
	{
		pthread_mutex_lock(&philo->mutex_meal_count);
		philo->meal_count++;
		pthread_mutex_unlock(&philo->mutex_meal_count);
	}
	pthread_mutex_lock(&philo->mutex_state);
	philo->state = is_eating;
	pthread_mutex_unlock(&philo->mutex_state);
	if (!check_someone_died(philo))
		return (0);
	pthread_mutex_lock(&philo->rules->printf_mutex);
	if (!check_someone_died(philo))
	{
		pthread_mutex_unlock(&philo->rules->printf_mutex);
		return (0);
	}
	printf("%lld %d is eating\n", get_current_time(), philo->id);
	pthread_mutex_unlock(&philo->rules->printf_mutex);
	while (get_current_time() < stop_eating)
	{
		// if (!check_someone_died(philo))
		// 	return (0);
		if (!check_all_philos_alive(philo->rules->head_philo))
		{
			// printf("ok can eat\n");
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
		pthread_mutex_lock(&philo->rules->fork_mutex[fork_right]);
		if (!check_someone_died(philo))
			return (0);
		philo->has_right = 1;
		pthread_mutex_lock(&philo->rules->printf_mutex);
		if (!check_someone_died(philo))
		{
			pthread_mutex_unlock(&philo->rules->printf_mutex);
			return (0);
		}
		printf("%lld %d has taken a fork\n", get_current_time(), philo->id);
		pthread_mutex_unlock(&philo->rules->printf_mutex);
		pthread_mutex_lock(&philo->rules->fork_mutex[fork_left]);
		if (!check_someone_died(philo))
			return (0);
		philo->has_left = 1;
		pthread_mutex_lock(&philo->rules->printf_mutex);
		if (!check_someone_died(philo))
		{
			pthread_mutex_unlock(&philo->rules->printf_mutex);
			return (0);
		}
		printf("%lld %d has taken a fork\n", get_current_time(), philo->id);
		pthread_mutex_unlock(&philo->rules->printf_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->rules->fork_mutex[fork_left]);
		philo->has_left = 1;
		if (!check_someone_died(philo))
			return (0);
		pthread_mutex_lock(&philo->rules->printf_mutex);
		if (!check_someone_died(philo))
		{
			pthread_mutex_unlock(&philo->rules->printf_mutex);
			return (0);
		}
		printf("%lld %d has taken a fork\n", get_current_time(), philo->id);
		pthread_mutex_unlock(&philo->rules->printf_mutex);
		pthread_mutex_lock(&philo->rules->fork_mutex[fork_right]);
		if (!check_someone_died(philo))
			return (0);
		philo->has_right = 1;
		pthread_mutex_lock(&philo->rules->printf_mutex);
		if (!check_someone_died(philo))
		{
			pthread_mutex_unlock(&philo->rules->printf_mutex);
			return (0);
		}
		printf("%lld %d has taken a fork\n", get_current_time(), philo->id);
		pthread_mutex_unlock(&philo->rules->printf_mutex);
	}
	// if (!check_someone_died(philo))
	// 	return (0);
	return (1);
}

long long	get_current_time(void)
{
	struct timeval	current_time;
	long long		start_time;

	gettimeofday(&current_time, NULL);
	start_time = (long long)current_time.tv_sec * 1000
		+ (long long)current_time.tv_usec / 1000;
	// Convertion de seconde a milliseconde (1 sec == 1000 milliseconde) et de microseconde a milliseconde 1000 microseconde == 1 milliseconde
	return (start_time);
}

int	change_state_to_sleep(t_philo *philo)
{
	long long	final_time;
	long long	start_time;

	pthread_mutex_lock(&philo->rules->someone_died_mutex);
	if (philo->rules->someone_died)
	{
		pthread_mutex_unlock(&philo->rules->someone_died_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->rules->someone_died_mutex);
	start_time = get_current_time();
	final_time = philo->rules->time_to_sleep + start_time;
	pthread_mutex_lock(&philo->mutex_state);
	philo->state = is_sleeping;
	pthread_mutex_unlock(&philo->mutex_state);
	if (!check_someone_died(philo))
	{
		// pthread_mutex_unlock(&philo->rules->printf_mutex);
		return (0);
	}
	pthread_mutex_lock(&philo->rules->printf_mutex);
	if (!check_someone_died(philo))
	{
		pthread_mutex_unlock(&philo->rules->printf_mutex);
		return (0);
	}
	printf("%lld %d is sleeping\n", get_current_time(), philo->id);
	pthread_mutex_unlock(&philo->rules->printf_mutex);
	if (!check_someone_died(philo))
	{
		return (0);
	}
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
		{
			return (0);
		}
		usleep(1000); // 1000 microseconde = 1 milliseconde
	}
	return (1);
}

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
	{
		// pthread_mutex_unlock(&philo->rules->printf_mutex);
		return (0);
	}
	pthread_mutex_lock(&philo->rules->printf_mutex);
	if (!check_someone_died(philo))
	{
		pthread_mutex_unlock(&philo->rules->printf_mutex);
		return (0);
	}
	printf("%lld %d is thinking\n", get_current_time(), philo->id);
	pthread_mutex_unlock(&philo->rules->printf_mutex);
	if (!check_someone_died(philo))
		return (0);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(1000);
	while (check_all_philos_alive(philo->rules->head_philo)
		&& check_can_philo_eat_more(philo))
	{
		if (!check_someone_died(philo))
		{
			// printf("ok routine__1\n");
			if (philo->has_left || philo->has_right)
				release_forks(philo);
			return (NULL);
		}
		if (!take_forks(philo))
		{
			// printf("ok routine__2\n");
			if (philo->has_left || philo->has_right)
			{
				// printf("ok\n");
				release_forks(philo);
				// printf("no\n");
			}
			return (NULL);
		}
		if (!can_eat(philo))
		{
			// printf("ok routine__3\n");
			if (philo->has_left || philo->has_right)
				release_forks(philo);
			return (NULL);
		}
		release_forks(philo);
		if (!check_all_philos_alive(philo->rules->head_philo))
		{
			// printf("ok routine\n");
			if (philo->has_left || philo->has_right)
			{
				// printf("yes\n");
				release_forks(philo);
				// printf("no00\n");
			}
			return (NULL);
		}
		if (!change_state_to_sleep(philo))
		{
			// printf("ok routine__4\n");
			if (philo->has_left || philo->has_right)
				release_forks(philo);
			return (NULL);
		}
		change_state_to_thinking(philo);
	}
	return (NULL);
}

int	init_mutex(t_philo *philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_of_philos)
	{
		pthread_mutex_init(&philo[i].mutex_state, NULL);
		pthread_mutex_init(&philo[i].mutex_meal_count, NULL);
		pthread_mutex_init(&philo[i].mutex_last_meal, NULL);
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
	// rules->printf_mutex = malloc(sizeof(pthread_mutex_t));
	// if (!rules->printf_mutex)
	// 	return (1);
	pthread_mutex_init(&rules->printf_mutex, NULL);
	pthread_mutex_init(&rules->someone_died_mutex, NULL);
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
			return (free(rules->forks), free(rules->thread), free(rules), 1);
		if (create_nb_of_philos(rules, &philos) != 0)
		{
			write(2, "Error\nCreation of philo failed\n", 32);
			return (free(philos), free(rules->thread), free(rules->forks),
				free(rules), 1);
		}
		rules->head_philo = philos;
		if (init_mutex(philos, rules) != 0)
		{
			write(2, "Error\nMutex initialisation failed\n", 35);
			free(philos);
			free(rules->thread);
			free(rules->forks);
			free(rules);
			return (1);
		}
		if (create_threads(rules, philos) != 0)
		{
			write(2, "Error\nCreation of thread failed\n", 33);
			destroy_mutex(philos, rules);
			free(philos);
			free(rules->thread);
			free(rules->forks);
			free(rules);
			return (1);
		}
		i = 0;
		while (i < rules->nb_of_philos)
		{
			if (pthread_join(rules->thread[i], NULL) != 0)
				return (1);
			// printf("Thread %d end\n", i);
			i++;
		}
		destroy_mutex(philos, rules);
		free(rules->forks);
		free(rules->thread);
		free(rules);
		free(philos);
	}
	else
		write(2, "Too many or too less args.Please Enter 5 or 4 args.\n", 53);
	return (0);
}
