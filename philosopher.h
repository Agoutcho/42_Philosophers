/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:08:01 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/05 19:01:06 by atchougo         ###   ########.fr       */
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

typedef struct s_data t_data;

typedef enum e_state{
    e_eating,
    e_sleeping,
    e_thinking,
    e_died
} t_state;

typedef struct s_philo {
    int id;
    long last_time_eat;
    int nbr_eat;
    long time;
    long death_time;
    t_state state;
    pthread_mutex_t mutex_fork;
    pthread_t thread;
    t_data *data;
} t_philo;

typedef struct s_data {
    int nbr_of_philo;
    int t_to_die;
    int t_to_eat;
    int t_to_sleep;
    int nbr_must_eat;
    long time;
    int dead;
    pthread_mutex_t mutex_death;
    t_philo *philo;
} t_data;

int is_parsing_ok(int argc, char **argv);
int parse_value(int argc, char **argv, t_data *data);
long time_in_ms(int value, long time);
long time_in_us(int value, long time);
int max(int a, int b);
int is_dead(t_philo *philo);

#endif