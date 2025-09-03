/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:58:46 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/03 14:20:58 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	update_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->last_meal_mutex);
	philo->last_meal = get_time(philo, 1);
	pthread_mutex_unlock(&philo->table->last_meal_mutex);
	pthread_mutex_lock(&philo->table->meals_mutex);
	philo->meals++;
	pthread_mutex_unlock(&philo->table->meals_mutex);
}

int	philo_eat(t_philo *philo)
{
	update_meal(philo);
	return (wait_time(philo, philo->table->eat_time));
}

int	lock_forks(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->fork_l < philo->fork_r)
	{
		*first = philo->fork_l;
		*second = philo->fork_r;
		philo->has_fork = 1;
	}
	else
	{
		*first = philo->fork_r;
		*second = philo->fork_l;
		philo->has_fork = 0;
	}
	return (0);
}

int	lock_forks(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	if (print_action(philo, "\033[0;33mhas taken a fork\033[0m"))
	{
		pthread_mutex_unlock(first);
		return (1);
	}
	pthread_mutex_lock(second);
	if (print_action(philo, "\033[0;33mhas taken a fork\033[0m"))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (1);
	}
	if (is_dead(philo))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (1);
	}
	return (0);
}

int	handle_forks(t_philo *philo, int f)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (f)
	{
		if (lock_forks(philo, &first, &second))
			return (1);
		if (lock_forks(philo, first, second))
			return (1);
	}
	else
	{
		if (philo->has_fork)
		{
			pthread_mutex_unlock(philo->fork_r);
			pthread_mutex_unlock(philo->fork_l);
		}
		else
		{
			pthread_mutex_unlock(philo->fork_l);
			pthread_mutex_unlock(philo->fork_r);
		}
	}
	return (0);
}
