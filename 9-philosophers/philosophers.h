/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:25:02 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/22 17:42:29 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include <pthread.h>
# include <sys/time.h>

typedef enum philo_state
{
	is_thinking,
	is_sleeping,
	is_eating,
	is_died
}						philo_state;

typedef struct s_philo	t_philo;

typedef struct s_rules
{
	int					nb_of_philos;
	long long			start_time;
	long long			time_to_sleep;
	long long			time_to_eat;
	long long			time_to_die;
	int					nb_meals_required;
	int					nb_forks;
	int					someone_died;
	pthread_mutex_t		someone_died_mutex;
	pthread_t			*thread;
	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		printf_mutex;
	t_philo				*head_philo;
}						t_rules;

typedef struct s_philo
{
	int id;              // For identify philo
	long long last_meal; // For estimate time before die
	// long long begining_of_eat;
	// For stop to eat when he time of eat is finish
	int meal_count; // For stop the meal
	int					has_right;
	int					has_left;
	pthread_mutex_t		mutex_last_meal;
	pthread_mutex_t		mutex_state;
	pthread_mutex_t		mutex_meal_count;
	philo_state			state;
	t_rules				*rules;
}						t_philo;

int						initialize_rules(t_rules *rules, int ac, char **av);
int						create_nb_of_philos(t_rules *rules, t_philo **philos);
int						create_threads(t_rules *rules, t_philo *philo);
long long				get_current_time(void);
int						handle_one_philo(t_rules *rules, t_philo *philos);
int						init_mutex(t_philo *philo, t_rules *rules);
void					destroy_mutex(t_philo *philo, t_rules *rules);
void					release_forks(t_philo *philo);
long long				get_current_time(void);
int						check_philo_is_thinking(t_philo *philo);
int						check_someone_died(t_philo *philo);
int						check_can_philo_eat_more(t_philo *philo);
int						change_state_to_thinking(t_philo *philo);
int						change_state_to_sleep(t_philo *philo);
int						check_all_philos_alive(t_philo *philo);
void					notify_death(t_philo *philo, int i);
int						update_eating_state(t_philo *philo,
							long long *stop_eating);
int						print_eating_message(t_philo *philo);
int						wait_and_finish_eating(t_philo *philo,
							long long stop_eating);
int						print_fork_taken(t_philo *philo);
int						take_even_forks(t_philo *philo, int fork_right,
							int fork_left);
int						take_odd_forks(t_philo *philo, int fork_right,
							int fork_left);
void					*routine(void *args);

int						ft_atoi(const char *str);

#endif
