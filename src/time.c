/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:00:00 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/04 20:31:28 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time(t_philo *philo, int f)
{
	struct timeval	c_time;
	long			current_time;
	long			begin_time;

	(void)f;
	gettimeofday(&c_time, NULL);
	current_time = (c_time.tv_sec * 1000000 + c_time.tv_usec) / 1000;
	if (philo)
	{
		pthread_mutex_lock(&philo->table->start_mtx);
		begin_time = philo->table->start_time;
		pthread_mutex_unlock(&philo->table->start_mtx);
		return (current_time - begin_time);
	}
	return (current_time);
}

void	print_with_safety(t_philo *philo, char *status, char *color)
{
	int	timestamp;

	pthread_mutex_lock(&philo->table->stop_mtx);
	if (philo->table->stop == 0)
	{
		pthread_mutex_lock(&philo->table->print_mtx);
		timestamp = get_elapsed_time(philo->table->program_start);
		printf("%s%-4d %sphilo [%d] %s%s%s\n", WHITE, timestamp, RESET,
			philo->id + 1, color, status, RESET);
		pthread_mutex_unlock(&philo->table->print_mtx);
	}
	pthread_mutex_unlock(&philo->table->stop_mtx);
}

void	print_death(t_philo *philo)
{
	int	timestamp;

	pthread_mutex_lock(&philo->table->print_mtx);
	timestamp = get_elapsed_time(philo->table->program_start);
	printf("%s%-4d %sphilo [%d] %s%s died%s\n", WHITE, timestamp, RESET,
		philo->id + 1, RED, DEATH_SYMBOL, RESET);
	pthread_mutex_unlock(&philo->table->print_mtx);
}

void	sleep_and_check(t_data *table, long ms)
{
	long	start;
	long	end;

	start = get_timestamp_in_ms();
	end = start + ms;
	while (get_timestamp_in_ms() < end)
	{
		pthread_mutex_lock(&table->stop_mtx);
		if (table->stop)
		{
			pthread_mutex_unlock(&table->stop_mtx);
			break ;
		}
		pthread_mutex_unlock(&table->stop_mtx);
		usleep(500);
	}
}

int	wait_time(t_philo *philo, int time)
{
	int	time_slept;
	int	sleep_time;

	if (!is_simulation_over(philo))
	{
		time_slept = 0;
		while (time_slept < time && !is_simulation_over(philo))
		{
			if (time - time_slept < 10)
				sleep_time = time - time_slept;
			else
				sleep_time = 10;
			usleep(sleep_time * 1000);
			time_slept += sleep_time;
		}
	}
	return (0);
}
