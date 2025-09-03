/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:58:46 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/03 18:51:11 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	join_threads(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->count)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
}

int	create_threads(t_data *table)
{
	int	i;

	pthread_mutex_lock(&table->start_mtx);
	table->start_time = get_time(NULL, 0);
	pthread_mutex_unlock(&table->start_mtx);
	i = 0;
	while (i < table->count)
	{
		pthread_mutex_lock(&table->last_meal_mtx);
		table->philos[i].last_meal = table->start_time;
		pthread_mutex_unlock(&table->last_meal_mtx);
		if (pthread_create(&table->philos[i].thread_id, NULL, philo_routine,
				&table->philos[i]))
		{
			pthread_mutex_lock(&table->print_mtx);
			printf(RED"error creating thread philo [%d]\n"RESET, i + 1);
			pthread_mutex_unlock(&table->print_mtx);
			return (1);
		}
		usleep(100);
		i++;
	}
	return (0);
}
