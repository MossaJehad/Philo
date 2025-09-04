/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:00:00 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/04 20:31:36 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	update_meal(t_philo *philo)
{
	long	eating_start;

	print_with_safety(philo, "is eating " EAT_SYMBOL, GREEN);
	pthread_mutex_lock(&philo->last_meal_mutex);
	gettimeofday(&philo->start, NULL);
	philo->last_meal = get_time(philo, 1);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	eating_start = get_timestamp_in_ms();
	while (!is_simulation_over(philo) && (get_timestamp_in_ms()
			- eating_start < philo->input[TIME_TO_EAT]))
		usleep(1000);
	return (0);
}

int	start_dinner(t_philo *philo)
{
	if (handle_forks(philo))
		return (1);
	if (update_meal(philo))
	{
		unlock_forks(philo);
		return (1);
	}
	unlock_forks(philo);
	if (!is_simulation_over(philo))
	{
		pthread_mutex_lock(&philo->meal_mutex);
		philo->meals++;
		pthread_mutex_unlock(&philo->meal_mutex);
	}
	if (!is_simulation_over(philo))
		return (0);
	return (1);
}
