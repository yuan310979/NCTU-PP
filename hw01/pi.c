#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double distance(double x, double y){
    return x*x+y*y;
}

int main(int argc, char* argv[]){
    int number_in_circle = 0;
    int toss;

    long number_of_tosses = strtol(argv[1], NULL, 10);

    for(toss = 0; toss < number_of_tosses; toss++){
        double x = (double) rand() / (double)(RAND_MAX/2) - 1;
        double y  = (double) rand() / (double)(RAND_MAX/2) - 1;
        if(distance(x,y) < 1)
            number_in_circle++;
    }

    printf("PI: %lf", (double) number_in_circle / number_of_tosses * 4);
}
