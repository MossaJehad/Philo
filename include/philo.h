/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:39:22 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/03 19:04:42 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define GREEN		"\033[1;32m"
# define CYAN		"\033[1;36m"
# define YELLOW		"\033[1;33m"
# define RED		"\033[1;31m"
# define BLUE		"\033[1;34m"
# define MAGENTA	"\033[1;35m"
# define RESET		"\033[0m"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					is_dead;
	int					meals;
	long				last_meal;
	pthread_t			thread_id;
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		*fork_l;
	t_data				*table;
}						t_philo;

typedef struct s_data
{
	int					count;
	int					eat_time;
	int					max_meals;
	int					sleep_time;
	int					die_time;
	int					can_speak;
	long				start_time;
	pthread_t			monitoring;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		meals_mtx;
	pthread_mutex_t		print_mtx;
	pthread_mutex_t		last_meal_mtx;
	pthread_mutex_t		speak_mtx;
	pthread_mutex_t		start_mtx;
	t_philo				philos[250];
}						t_data;

int						philo_eat_one_philo(t_data *table);
void					smart_smart_usleep(long duration_ms);
void					*philo_routine(void *p);
int						is_dead(t_philo *p);
int						handle_forks(t_philo *p, int f);
void						lock_forks(t_philo *p,
							pthread_mutex_t **first,
							pthread_mutex_t **second);
int						create_threads(t_data *table);
void					join_threads(t_data *table);
void					cleanup_mutexes(t_data *table);
void					monitoringing(t_data *table);
int						check_dead(t_data *table, int i);
int						check_full(t_data *table, int *full, int i);
long					get_time(t_philo *p, int f);
int						print_action(t_philo *p, char *msg);
int						wait_time(t_philo *p, int time);
int						to_int(char *s);
int						is_num(char *s);
int						init_all(t_data *table, char **argv);
int						start_dinner(t_philo *philo);
int						update_meal(t_philo *philo);
void					unlock_forks(t_philo *philo);
#endif
