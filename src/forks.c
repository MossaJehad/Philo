/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:27:04 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/03 19:14:56 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>

void	lock_forks(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->fork_l;
		*second = philo->fork_r;
	}
	else
	{
		*first = philo->fork_r;
		*second = philo->fork_l;
	}
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

int	handle_forks(t_philo *philo, int f)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	(void)f;
	lock_forks(philo, &first, &second);
	pthread_mutex_lock(first);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(first);
		return (1);
	}
	print_action(philo, CYAN"has taken a fork (left)"RESET);
	pthread_mutex_lock(second);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (1);
	}
	print_action(philo, CYAN"has taken a fork (right)"RESET);
	return (0);
}
