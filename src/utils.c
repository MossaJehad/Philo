/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:58:46 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/04 20:27:32 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	to_int(char *s)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result *= 10;
		result += s[i] - '0';
		i++;
	}
	return (result * sign);
}

int	is_num(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_num(argv[i]))
		{
			printf("Error: Invalid argument\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	*check_args(int argc, char **argv)
{
	int	*nums;

	if (!validate_args(argc, argv))
		return (NULL);
	nums = malloc(sizeof(int) * 5);
	if (!nums)
		return (NULL);
	nums[NUM_OF_PHILO] = to_int(argv[1]);
	nums[TIME_TO_DIE] = to_int(argv[2]);
	nums[TIME_TO_EAT] = to_int(argv[3]);
	nums[TIME_TO_SLEEP] = to_int(argv[4]);
	if (argc == 6)
		nums[NUM_TO_EAT] = to_int(argv[5]);
	else
		nums[NUM_TO_EAT] = -1;
	return (nums);
}
