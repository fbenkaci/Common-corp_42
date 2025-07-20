/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:25:02 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/20 15:11:55 by fbenkaci         ###   ########.fr       */
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
	long long			time_to_sleep;
	long long			time_to_eat;
	long long			time_to_die;
	int					nb_meals_required;
	int					nb_forks;
	int					*forks;
	int					someone_died;
	pthread_mutex_t		someone_died_mutex;
	pthread_t			*thread;
	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		printf_mutex;
	t_philo				*head_philo;
}						t_rules;

typedef struct s_philo
{
	int id;                    // For identify philo
	long long last_meal;       // For estimate time before die
	long long begining_of_eat; // For stop to eat when he time of eat is finish
	int meal_count;            // For stop the meal
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
void					*routine(void *args);

int						ft_atoi(const char *str);

#endif
