/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:58:46 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/03 14:22:50 by mhasoneh         ###   ########.fr       */
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

int	create_all_threads(t_data *table)
{
	int	i;

	pthread_mutex_lock(&table->start_mtx);
	table->start_time = get_time(NULL, 0);
	pthread_mutex_unlock(&table->start_mtx);
	i = 0;
	while (i < table->count)
	{
		pthread_mutex_lock(&table->last_meal_mutex);
		table->philos[i].last_meal = table->start_time;
		pthread_mutex_unlock(&table->last_meal_mutex);
		if (pthread_create(&table->philos[i].thread_id, NULL, philo_routine,
				&table->philos[i]))
		{
			pthread_mutex_lock(&table->print_mtx);
			printf("\033[1;31merror crphilo_eat thread philo[%d]\033[0m\n", i + 1);
			pthread_mutex_unlock(&table->print_mtx);
			return (1);
		}
		usleep(100);
		i++;
	}
	return (0);
}

int	check_dead(t_data *table, int i)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&table->last_meal_mutex);
	time_since_last_meal = get_time(&table->philos[i], 1)
		- table->philos[i].last_meal;
	pthread_mutex_unlock(&table->last_meal_mutex);
	if (time_since_last_meal > table->die_time)
	{
		pthread_mutex_lock(&table->can_speak_mutex);
		if (table->can_speak)
		{
			pthread_mutex_lock(&table->print_mtx);
			printf("%ld\t philo[%d] \033[1;31mdied\033[0m\n",
				get_time(&table->philos[i], 1), i + 1);
			pthread_mutex_unlock(&table->print_mtx);
			table->can_speak = 0;
		}
		pthread_mutex_unlock(&table->can_speak_mutex);
		return (1);
	}
	return (0);
}

int	check_full(t_data *table, int *all_eaten, int i)
{
	pthread_mutex_lock(&table->meals_mutex);
	if (table->max_meals != -1 && table->philos[i].meals < table->max_meals)
		*all_eaten = 0;
	pthread_mutex_unlock(&table->meals_mutex);
	return (*all_eaten);
}

void	monitoring(t_data *table)
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
			pthread_mutex_lock(&table->can_speak_mutex);
			table->can_speak = 0;
			pthread_mutex_unlock(&table->can_speak_mutex);
			return ;
		}
		usleep(500);
	}
}
