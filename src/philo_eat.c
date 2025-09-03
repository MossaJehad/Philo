/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:58:46 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/03 17:05:23 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	update_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->last_meal_mtx);
	philo->last_meal = get_time(philo, 1);
	pthread_mutex_unlock(&philo->table->last_meal_mtx);
	pthread_mutex_lock(&philo->table->meals_mtx);
	philo->meals++;
	pthread_mutex_unlock(&philo->table->meals_mtx);
}

int	philo_eat(t_philo *philo)
{
	update_meal(philo);
	return (wait_time(philo, philo->table->eat_time));
}

int	lock_second(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second)
{
	(void)first;
	pthread_mutex_lock(second);
	if (second == philo->fork_l)
	{
		if (print_action(philo, CYAN"has taken a fork (left)"RESET))
		{
			pthread_mutex_unlock(second);
			return (1);
		}
	}
	else if (print_action(philo, CYAN"has taken a fork (right)"RESET))
	{
		pthread_mutex_unlock(second);
		return (1);
	}
	if (is_dead(philo))
	{
		pthread_mutex_unlock(second);
		return (1);
	}
	return (0);
}

int	start_dinner(t_philo *philo)
{
	if (handle_forks(philo, 1))
		return (1);
	if (print_action(philo, BLUE"is eating"RESET))
		return (1);
	return (0);
}
