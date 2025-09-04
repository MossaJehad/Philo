/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:00:00 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/04 18:39:23 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	take_fork(pthread_mutex_t *fork, t_philo *philo, char *msg, char *color)
{
	if (is_simulation_over(philo))
		return (0);
	pthread_mutex_lock(fork);
	if (is_simulation_over(philo))
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	print_with_safety(philo, msg, color);
	return (1);
}

void	unlock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
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

int	handle_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (!take_fork(philo->fork_l, philo, "has taken a fork", CYAN))
			return (1);
		if (!take_fork(philo->fork_r, philo, "has taken a fork", CYAN))
		{
			pthread_mutex_unlock(philo->fork_l);
			return (1);
		}
	}
	else
	{
		if (!take_fork(philo->fork_r, philo, "has taken a fork", CYAN))
			return (1);
		if (!take_fork(philo->fork_l, philo, "has taken a fork", CYAN))
		{
			pthread_mutex_unlock(philo->fork_r);
			return (1);
		}
	}
	return (0);
}
