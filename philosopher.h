/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:08:01 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/04 17:51:08 by atchougo         ###   ########.fr       */
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

typedef struct s_philo {
    int id;
} t_philo;

typedef struct s_data {
    int nbr_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_must_eat;
} t_data;

#endif