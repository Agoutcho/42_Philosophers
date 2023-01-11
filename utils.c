/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:37:34 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/11 19:00:56 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	accurate_msleep(unsigned long long msec)
{
	long	actual_time;

	actual_time = time_in_ms(0, 0);
	while (time_in_ms(0, 0) - actual_time < (long int)(msec))
	{
		usleep(500);
	}
}

void	to_print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_death);
	if (philo->state == e_died)
		printf("\e[1;101m%ld Philosopher %d died\e[0m\n", \
				philo->death_time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->mutex_death);
}

long	time_in_ms(int value, long time)
{
	struct timeval	tp;
	long			ms;

	gettimeofday(&tp, NULL);
	if (value)
	{
		ms = tp.tv_sec * 1000;
		ms += tp.tv_usec / 1000;
		return (ms - time);
	}
	else
	{
		ms = tp.tv_sec * 1000;
		ms += tp.tv_usec / 1000;
		return (ms);
	}
}

void	destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		pthread_mutex_destroy(&data->philo[i].mutex_fork);
		i++;
	}
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	pthread_mutex_destroy(&data->mutex_death);
}
