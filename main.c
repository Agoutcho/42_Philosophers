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

void accurate_msleep(unsigned long long msec)
{
    long actual_time;

    actual_time = time_in_ms(0, 0);
    while (time_in_ms(0, 0) - actual_time < (long int)(msec))
    {
        // printf("[%s] ms : %ld\n",__FUNCTION__, time_in_ms(0, 0));
        // printf("[%s] time_in_ms(0, 0) - actual_time : %ld\n",__FUNCTION__, time_in_ms(0, 0) - actual_time);
        // printf("[%s] msec * 1000 : %ld\n",__FUNCTION__, (long int)(msec));
        usleep(100);
    }
}

void accurate_usleep(unsigned long long usec)
{
    long actual_time;

    actual_time = time_in_us(0, 0);
    while (time_in_us(0, 0) - actual_time < (long int)(usec))
    {
        // printf("[%s] ms : %ld\n",__FUNCTION__, time_in_ms(0, 0));
        // printf("[%s] time_in_ms(0, 0) - actual_time : %ld\n",__FUNCTION__, time_in_ms(0, 0) - actual_time);
        // printf("[%s] msec * 1000 : %ld\n",__FUNCTION__, (long int)(msec));
        usleep(10);
    }
}

// void accurate_usleep(unsigned long long usec)
// {
//     struct timeval tp;
//     long int timee;
    
//     // printf("[%s] Debut usleep\n",__FUNCTION__);
//     gettimeofday(&tp, NULL);
//     timee = tp.tv_usec;
//     while (timee + (long int)(usec) > 1000000)
//     {
//         gettimeofday(&tp, NULL);
//         timee = tp.tv_usec;
//     }
//     while (tp.tv_usec - timee < (long int)(usec))
//     {
//         gettimeofday(&tp, NULL);
//         usleep(10);
//     }
// }

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
    int sleep;

    philo = (t_philo *)phil;
    temp = (philo->id + 1) % philo->data->nbr_of_philo;
    sleep = philo->data->t_to_sleep;
    accurate_usleep(100);
    while (1)
    {
        printf("%ld Philosopher %d is thinking\n", time_in_ms(1, philo->time), philo->id + 1);
        if (!pthread_mutex_lock(&philo->mutex) && !pthread_mutex_lock(&philo->data->philo[temp].mutex))
        {
            philo->last_time_eat = time_in_ms(0, 0);
            printf("%ld Philosopher %d has taken a fork\n", time_in_ms(1, philo->time), philo->id + 1);
            printf("%ld Philosopher %d has taken a fork\n", time_in_ms(1, philo->time), philo->id + 1);
            printf("%ld Philosopher %d is eating\n", time_in_ms(1, philo->time), philo->id + 1);
            accurate_msleep(philo->data->t_to_eat);
            // printf("%ld Philosopher %d will put back\n", time_in_ms(1, philo->time), philo->id + 1);
            pthread_mutex_unlock(&philo->mutex);
            pthread_mutex_unlock(&philo->data->philo[temp].mutex);
            // printf("%ld Philosopher %d is sleeping\n", time_in_ms(1, philo->time), philo->id + 1);
        }
        if (time_in_ms(0, 0) - philo->last_time_eat >= philo->data->t_to_die)
        {
            printf("%ld Philosopher %d died\n", time_in_ms(1, philo->time), philo->id + 1);
            philo->state = e_DIED;
            break;
        }
        else if (philo->data->t_to_sleep >= philo->data->t_to_die - philo->data->t_to_eat)
            sleep = philo->data->t_to_die - philo->data->t_to_eat;
        else 
            sleep = philo->data->t_to_sleep;
        printf("%ld Philosopher %d is sleeping\n", time_in_ms(1, philo->time), philo->id + 1);
        accurate_msleep(sleep);
        if (time_in_ms(0, 0) - philo->last_time_eat >= philo->data->t_to_die)
        {
            printf("%ld Philosopher %d died\n", time_in_ms(1, philo->time), philo->id + 1);
            philo->state = e_DIED;
            break;
        }
        accurate_usleep(10);
    }
    return (NULL);
}

long time_in_us(int value, long time)
{
    struct timeval tp;
    long us;

    gettimeofday(&tp, NULL);
    if (value)
    {
        // printf("[%s] data.time : %ld\n",__FUNCTION__, time);
        // printf("[%s] tp.tv_sec : %ld\n",__FUNCTION__, tp.tv_usec);
        us = tp.tv_sec;
	    us += tp.tv_usec;
        return (us - time);
    }
    else
    {
        us = tp.tv_sec;
	    us += tp.tv_usec;
        // printf("[%s] us : %ld\n",__FUNCTION__, us);
        return (us);
    }
}

long time_in_ms(int value, long time)
{
    struct timeval tp;
    long ms;

    gettimeofday(&tp, NULL);
    if (value)
    {
        // printf("[%s] data.time : %ld\n",__FUNCTION__, time);
        // printf("[%s] tp.tv_sec : %ld\n",__FUNCTION__, tp.tv_usec);
        ms = tp.tv_sec * 1000;
	    ms += tp.tv_usec / 1000;
        return (ms - time);
    }
    else
    { 
        ms = tp.tv_sec * 1000;
	    ms += tp.tv_usec / 1000;
        // printf("[%s] ms : %ld\n",__FUNCTION__, ms);
        return (ms);
    }
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
    printf("[%s] time : %ld\n",__FUNCTION__, data->time);
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

int check_death(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nbr_of_philo)
    {
        if (data->philo[i % data->nbr_of_philo].state == e_DIED)
        {
            return (1);
        }
        i++;
    }
    return (0);
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

    while (!check_death(&data))
    {}
    i = 0;
    while (i < data.nbr_of_philo)
    {
        pthread_detach(data.philo[i % data.nbr_of_philo].thread);
        i++;
    }
    // while (1)
    // {
    //     pthread_join(data.philo[i % data.nbr_of_philo].thread, NULL);
    //     i++;
    // }
    // printf("[%s] MAIN DONE\n",__FUNCTION__);
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