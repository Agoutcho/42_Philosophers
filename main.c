/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:10:31 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/11 18:41:39 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

int	is_dead(t_philo *philo)
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

void	check_death(t_data *data)
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

int	init(int argc, char **argv, t_data *data)
{
	int	i;

	if (!parse_value(argc, argv, data))
		return (0);
	data->philo = (t_philo *) malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (!data->philo)
		return (0);
	i = 0;
	pthread_mutex_init(&data->mutex_death, NULL);
	data->time = time_in_ms(0, 0);
	while (i < data->nbr_of_philo)
	{
		data->philo[i].time = time_in_ms(0, 0);
		data->philo[i].death_time = 0;
		data->philo[i].id = i;
		data->philo[i].nbr_eat = 0;
		data->philo[i].data = data;
		data->philo[i].last_time_eat = time_in_ms(0, 0);
		pthread_mutex_init(&data->philo[i].mutex_fork, NULL);
        if (i == 0)
		    pthread_mutex_lock(&data->philo[i].mutex_fork);
		pthread_create(&data->philo[i].thread, NULL, \
				ft_philo, &data->philo[i]);
        if (i == 0)
            pthread_mutex_unlock(&data->philo[i].mutex_fork);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

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
