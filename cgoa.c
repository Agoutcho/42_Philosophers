#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 100
#define DEFAULT_EAT_COUNT -1
#define DEFAULT_SLEEP_TIME 1000
#define DEFAULT_EAT_TIME 1000
#define DEFAULT_DIE_TIME 10000

// Data structure to represent a philosopher
typedef struct {
  int id;
  int eat_count;
  int sleep_time;
  int eat_time;
  int die_time;
  int left_fork;
  int right_fork;
} philosopher_t;

// Array of philosophers
philosopher_t philosophers[MAX_PHILOSOPHERS];

// Number of philosophers
int num_philosophers;

// Mutex to protect access to forks
pthread_mutex_t forks[MAX_PHILOSOPHERS];

// Mutex to protect access to the log
pthread_mutex_t log_mutex;

// Function that represents the behavior of a philosopher
void * philosopher_thread(void *arg) {
  philosopher_t *p = (philosopher_t*)arg;

  while (1) {
    // Wait some time before thinking
    usleep(p->sleep_time * 1000);

    // Try to get the left fork
    pthread_mutex_lock(&forks[p->left_fork]);
    printf("%ld %d has taken left fork\n", time(NULL), p->id);

    // Try to get the right fork
    pthread_mutex_lock(&forks[p->right_fork]);
    printf("%ld %d has taken right fork\n", time(NULL), p->id);

    // Eat for some time
    printf("%ld %d is eating\n", time(NULL), p->id);
    usleep(p->eat_time * 1000);
    p->eat_count++;

    // Release the forks
    pthread_mutex_unlock(&forks[p->left_fork]);
    pthread_mutex_unlock(&forks[p->right_fork]);
  }
}

int main(int argc, char *argv[]) {
  // Parse command line arguments
  if (argc < 4) {
    printf("Usage: %s number_of_philosophers time_to_die time_to_eat [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n", argv[0]);
    return 1;
  }
  num_philosophers = atoi(argv[1]);
  int die_time = atoi(argv[2]);
  int eat_time = atoi(argv[3]);
  int sleep_time = DEFAULT_SLEEP_TIME;
  int eat_count = DEFAULT_EAT_COUNT;
  if (argc > 4) {
    sleep_time = atoi(argv[4]);
  }
  if (argc > 5) {
    eat_count = atoi(argv[5
