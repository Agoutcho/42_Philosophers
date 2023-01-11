/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:37:38 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/11 18:43:52 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	to_print(char *str, t_philo *philo)
{
	int	c;
	int	temp;

	temp = (philo->id + 1) % philo->data->nbr_of_philo;
	c = (philo->id % 8) + 30;
	printf(str, c, time_in_ms(1, philo->time), philo->id + 1);
}

int	thinking(t_philo *philo)
{
	int	c;

	c = (philo->id % 8) + 30;
	if (is_dead(philo))
		return (0);
	printf("\e[1;%dm%ld Philosopher %d is thinking\e[0m\n", \
			c, time_in_ms(1, philo->time), philo->id + 1);
	if (philo->data->nbr_of_philo == 1)
	{
		pthread_mutex_lock(&philo->data->mutex_death);
		philo->state = e_died;
		pthread_mutex_unlock(&philo->data->mutex_death);
		if (!pthread_mutex_lock(&philo->mutex_fork))
			to_print("\e[1;%dm%ld Philosopher %d has taken a fork\e[0m\n", philo);
		accurate_msleep(philo->data->t_to_die + 2);
		pthread_mutex_unlock(&philo->mutex_fork);
		return (0);
	}
	return (1);
}

int	sleeping(t_philo *philo)
{
	int	c;
	int	sleep;

	sleep = philo->data->t_to_sleep;
	c = (philo->id % 8) + 30;
	if (is_dead(philo))
		return (0);
	printf("\e[1;%dm%ld Philosopher %d is sleeping\e[0m\n", \
			c, time_in_ms(1, philo->time), philo->id + 1);
	accurate_msleep(sleep);
	return (1);
}

int	eating(t_philo *philo)
{
	int	temp;

	temp = (philo->id + 1) % philo->data->nbr_of_philo;
	if (is_dead(philo))
		return (0);
	if (!pthread_mutex_lock(&philo->mutex_fork))
	{
		to_print("\e[1;%dm%ld Philosopher %d has taken a fork\e[0m\n", philo);
		if (!pthread_mutex_lock(&philo->data->philo[temp].mutex_fork))
			to_print("\e[1;%dm%ld Philosopher %d has taken a fork\e[0m\n", philo);
		if (is_dead(philo))
			return (0);
		philo->last_time_eat = time_in_ms(0, 0);
		to_print("\e[1;%dm%ld Philosopher %d is eating\e[0m\n", philo);
		accurate_msleep(philo->data->t_to_eat);
		pthread_mutex_unlock(&philo->mutex_fork);
		pthread_mutex_unlock(&philo->data->philo[temp].mutex_fork);
		philo->nbr_eat++;
	}
	if (philo->data->nbr_must_eat != -1 \
			&& philo->nbr_eat >= philo->data->nbr_must_eat)
		return (0);
	return (1);
}

void	*ft_philo(void *phil)
{
	t_philo	*philo;
	int		temp;

	philo = (t_philo *)phil;
	temp = (philo->id + 1) % philo->data->nbr_of_philo;
	while (1 && thinking(philo))
	{
		if ((philo->id + 1) % 2 == 0 && !sleeping(philo))
			break ;
		if (!eating(philo))
			break ;
		if ((philo->id + 1) % 2 != 0 && !sleeping(philo))
			break ;
	}
	to_print_death(philo);
	pthread_mutex_unlock(&philo->mutex_fork);
	pthread_mutex_unlock(&philo->data->philo[temp].mutex_fork);
	return (NULL);
}
