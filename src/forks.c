/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:27:04 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/03 17:05:49 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>

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

int	handle_forks(t_philo *philo, int f)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	(void)f;
	if (lock_forks(philo, &first, &second))
		return (1);
	pthread_mutex_lock(first);
	print_action(philo, CYAN"has taken a fork (left)"RESET);
	pthread_mutex_lock(second);
	print_action(philo, CYAN"has taken a fork (right)"RESET);
	philo_eat(philo);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
	return (0);
}
