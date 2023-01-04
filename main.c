/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:10:31 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/04 22:45:41 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <string.h>

struct s_dataa{
        int is_dead;
        int time;
};

void accurate_usleep(int usec)
{
    struct timeval tp;
    int time;
    gettimeofday(&tp, NULL);
    time = tp.tv_usec;
    while (tp.tv_usec - time < usec)
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
    //     accurate_usleep(15);
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

int init(int argc, char **argv, t_data *data)
{
    if (!init_value(argc, argv, data))
        return (0);
    return (1);
}

void destroy(t_data *data)
{
    pthread_mutex_destroy(&data->mutex);
}

int main()
{
    t_data data;
    pthread_t thread1;
    
    // if (!init(argc, argv, &data))
    //     return (0);
    pthread_mutex_init(&data.mutex, NULL);
    pthread_mutex_lock(&data.mutex);
    printf("[%s] START\n",__FUNCTION__);
    
    pthread_create(&thread1, NULL, fct, &data);
    accurate_usleep(700);
    printf("[%s] Created\n",__FUNCTION__);
    pthread_mutex_unlock(&data.mutex);
    pthread_join(thread1, NULL);
    destroy(&data.mutex);
    // struct s_dataa data;
    // pthread_t thread1;
    // struct timeval tp;
    // data.is_dead = 0;
    // printf("\n[%s] GO Thread\n",__FUNCTION__);
    // gettimeofday(&tp, NULL);
    // data.time = tp.tv_usec;
    // gettimeofday(&tp, NULL);
    // printf("[%s] Before Create time : %d\n",__FUNCTION__,  tp.tv_usec - data.time);
    // gettimeofday(&tp, NULL);
    // printf("[%s] After Create time : %d\n",__FUNCTION__,  tp.tv_usec - data.time);
    // accurate_usleep(150);
    // data.is_dead = 1;
    // gettimeofday(&tp, NULL);
    // printf("[%s] Finish time : %d\n",__FUNCTION__,  tp.tv_usec - data.time);
    // pthread_join(thread1, NULL);
    
    return (0);
}