/*One thread prints "SUNBEAM" continuously, and other thread prints "INFOTECH" continhously. Only one should print at a time starting with "SUNBEAM". Hint: using semaphores*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Two semaphores to control the alternating access
sem_t sem_sunbeam;
sem_t sem_infotech;

// Thread function for printing "SUNBEAM"
void *print_sunbeam(void *arg) {
    while (1) {
        // Wait for the "SUNBEAM" semaphore
        sem_wait(&sem_sunbeam);
        
        printf("SUNBEAM ");
        fflush(stdout); // Ensure output is printed immediately
        
        // Signal the "INFOTECH" semaphore
        sem_post(&sem_infotech);
    }
    return NULL;
}

// Thread function for printing "INFOTECH"
void *print_infotech(void *arg) {
    while (1) {
        // Wait for the "INFOTECH" semaphore
        sem_wait(&sem_infotech);
        
        printf("INFOTECH\n");
        fflush(stdout); // Ensure output is printed immediately
        
        // Signal the "SUNBEAM" semaphore
        sem_post(&sem_sunbeam);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialize semaphores
    // sem_sunbeam is initialized to 1 so that the "SUNBEAM" thread starts first.
    // sem_infotech is initialized to 0 so that the "INFOTECH" thread waits.
    sem_init(&sem_sunbeam, 0, 1);
    sem_init(&sem_infotech, 0, 0);

    // Create the two threads
    pthread_create(&thread1, NULL, print_sunbeam, NULL);
    pthread_create(&thread2, NULL, print_infotech, NULL);

    // Keep the main thread alive for a few seconds to let the other threads run
    sleep(10);

    // Cancel and join the threads
    pthread_cancel(thread1);
    pthread_cancel(thread2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    // Destroy semaphores
    sem_destroy(&sem_sunbeam);
    sem_destroy(&sem_infotech);

    return 0;
}

