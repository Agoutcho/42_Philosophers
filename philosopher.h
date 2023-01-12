/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:08:01 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/12 19:29:30 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data	t_data;

typedef enum e_state{
	e_eating = 1,
	e_sleeping,
	e_thinking,
	e_died
}			t_state;

typedef struct s_philo {
	int				id;
	long			last_time_eat;
	int				nbr_eat;
	long			time;
	long			death_time;
	t_state			state;
	pthread_mutex_t	mutex_fork;
	pthread_t		thread;
	t_data			*data;
}				t_philo;

typedef struct s_data {
	int				nbr_of_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nbr_must_eat;
	long			time;
	int				dead;
	int				stop;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_stop;
	t_philo			*philo;
}				t_data;

int		parse_value(int argc, char **argv, t_data *data);
long	time_in_ms(int value, long time);
int		is_dead(t_philo *philo);
void	destroy(t_data *data);
void	*ft_philo(void *phil);
void	accurate_msleep(unsigned long long msec);
void	to_print(char *str, t_philo *philo);
void	to_print_death(t_philo *philo);
void	repare_value(t_data *data);

#endif
