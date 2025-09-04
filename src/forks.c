/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:00:00 by h improveme       #+#    #+#             */
/*   Updated: 2025/09/04 12:17:08 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	take_fork(pthread_mutex_t *fork, t_philo *philo, char *msg)
{
	if (is_simulation_over(philo))
		return (0);
	pthread_mutex_lock(fork);
	if (is_simulation_over(philo))
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	print_with_safety(philo, msg);
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
		if (!take_fork(philo->fork_l, philo, CYAN"has taken a fork (left)"RESET))
			return (1);
		if (!take_fork(philo->fork_r, philo, CYAN"has taken a fork (right)"RESET))
		{
			pthread_mutex_unlock(philo->fork_l);
			return (1);
		}
	}
	else
	{
		if (!take_fork(philo->fork_r, philo, CYAN"has taken a fork (right)"RESET))
			return (1);
		if (!take_fork(philo->fork_l, philo, CYAN"has taken a fork (left)"RESET))
		{
			pthread_mutex_unlock(philo->fork_r);
			return (1);
		}
	}
	return (0);
}
