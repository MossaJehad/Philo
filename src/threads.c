/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:00:00 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/04 20:14:16 by mhasoneh         ###   ########.fr       */
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
	gettimeofday(&table->program_start, NULL);
	pthread_mutex_unlock(&table->start_mtx);
	i = 0;
	while (i < table->count)
	{
		pthread_mutex_lock(&table->philos[i].last_meal_mutex);
		table->philos[i].start = table->program_start;
		table->philos[i].last_meal = table->start_time;
		pthread_mutex_unlock(&table->philos[i].last_meal_mutex);
		if (pthread_create(&table->philos[i].thread_id, NULL, philo_routine,
				&table->philos[i]))
		{
			printf(RED "error creating thread philo [%d]\n" RESET, i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	cleanup_mutexes(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		pthread_mutex_destroy(&table->philos[i].last_meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->print_mtx);
	pthread_mutex_destroy(&table->speak_mtx);
	pthread_mutex_destroy(&table->start_mtx);
	pthread_mutex_destroy(&table->stop_mtx);
}
