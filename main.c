/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:10:31 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/05 19:06:33 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void accurate_msleep(unsigned long long msec)
{
	long	actual_time;

	actual_time = time_in_ms(0, 0);
	while (time_in_ms(0, 0) - actual_time < (long int)(msec))
	{
		usleep(500);
	}
}

void *ft_philo(void *phil)
{
	t_philo	*philo;
	int	temp;
	int	sleep;
	int	c;

	philo = (t_philo *)phil;
	temp = (philo->id + 1) % philo->data->nbr_of_philo;
	sleep = philo->data->t_to_sleep;
	philo->last_time_eat = time_in_ms(0, 0);
	c = (philo->id % 8) + 30;
	while (1)
	{
		if (is_dead(philo))
			break;
		printf("\e[1;%dm%ld Philosopher %d is thinking\e[0m\n", c, time_in_ms(1, philo->time), philo->id + 1);
		if ((philo->id + 1) % 2 == 0)
		{
			if (is_dead(philo))
				break;
			printf("\e[1;%dm%ld Philosopher %d is sleeping\e[0m\n", c, time_in_ms(1, philo->time), philo->id + 1);
			accurate_msleep(sleep);
		}
		if (!pthread_mutex_lock(&philo->mutex_fork) && !pthread_mutex_lock(&philo->data->philo[temp].mutex_fork))
		{
			if (is_dead(philo))
				break;
			printf("\e[1;%dm%ld Philosopher %d has taken a fork\e[0m\n", c, time_in_ms(1, philo->time), philo->id + 1);
			printf("\e[1;%dm%ld Philosopher %d has taken a fork\e[0m\n", c, time_in_ms(1, philo->time), philo->id + 1);
			philo->last_time_eat = time_in_ms(0, 0);
			printf("\e[1;%dm%ld Philosopher %d is eating\e[0m\n", c, time_in_ms(1, philo->time), philo->id + 1);
			accurate_msleep(philo->data->t_to_eat);
			pthread_mutex_unlock(&philo->mutex_fork);
			pthread_mutex_unlock(&philo->data->philo[temp].mutex_fork);
			philo->nbr_eat++;
		}
		if (philo->nbr_eat >= philo->data->nbr_must_eat)
			break;
		if ((philo->id + 1) % 2 != 0)
		{
			if (is_dead(philo))
				break;
			printf("\e[1;%dm%ld Philosopher %d is sleeping\e[0m\n", c, time_in_ms(1, philo->time), philo->id + 1);
			accurate_msleep(sleep);
		}
	}
	if (philo->state == e_died)
		printf("\e[1;101m%ld Philosopher %d died\e[0m\n", philo->death_time, philo->id + 1);
	pthread_mutex_unlock(&philo->mutex_fork);
	pthread_mutex_unlock(&philo->data->philo[temp].mutex_fork);
	return (NULL);
}

long time_in_ms(int value, long time)
{
	struct timeval	tp;
	long		ms;

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

void destroy(t_data *data)
{
	int	i;

	i = 0;
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	while (i < data->nbr_of_philo)
	{
		pthread_mutex_destroy(&data->philo[i].mutex_fork);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_death);

}

int init(int argc, char **argv, t_data *data)
{
	int	i;

	if (!parse_value(argc, argv, data))
		return (0);
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (!data->philo )
		return (0);
	i = 0;
	pthread_mutex_init(&data->mutex_death, NULL);
	data->time = time_in_ms(0, 0);
	while (i < data->nbr_of_philo)
	{
		data->philo[i].time  = time_in_ms(0, 0);
		data->philo[i].death_time  = 0;
		data->philo[i].id = i;
		data->philo[i].nbr_eat = 0;
		data->philo[i].data = data;
		data->philo[i].last_time_eat = time_in_ms(0, 0);
		pthread_mutex_init(&data->philo[i].mutex_fork, NULL);
		pthread_create(&data->philo[i].thread, NULL, \
				ft_philo, &data->philo[i]);
		i++;
	}
	return (1);
}

int is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_death);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex_death);
		return (1);
	}
	if (time_in_ms(0, 0) - philo->last_time_eat >= philo->data->t_to_die)
	{
		philo->death_time = time_in_ms(1, philo->time);
		philo->state = e_died;
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->mutex_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_death);
	return (0);
}

void check_death(t_data *data)
{
	int	i;
	int	n;

	n = data->nbr_of_philo;
	i = 0;
	while (1)
	{
		if (is_dead(&data->philo[i % n]))
			return ;
		i++;
	}
}

int main(int argc, char **argv)
{
	t_data	data;
	int	i;

	if (!init(argc, argv, &data))
		return (0);
	check_death(&data);
	i = 0;
	while (i < data.nbr_of_philo)
	{
		pthread_join(data.philo[i % data.nbr_of_philo].thread, NULL);
		i++;
	}
	destroy(&data);
	return (0);
}
