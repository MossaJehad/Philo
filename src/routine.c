/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:00:00 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/04 20:36:40 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_fulls(t_philo *philo)
{
	int	full;

	if (philo->input[NUM_TO_EAT] == -1)
		return (0);
	pthread_mutex_lock(&philo->meal_mutex);
	full = philo->meals >= philo->input[NUM_TO_EAT];
	pthread_mutex_unlock(&philo->meal_mutex);
	return (full);
}

int	is_simulation_over(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->table->stop_mtx);
	stop = philo->table->stop;
	pthread_mutex_unlock(&philo->table->stop_mtx);
	return (stop);
}

static void	think(t_philo *philo)
{
	if (!is_simulation_over(philo))
		print_with_safety(philo, "is thinking " THINK_SYMBOL, YELLOW);
}

void	*lonely_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->fork_r);
	print_with_safety(philo, "has taken a fork " FORK_SYMBOL, CYAN);
	sleep_and_check(philo->table, philo->input[TIME_TO_DIE]);
	pthread_mutex_unlock(philo->fork_r);
	return (NULL);
}

void	*philo_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->id % 2 == 0)
		sleep_and_check(philo->table, 1);
	while (!is_simulation_over(philo))
	{
		if (check_fulls(philo))
			break ;
		if (start_dinner(philo))
			break ;
		if (check_fulls(philo))
			break ;
		if (is_simulation_over(philo))
			break ;
		print_with_safety(philo, "is sleeping " SLEEP_SYMBOL, BLUE);
		wait_time(philo, philo->table->sleep_time);
		if (is_simulation_over(philo))
			break ;
		think(philo);
	}
	return (NULL);
}
