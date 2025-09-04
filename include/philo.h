/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:00:00 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/04 18:39:12 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

// Colors for output with bold
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define RESET "\033[0m"

// Emojis/symbols for actions
# define FORK_SYMBOL "🍴"
# define EAT_SYMBOL "🍝"
# define SLEEP_SYMBOL "💤"
# define THINK_SYMBOL "💭"
# define DEATH_SYMBOL "💀"

// Input array indices
# define NUM_OF_PHILO 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define NUM_TO_EAT 4

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	last_meal_mutex;
	struct s_data	*table;
	int				*input;
	struct timeval	start;
}					t_philo;

typedef struct s_data
{
	int				count;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				max_meals;
	long			start_time;
	int				can_speak;
	int				stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	speak_mtx;
	pthread_mutex_t	start_mtx;
	pthread_mutex_t	stop_mtx;
	struct timeval	program_start;
	t_philo			philos[250];
	int				*input;
}					t_data;

// Utils functions
int		ft_isspace(char c);
int		to_int(char *s);
int		is_num(char *s);

// Time functions
long	get_time(t_philo *philo, int f);
int		print_action(t_philo *philo, char *msg);
int		wait_time(t_philo *philo, int time);
long	get_timestamp_in_ms(void);
int		get_elapsed_time(struct timeval start);
void	sleep_and_check(t_data *table, long ms);

// Init functions
int		init_all(t_data *table, char **argv);
void	cleanup_mutexes(t_data *table);

// Fork handling
void	lock_forks(t_philo *philo, pthread_mutex_t **first, pthread_mutex_t **second);
void	unlock_forks(t_philo *philo);
int		handle_forks(t_philo *philo);

// Eating
int		update_meal(t_philo *philo);
int		start_dinner(t_philo *philo);

// Routine
void	*philo_routine(void *ph);
int		is_simulation_over(t_philo *philo);
void	*lonely_routine(void *arg);

// Thread management
void	join_threads(t_data *table);
int		create_threads(t_data *table);

// Monitoring
int		check_dead(t_data *table, int i);
int		check_full(t_data *table);
void	monitoringing(t_data *table);

// One philo case
int		philo_eat_one_philo(t_data *table);

// Safe printing
void	print_with_safety(t_philo *philo, char *status, char *color);
void	print_death(t_philo *philo);

#endif