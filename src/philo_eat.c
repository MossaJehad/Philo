/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:58:46 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/03 19:13:07 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>

int	update_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->last_meal_mtx);
	philo->last_meal = get_time(philo, 1);
	pthread_mutex_unlock(&philo->table->last_meal_mtx);
	pthread_mutex_lock(&philo->table->meals_mtx);
	philo->meals++;
	pthread_mutex_unlock(&philo->table->meals_mtx);
	return (0);
}

int	start_dinner(t_philo *philo)
{
	if (handle_forks(philo, 1))
		return (1);
	if (print_action(philo, BLUE"is eating"RESET))
	{
		unlock_forks(philo);
		return (1);
	}
	if (update_meal(philo))
	{
		unlock_forks(philo);
		return (1);
	}
	if (wait_time(philo, philo->table->eat_time))
	{
		unlock_forks(philo);
		return (1);
	}
	unlock_forks(philo);
	return (0);
}
