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
    e_EATING,
    e_SLEEPING,
    e_THINKING,
    e_DIED
} t_state;

typedef struct s_philo {
    int id;
    int last_time_eat;
    int nbr_eat;
    int time;
    t_state state;
    pthread_mutex_t mutex;
    pthread_t thread;
    t_data *data;
} t_philo;

typedef struct s_data {
    int nbr_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_must_eat;
    int time;
    pthread_mutex_t mutex;
    t_philo *philo;
} t_data;

int is_parsing_ok(int argc, char **argv);
int parse_value(int argc, char **argv, t_data *data);
int time_in_ms(int value, int time);
int max(int a, int b);

#endif