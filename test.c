#include "philosopher.h"
#include <string.h>

int timeo;
void ft_philo(pthread_mutex_t *mutex);

void accurate_msleep(unsigned long long usec)
{
    struct timeval tp;
    long int timee;
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

void *fct(void *truc)
{
    struct timeval tp;
    
    pthread_mutex_t *mutex;
    printf("[%s] | Je rentre dans le thread\n",__FUNCTION__);
    gettimeofday(&tp, NULL);
    printf("[%s] | tp.tv_usec : %ld\n",__FUNCTION__, tp.tv_usec - timeo);
    ft_philo((pthread_mutex_t *)truc);
    printf("[%s] | Je sors du thread\n",__FUNCTION__);
}

void ft_philo(pthread_mutex_t *mutex)
{
    printf("[%s] | Je rentre dans la fonction\n",__FUNCTION__);
    if (!pthread_mutex_lock(mutex))
    {
        printf("[%s] | J'ai eu le mutex\n",__FUNCTION__);
        printf("[%s] | On rend le mutex\n",__FUNCTION__);
        pthread_mutex_unlock(mutex);
        printf("[%s] | On a rendu le mutex\n",__FUNCTION__);
    }
    printf("[%s] | Je sors de la fonction\n",__FUNCTION__);
}

int main(int argc, char **argv)
{
    pthread_mutex_t mutex;
    pthread_t thread;
    struct timeval tp;

    gettimeofday(&tp, NULL);
    timeo = tp.tv_usec;
    pthread_mutex_init(&mutex, NULL);
    if (!pthread_mutex_lock(&mutex))
    {
        printf("[%s] | J'ai eu le mutex\n",__FUNCTION__);
        pthread_create(&thread, NULL, fct, &mutex);
        printf("[%s] | Thread crée\n",__FUNCTION__);
        accurate_msleep(100);
        printf("[%s] | On a attendu 100ms\n",__FUNCTION__);
        gettimeofday(&tp, NULL);
        printf("[%s] | tp.tv_usec : %ld\n",__FUNCTION__, (tp.tv_usec - timeo) / 1000);
        printf("[%s] | On destroy le mutex\n",__FUNCTION__);
        // pthread_mutex_destroy(&mutex);
        // printf("[%s] | On rend le mutex\n",__FUNCTION__);
        // pthread_mutex_unlock(&mutex);
        // printf("[%s] | On a rendu le mutex\n",__FUNCTION__);
    }
    printf("[%s] | On attend la fin du thread\n",__FUNCTION__);
    pthread_detach(thread);
    printf("[%s] | FIN THREAD JOIN\n",__FUNCTION__);
    return (0);
}