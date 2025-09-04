/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:00:00 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/04 18:27:24 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	start_simulation(t_data *table)
{
	if (table->count == 1)
	{
		if (philo_eat_one_philo(table))
			return (1);
		return (0);
	}
	if (create_threads(table))
		return (1);
	monitoringing(table);
	join_threads(table);
	return (0);
}

static void	free_program(t_data *table)
{
	cleanup_mutexes(table);
	if (table->input)
		free(table->input);
	if (table->forks)
		free(table->forks);
}

int	main(int argc, char **argv)
{
	t_data	table;

	memset(&table, 0, sizeof(t_data));
	if ((argc != 5 && argc != 6) || init_all(&table, argv))
	{
		printf(RED"Wrong in arguments\n"RESET);
		return (1);
	}
	if (start_simulation(&table))
	{
		free_program(&table);
		return (1);
	}
	free_program(&table);
	return (0);
}
