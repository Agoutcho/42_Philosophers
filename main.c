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
#include <string.h>

struct s_dataa{
        int is_dead;
        int time;
};

void accurate_msleep(unsigned long long usec)
{
    struct timeval tp;
    int time;
    
    gettimeofday(&tp, NULL);
    time = tp.tv_usec;
    while (tp.tv_usec - time < (int)(usec * 1000))
    {
        gettimeofday(&tp, NULL);
        usleep(1);
    }
}

void *fct(void *arg)
{
    // struct timeval tp;
    // struct s_dataa *deado = (struct s_dataa *)arg;
    // gettimeofday(&tp, NULL);
    // int i = 0;
    // // printf("[%s] ENTER time : %d\n",__FUNCTION__,  tp.tv_usec - deado->time);
    // while(!deado->is_dead)
    // {
    //     gettimeofday(&tp, NULL);
    //     printf("[%s] Before usleep time : %d\n",__FUNCTION__,  tp.tv_usec - deado->time);
    //     accurate_msleep(15);
    //     i++;
    // }
    t_data *data;
    data = (t_data *)arg;
    pthread_mutex_lock(&data->mutex);
    printf("[%s] Here !\n",__FUNCTION__);
    pthread_mutex_unlock(&data->mutex);
    printf("[%s] FINITO !\n",__FUNCTION__);
    return NULL;
}

void destroy(t_data *data)
{
    pthread_mutex_destroy(&data->mutex);
}

void *ft_philo(void *phil)
{
    t_philo *data;
    int temp;

    data = (t_philo *)phil;
    temp = (data->id + 1) % data->data->nbr_of_philo;
    if (!pthread_mutex_lock(&data->mutex) && !pthread_mutex_lock(&data->data->philo[temp].mutex))
    {
        printf("%d Philosopher %d has taken a fork", time_in_ms(1, data->data), data->id + 1);
        accurate_msleep(data->data->time_to_eat);
        pthread_mutex_unlock(&data->mutex);
        pthread_mutex_unlock(&data->data->philo[temp].mutex);
    }
    return (NULL);
}

int time_in_ms(int value, t_data *data)
{
    struct timeval tp;
    
    gettimeofday(&tp, NULL);
    if (value)
    {
        printf("[%s] data.time : %d\n",__FUNCTION__, data->time);
        printf("[%s] tp.tv_sec : %d\n",__FUNCTION__, tp.tv_usec);
        return ((tp.tv_usec - data->time) / 1000);
    }
    else 
        return (tp.tv_usec);
}

int init(int argc, char **argv, t_data *data)
{
    if (!init_value(argc, argv, data))
        return (0);
    return (1);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    t_data data;

    // init(argc, argv, &data);
    data.time = time_in_ms(0, &data);
    printf("[%s] START\n",__FUNCTION__);
    printf("[%s] data.time : %d\n",__FUNCTION__, data.time);
    printf("[%s] actual time : %d\n",__FUNCTION__, time_in_ms(1, &data));
    printf("[%s] GO sleep\n",__FUNCTION__);
    accurate_msleep(100);
    printf("[%s] 1 STOP sleep\n",__FUNCTION__);
    printf("[%s] actual time : %d\n",__FUNCTION__, time_in_ms(1, &data));
    accurate_msleep(256);
    printf("[%s] 2 STOP sleep\n",__FUNCTION__);
    printf("[%s] actual time : %d\n",__FUNCTION__, time_in_ms(1, &data));
    accurate_msleep(322);
    printf("[%s] 3 STOP sleep\n",__FUNCTION__);
    printf("[%s] actual time : %d\n",__FUNCTION__, time_in_ms(1, &data));
    return 0;
    // // if (!init(argc, argv, &data))
    // //     return (0);
    // pthread_mutex_init(&data.mutex, NULL);
    // pthread_mutex_lock(&data.mutex);
    // printf("[%s] START\n",__FUNCTION__);
    
    // pthread_create(&thread1, NULL, fct, &data);
    // accurate_msleep(700);
    // printf("[%s] Created\n",__FUNCTION__);
    // pthread_mutex_unlock(&data.mutex);
    // pthread_join(thread1, NULL);
    // destroy(&data.mutex);
    
    return (0);
}