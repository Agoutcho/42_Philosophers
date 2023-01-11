#include "philosopher.h"

int thinking(t_philo *philo)
{
	int	c;

	c = (philo->id % 8) + 30;
	if (is_dead(philo))
			return (0);
	printf("\e[1;%dm%ld Philosopher %d is thinking\e[0m\n",\
		c, time_in_ms(1, philo->time), philo->id + 1);
	if (philo->data->nbr_of_philo == 1)
	{
		philo->state = e_died;
		accurate_msleep(philo->data->t_to_die + 2);
		return (0);
	}
	return (1);
}

int sleeping(t_philo *philo)
{
	if (is_dead(philo))
		return (0);
	printf("\e[1;%dm%ld Philosopher %d is sleeping\e[0m\n", c, time_in_ms(1, philo->time), philo->id + 1);
	accurate_msleep(sleep);
	return (1);
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
		if (!thinking(philo))
			break;
		if ((philo->id + 1) % 2 == 0)
		{
			if (!sleeping(philo))
				break;
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
		if (philo->data->nbr_must_eat != -1 && philo->nbr_eat >= philo->data->nbr_must_eat)
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