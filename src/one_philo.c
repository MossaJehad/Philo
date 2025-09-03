/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:30:46 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/03 16:54:32 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*one_philo(void *die_time)
{
	int	time_died;

	time_died = *(int *)die_time;
	printf(CYAN"0   philo [1] has taken a fork (right)\n"RESET);
	usleep(time_died);
	printf(RED"%d   philo [1] died\n"RESET, time_died);
	return (NULL);
}

int	philo_eat_one_philo(t_data *table)
{
	pthread_t	philo;

	if (pthread_create(&philo, NULL, one_philo, &table->die_time))
	{
		printf(RED"error creating thread for the one philo\n"RESET);
		return (1);
	}
	pthread_join(philo, NULL);
	return (0);
}
