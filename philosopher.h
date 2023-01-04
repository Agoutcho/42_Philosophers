/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:08:01 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/04 22:31:53 by atchougo         ###   ########.fr       */
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

typedef enum e_state{
    e_EATING,
    e_SLEEPING,
    e_THINKING,
    e_DIED
} t_state;

typedef struct s_philo {
    int id;
    t_state state;
} t_philo;

typedef struct s_data {
    int nbr_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_must_eat;
    pthread_mutex_t mutex;
} t_data;

int is_parsing_ok(int argc, char **argv);
int init_value(int argc, char **argv, t_data *data);

#endif