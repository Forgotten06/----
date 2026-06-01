#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define ITERATIONS 1000000
#define ALLOC_SIZE 64

void* work(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        void* p = malloc(ALLOC_SIZE);
        if (p) {
            free(p);
        }
    }
    return NULL;
}

void run_test(int num_threads) {
    pthread_t threads[num_threads];
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, work, NULL);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Threads: %d, Time: %.4f seconds\n", num_threads, time_taken);
}

int main() {
    int thread_counts[] = {1, 2, 4, 8};
    
    for (int i = 0; i < 4; i++) {
        run_test(thread_counts[i]);
    }

    return 0;
}