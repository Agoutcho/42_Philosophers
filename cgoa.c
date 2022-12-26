#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define UNUSED(x) (void)(x)

typedef enum {
    THINKING,
    EATING,
    SLEEPING,
    DEAD
} philosopher_state_t;

typedef struct {
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int id;
    int num_times_eaten;
    philosopher_state_t state;
    unsigned int time_to_die;
    unsigned int time_to_eat;
    unsigned int time_to_sleep;
    unsigned int num_times_to_eat;
} philosopher_t;

void *philosopher_thread_func(void *arg)
{
    philosopher_t *philosopher = (philosopher_t*)arg;
    unsigned int time_since_last_meal = 0;
    int ret;
    struct timespec ts;

    while (1) {
        philosopher->state = THINKING;
        printf("%u Philosopher %d is thinking\n", (unsigned int)time(NULL), philosopher->id);

        ret = pthread_mutex_trylock(philosopher->left_fork);
        if (ret != 0) {
            continue;
        }

        ret = pthread_mutex_trylock(philosopher->right_fork);
        if (ret != 0) {
            pthread_mutex_unlock(philosopher->left_fork);
            continue;
        }

        philosopher->state = EATING;
        printf("%u Philosopher %d is eating\n", (unsigned int)time(NULL), philosopher->id);

        ts.tv_sec = philosopher->time_to_eat / 1000;
        ts.tv_nsec = (philosopher->time_to_eat % 1000) * 1000000;
        nanosleep(&ts, NULL);

        pthread_mutex_unlock(philosopher->left_fork);
        pthread_mutex_unlock(philosopher->right_fork);

        philosopher->num_times_eaten++;
        time_since_last_meal = 0;

        if (philosopher->num_times_to_eat > 0 && philosopher->num_times_eaten >= philosopher->num_times_to_eat) {
            break;
        }

        philosopher->state = SLEEPING;
        printf("%u Philosopher %d is sleeping\n", (unsigned int)time(NULL), philosopher->id);

        ts.tv_sec = philosopher->time_to_sleep / 1000;
        ts.tv_nsec = (philosopher->time_to_sleep % 1000) * 1000000;
        nanosleep(&ts, NULL);

        time_since_last_meal += philosopher->time_to_sleep;
        if (time_since_last_meal >= philosopher->time_to_die) {
            philosopher->state = DEAD;
            printf("%u Philosopher %d died\n", (unsigned int)time(NULL), philosopher->id);
            break;
        }
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    int num_philosophers;
    unsigned int time_to_die;
    unsigned int time_to_eat;
    unsigned int time_to_sleep;
    unsigned int num_times_to_eat = 0;
    pthread_mutex_t forks[100];
    philosopher_t philosophers[100];

    if (argc < 5 || argc > 6) {
        fprintf(stderr, "Usage: %s num_philosophers time_to_die time_to_eat time_to_sleep [num_times_to_eat]\n", argv[0]);
        return 1;
    }

    num_philosophers = atoi(argv[1]);
    time_to_die = atoi(argv[2]);
    time_to_eat = atoi(argv[3]);
    time_to_sleep = atoi(argv[4]);
    if (argc == 6) {
        num_times_to_eat = atoi(argv[5]);
    }

    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < num_philosophers; i++) {
        philosophers[i].left_fork = &forks[i];
        philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];
        philosophers[i].id = i + 1;
        philosophers[i].num_times_eaten = 0;
        philosophers[i].time_to_die = time_to_die;
        philosophers[i].time_to_eat = time_to_eat;
        philosophers[i].time_to_sleep = time_to_sleep;
        philosophers[i].num_times_to_eat = num_times_to_eat;
        pthread_create(&philosophers[i].thread, NULL, philosopher_thread_func, &philosophers[i]);
    }

    for (int i = 0; i < num_philosophers; i++) {
        pthread_join(philosophers[i].thread, NULL);
    }

    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
