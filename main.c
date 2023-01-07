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


struct s_dataa{
        int is_dead;
        int time;
};

void accurate_msleep(unsigned long long usec)
{
    struct timeval tp;
    long int timee;

    // printf("[%s] Debut msleep\n",__FUNCTION__);
    gettimeofday(&tp, NULL);
    timee = tp.tv_usec;
    while (timee + (long int)(usec * 1000) > 1000000)
    {
        gettimeofday(&tp, NULL);
        timee = tp.tv_usec;
    }
    while (tp.tv_usec - timee < (long int)(usec * 1000))
    {
        gettimeofday(&tp, NULL);
        usleep(10);
    }
}

void accurate_usleep(unsigned long long usec)
{
    struct timeval tp;
    long int timee;
    
    // printf("[%s] Debut usleep\n",__FUNCTION__);
    gettimeofday(&tp, NULL);
    timee = tp.tv_usec;
    while (timee + (long int)(usec) > 1000000)
    {
        gettimeofday(&tp, NULL);
        timee = tp.tv_usec;
    }
    while (tp.tv_usec - timee < (long int)(usec))
    {
        gettimeofday(&tp, NULL);
        usleep(10);
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
    t_philo *philo;
    int temp;

    philo = (t_philo *)phil;
    temp = (philo->id + 1) % philo->data->nbr_of_philo;
    accurate_usleep((philo->data->nbr_of_philo + 1) / (philo->id + 1));
    while (1)
    {
        if (!pthread_mutex_lock(&philo->mutex) && !pthread_mutex_lock(&philo->data->philo[temp].mutex))
        {
            printf("%d Philosopher %d has taken a fork\n", time_in_ms(1, philo->time), philo->id + 1);
            accurate_msleep(philo->data->time_to_eat);
            pthread_mutex_unlock(&philo->mutex);
            pthread_mutex_unlock(&philo->data->philo[temp].mutex);
            printf("%d Philosopher %d is sleeping\n", time_in_ms(1, philo->time), philo->id + 1);
        }
        accurate_msleep(philo->data->time_to_sleep);
    }
    return (NULL);
}

int time_in_ms(int value, int time)
{
    struct timeval tp;
    
    gettimeofday(&tp, NULL);
    if (value)
    {
        // printf("[%s] data.time : %d\n",__FUNCTION__, time);
        // printf("[%s] tp.tv_sec : %ld\n",__FUNCTION__, tp.tv_usec);
        return ((tp.tv_usec - time) / 1000);
    }
    else 
        return (tp.tv_usec);
}

int init(int argc, char **argv, t_data *data)
{
    int i;

    if (!parse_value(argc, argv, data))
        return (0);
    data->philo = (t_philo *)malloc(sizeof(t_philo) * data->nbr_of_philo);
    if (!data->philo )
        return (0);
    i = 0;
    data->time  = time_in_ms(0, 0);
    while (i < data->nbr_of_philo)
    {
        // printf("[%s] Début while i : %d\n",__FUNCTION__, i);
        data->philo[i].time  = time_in_ms(0, 0);
        data->philo[i].id = i;
        data->philo[i].last_time_eat = 0;
        data->philo[i].nbr_eat = 0;
        data->philo[i].data = data;
        pthread_mutex_init(&data->philo[i].mutex, NULL);
        pthread_mutex_lock(&data->philo[i].mutex);
        pthread_create(&data->philo[i].thread, NULL, ft_philo, &data->philo[i]);
        pthread_mutex_unlock(&data->philo[i].mutex);
        // printf("[%s] Fin while i : %d\n",__FUNCTION__, i);
        i++;
    }
    return (1);
}

// Le temps le plus grand pour la boucle du time initial
int main(int argc, char **argv)
{
    t_data data;
    int i;

    printf("[%s] START INIT\n",__FUNCTION__);
    if (!init(argc, argv, &data))
        return (0);
    printf("[%s] INIT DONE\n",__FUNCTION__);

    i = 0;
    while (1)
    {
        pthread_join(data.philo[i % data.nbr_of_philo].thread, NULL);
        i++;
    }
    printf("[%s] MAIN DONE\n",__FUNCTION__);
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