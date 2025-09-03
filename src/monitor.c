/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:07:41 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/03 16:54:43 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_dead(t_data *table, int i)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&table->last_meal_mtx);
	time_since_last_meal = get_time(&table->philos[i], 1)
		- table->philos[i].last_meal;
	pthread_mutex_unlock(&table->last_meal_mtx);
	if (time_since_last_meal > table->die_time)
	{
		pthread_mutex_lock(&table->speak_mtx);
		if (table->can_speak)
		{
			pthread_mutex_lock(&table->print_mtx);
			printf(RED"%ld   philo [%d] died\n"RESET,
				get_time(&table->philos[i], 1), i + 1);
			pthread_mutex_unlock(&table->print_mtx);
			table->can_speak = 0;
		}
		pthread_mutex_unlock(&table->speak_mtx);
		return (1);
	}
	return (0);
}

int	check_full(t_data *table, int *all_eaten, int i)
{
	pthread_mutex_lock(&table->meals_mtx);
	if (table->max_meals != -1 && table->philos[i].meals < table->max_meals)
		*all_eaten = 0;
	pthread_mutex_unlock(&table->meals_mtx);
	return (*all_eaten);
}

void	monitoringing(t_data *table)
{
	int	all_eaten;
	int	i;

	while (1)
	{
		all_eaten = 1;
		i = 0;
		while (i < table->count)
		{
			if (check_dead(table, i))
				return ;
			check_full(table, &all_eaten, i);
			i++;
		}
		if (all_eaten && table->max_meals != -1)
		{
			pthread_mutex_lock(&table->speak_mtx);
			table->can_speak = 0;
			pthread_mutex_unlock(&table->speak_mtx);
			return ;
		}
		usleep(500);
	}
}
