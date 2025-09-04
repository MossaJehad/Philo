/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:00:00 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/04 20:27:05 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_mutexes(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->count)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&table->print_mtx, NULL)
		|| pthread_mutex_init(&table->speak_mtx, NULL)
		|| pthread_mutex_init(&table->start_mtx, NULL)
		|| pthread_mutex_init(&table->stop_mtx, NULL))
		return (1);
	return (0);
}

static int	assign_philos(t_data *table, int i)
{
	if (pthread_mutex_init(&table->philos[i].meal_mutex, NULL) != 0
		|| pthread_mutex_init(&table->philos[i].last_meal_mutex, NULL) != 0)
	{
		while (--i >= 0)
		{
			pthread_mutex_destroy(&table->philos[i].meal_mutex);
			pthread_mutex_destroy(&table->philos[i].last_meal_mutex);
		}
		return (0);
	}
	table->philos[i].id = i;
	table->philos[i].meals = 0;
	table->philos[i].last_meal = 0;
	table->philos[i].table = table;
	table->philos[i].input = table->input;
	table->philos[i].start = table->program_start;
	table->philos[i].fork_r = &table->forks[i];
	if (i != table->count - 1)
		table->philos[i].fork_l = &table->forks[i + 1];
	else
		table->philos[i].fork_l = &table->forks[0];
	return (1);
}

static int	init_philos(t_data *table)
{
	int	i;

	gettimeofday(&table->program_start, NULL);
	i = 0;
	while (i < table->count)
	{
		if (!assign_philos(table, i))
		{
			cleanup_mutexes(table);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_input_data(t_data *table, char **argv)
{
	int	argc_val;

	if (argv[5])
		argc_val = 6;
	else
		argc_val = 5;
	table->input = check_args(argc_val, argv);
	if (!table->input)
		return (1);
	table->count = table->input[NUM_OF_PHILO];
	table->die_time = table->input[TIME_TO_DIE];
	table->eat_time = table->input[TIME_TO_EAT];
	table->sleep_time = table->input[TIME_TO_SLEEP];
	table->max_meals = table->input[NUM_TO_EAT];
	table->start_time = 0;
	table->can_speak = 1;
	table->stop = 0;
	if (table->count <= 0 || table->die_time <= 0 || table->eat_time <= 0
		|| table->sleep_time <= 0 || table->count > 250)
	{
		free(table->input);
		return (1);
	}
	return (0);
}

int	init_all(t_data *table, char **argv)
{
	if (init_input_data(table, argv))
		return (1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->count);
	if (!table->forks)
	{
		free(table->input);
		return (1);
	}
	if (init_mutexes(table))
	{
		free(table->forks);
		free(table->input);
		return (1);
	}
	if (!init_philos(table))
	{
		free(table->forks);
		free(table->input);
		return (1);
	}
	return (0);
}
