/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:58:46 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/03 14:22:27 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*one_philo(void *die_time)
{
	int	time_died;

	time_died = *(int *)die_time;
	printf("0\t philo[1] \033[0;33mhas taken a fork\033[0m\n");
	printf("%d\t philo[1] \033[1;31mdied\033[0m\n", time_died);
	return (NULL);
}

int	philo_eat_one_philo(t_data *table)
{
	pthread_t	philo;

	if (pthread_create(&philo, NULL, one_philo, &table->die_time))
	{
		printf("\033[1;31merror crphilo_eat thread for the one philo\033[0m\n");
		return (1);
	}
	pthread_join(philo, NULL);
	return (0);
}

int	ft_thread(t_data *table)
{
	if (table->count == 1)
	{
		if (philo_eat_one_philo(table))
			return (1);
		return (0);
	}
	if (create_all_threads(table))
		return (1);
	monitoring(table);
	join_threads(table);
	cleanup_mutexes(table);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	table;

	if ((argc != 5 && argc != 6) || init_all(&table, argv))
	{
		printf("\033[1;31mWrong in arguments\033[0m\n");
		return (1);
	}
	if (ft_thread(&table))
		return (1);
	return (0);
}
