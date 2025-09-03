/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:58:46 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/03 16:03:11 by mhasoneh         ###   ########.fr       */
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
	if (pthread_mutex_init(&table->last_meal_mtx, NULL)
		|| pthread_mutex_init(&table->print_mtx, NULL)
		|| pthread_mutex_init(&table->meals_mtx, NULL)
		|| pthread_mutex_init(&table->speak_mtx, NULL)
		|| pthread_mutex_init(&table->start_mtx, NULL))
		return (1);
	return (0);
}

static int	init_philos(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->count)
	{
		table->philos[i].id = i;
		table->philos[i].meals = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].table = table;
		table->philos[i].fork_r = &table->forks[i];
		if (i != table->count - 1)
			table->philos[i].fork_l = &table->forks[i + 1];
		else
			table->philos[i].fork_l = &table->forks[0];
		i++;
	}
	return (0);
}

static int	init_max_meals(t_data *table, char *str)
{
	if (!is_num(str))
		return (1);
	table->max_meals = to_int(str);
	if (table->max_meals <= 0)
		return (1);
	return (0);
}

int	init_all(t_data *table, char **argv)
{
	if (!is_num(argv[1]) || !is_num(argv[2]) || !is_num(argv[3])
		|| !is_num(argv[4]))
		return (1);
	table->count = to_int(argv[1]);
	table->die_time = to_int(argv[2]);
	table->eat_time = to_int(argv[3]);
	table->sleep_time = to_int(argv[4]);
	table->max_meals = -1;
	table->start_time = 0;
	table->can_speak = 1;
	if (argv[5])
	{
		if (init_max_meals(table, argv[5]))
			return (1);
	}
	if (table->count <= 0 || table->die_time <= 0
		|| table->eat_time <= 0 || table->sleep_time <= 0
		|| table->count > 250)
		return (1);
	if (init_mutexes(table))
		return (1);
	if (init_philos(table))
		return (1);
	return (0);
}

void	cleanup_mutexes(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->meals_mtx);
	pthread_mutex_destroy(&table->print_mtx);
	pthread_mutex_destroy(&table->last_meal_mtx);
	pthread_mutex_destroy(&table->speak_mtx);
	pthread_mutex_destroy(&table->start_mtx);
}
