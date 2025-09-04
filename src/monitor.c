/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:00:00 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/04 18:39:58 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	is_starved(t_data *table, int i, long current_time_ms, long last_eat_time_ms)
{
	if ((current_time_ms - last_eat_time_ms) > table->input[TIME_TO_DIE])
	{
		pthread_mutex_lock(&table->stop_mtx);
		if (!table->stop)
		{
			print_death(&table->philos[i]);
			table->stop = 1;
		}
		pthread_mutex_unlock(&table->stop_mtx);
		return (1);
	}
	return (0);
}

int	check_dead(t_data *table, int i)
{
	long			current_time_ms;
	long			last_eat_time_ms;
	struct timeval	last_eat_time;

	current_time_ms = get_timestamp_in_ms();
	pthread_mutex_lock(&table->philos[i].last_meal_mutex);
	last_eat_time = table->philos[i].start;
	pthread_mutex_unlock(&table->philos[i].last_meal_mutex);
	last_eat_time_ms = (last_eat_time.tv_sec * 1000) + (last_eat_time.tv_usec / 1000);
	
	return (is_starved(table, i, current_time_ms, last_eat_time_ms));
}

int	check_full(t_data *table)
{
	int	i;
	int	all_full;

	i = 0;
	all_full = 1;
	if (table->input[NUM_TO_EAT] == -1)
		return (0);
	while (i < table->count)
	{
		pthread_mutex_lock(&table->philos[i].meal_mutex);
		if (table->philos[i].meals < table->input[NUM_TO_EAT])
		{
			all_full = 0;
			pthread_mutex_unlock(&table->philos[i].meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
		i++;
	}
	return (all_full);
}

void	monitoringing(t_data *table)
{
	int	stop_flag;
	int	i;

	stop_flag = 0;
	sleep_and_check(table, 1);
	while (!stop_flag)
	{
		i = 0;
		while (i < table->count)
		{
			if (check_dead(table, i))
				return ;
			i++;
		}
		if (check_full(table))
		{
			pthread_mutex_lock(&table->stop_mtx);
			table->stop = 1;
			pthread_mutex_unlock(&table->stop_mtx);
			return ;
		}
		pthread_mutex_lock(&table->stop_mtx);
		stop_flag = table->stop;
		pthread_mutex_unlock(&table->stop_mtx);
		usleep(500);
	}
}
