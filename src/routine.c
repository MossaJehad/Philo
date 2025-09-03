/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:58:46 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/03 14:23:08 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->thread_id % 2 == 0)
		usleep(1000);
	while (!is_dead(philo))
	{
		if (start_dinner(philo))
			break ;
		if (is_dead(philo))
			break ;
		if (print_action(philo, "\033[0;36mis sleeping\033[0m"))
			break ;
		if (wait_time(philo, philo->table->sleep_time))
			break ;
		if (is_dead(philo))
			break ;
		if (print_action(philo, "\033[0;35mis philo_thinking\033[0m"))
			break ;
	}
	return (NULL);
}

int	is_dead(t_philo *philo)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->table->last_meal_mutex);
	time_since_last_meal = get_time(philo, 1) - philo->last_meal;
	pthread_mutex_unlock(&philo->table->last_meal_mutex);
	return (time_since_last_meal > philo->table->die_time);
}

int	start_dinner(t_philo *philo)
{
	if (handle_forks(philo, 1))
		return (1);
	if (print_action(philo, "\033[0;32mis philo_eat\033[0m"))
	{
		handle_forks(philo, 0);
		return (1);
	}
	if (philo_eat(philo))
	{
		handle_forks(philo, 0);
		return (1);
	}
	handle_forks(philo, 0);
	return (0);
}
