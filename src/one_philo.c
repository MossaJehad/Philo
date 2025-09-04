/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:00:00 by h improveme       #+#    #+#             */
/*   Updated: 2025/09/04 12:18:40 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_eat_one_philo(t_data *table)
{
	gettimeofday(&table->program_start, NULL);
	table->philos[0].start = table->program_start;
	table->philos[0].input = table->input;
	if (pthread_create(&table->philos[0].thread_id, NULL, lonely_routine, &table->philos[0]))
	{
		printf(RED"error creating thread for the one philo\n"RESET);
		return (1);
	}
	pthread_join(table->philos[0].thread_id, NULL);
	return (0);
}
