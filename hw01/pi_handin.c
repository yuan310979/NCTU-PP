#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

long long int number_in_circle = 0;
long long int number_of_tosses;
long number_of_cores;
pthread_mutex_t increment;

void* throwDart(void* args){
    unsigned int seed = time(NULL);
    int local_sum = 0;
    for(int i = 0; i < number_of_tosses / number_of_cores; i++){
        double x = (double) rand_r(&seed) / (RAND_MAX/2) - 1;
        double y  = (double) rand_r(&seed) / (RAND_MAX/2) - 1;
        if(x*x+y*y < 1.0f){
            local_sum++;
        }
    }
    pthread_mutex_lock(&increment);
    number_in_circle += local_sum;
    pthread_mutex_unlock(&increment);
    pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]){
    if(argc != 3){
        fprintf(stderr, "[Usage] ./pi.out <number_of_cores> <number_of_tosses>");
        exit(1);
    }

    // read command line arguments
    number_of_cores = strtol(argv[1], NULL, 10);
    number_of_tosses = strtol(argv[2], NULL, 10);

    // pthread initialization
    pthread_t *threads = (pthread_t*) malloc(sizeof(pthread_t) * number_of_tosses);
    pthread_mutex_init(&increment, NULL);

    for(int i = 0; i < number_of_cores; i++){
        pthread_create(&threads[i], NULL, throwDart, NULL);
    }

    for(int i = 0; i < number_of_cores; i++){
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&increment);
    printf("%lf\n", (double) number_in_circle / number_of_tosses * 4);
}
