/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:12:25 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/04 20:12:33 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	get_elapsed_time(struct timeval start)
{
	return ((int)(get_timestamp_in_ms() - ((start.tv_sec * 1000)
			+ (start.tv_usec / 1000))));
}
