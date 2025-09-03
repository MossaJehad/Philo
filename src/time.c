/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:58:46 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/03 17:05:11 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <unistd.h>

long	get_time(t_philo *philo, int f)
{
	struct timeval	c_time;
	long			current_time;
	long			begin_time;

	gettimeofday(&c_time, NULL);
	current_time = (c_time.tv_sec * 1000000 + c_time.tv_usec) / 1000;
	if (f && philo)
	{
		pthread_mutex_lock(&philo->table->start_mtx);
		begin_time = philo->table->start_time;
		pthread_mutex_unlock(&philo->table->start_mtx);
		return (current_time - begin_time);
	}
	return (current_time);
}

int	print_action(t_philo *philo, char *msg)
{
	long	timephilo;

	pthread_mutex_lock(&philo->table->speak_mtx);
	if (!philo->table->can_speak)
	{
		pthread_mutex_unlock(&philo->table->speak_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->speak_mtx);
	pthread_mutex_lock(&philo->table->speak_mtx);
	timephilo = get_time(philo, 1);
	if (philo->table->can_speak)
		printf("%ld   philo [%d] %s\n", timephilo, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->table->speak_mtx);
	return (0);
}

int	wait_time(t_philo *philo, int time)
{
	long	start;
	long	now;

	start = get_time(philo, 1);
	while (1)
	{
		now = get_time(philo, 1);
		if (is_dead(philo) || (now - start >= time))
			break ;
		usleep(100);
	}
	return (0);
}
