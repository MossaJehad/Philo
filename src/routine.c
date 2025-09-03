/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:58:46 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/03 18:52:04 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_dead(philo))
	{
		if (start_dinner(philo))
			break ;
		if (is_dead(philo))
			break ;
		if (print_action(philo, YELLOW"is thinking"RESET))
			break ;
		if (is_dead(philo))
			break ;
		if (print_action(philo, MAGENTA"is sleeping"RESET))
			break ;
		if (wait_time(philo, philo->table->sleep_time))
			break ;
	}
	return (NULL);
}

int	is_dead(t_philo *philo)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->table->last_meal_mtx);
	time_since_last_meal = get_time(philo, 1) - philo->last_meal;
	pthread_mutex_unlock(&philo->table->last_meal_mtx);
	return (time_since_last_meal > philo->table->die_time);
}
