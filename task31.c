#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 2

int counter = 0;
sem_t semaphore;

void* increment(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        sem_wait(&semaphore); // Wait for the semaphore
        counter++;
        sem_post(&semaphore); // Signal that we're done
    }
    return NULL;
}

void* decrement(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        sem_wait(&semaphore); // Wait for the semaphore
        counter--;
        sem_post(&semaphore); // Signal that we're done
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize the semaphore with an initial value of 1
    sem_init(&semaphore, 0, 1);

    // Create two threads
    if (pthread_create(&threads[0], NULL, increment, NULL) != 0 ||
        pthread_create(&threads[1], NULL, decrement, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }

    // Wait for both threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the semaphore
    sem_destroy(&semaphore);

    printf("Counter: %d\n", counter);

    return 0;
}
