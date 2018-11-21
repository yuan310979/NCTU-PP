#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define PI 3.1415926535

int main(int argc, char **argv) 
{
    long long i, num_intervals;
    int my_rank, p;
    double rect_width, area, sum, x_middle; 

    /* start up MPI */
    MPI_Init(&argc, &argv);

    /* find out process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* find out number of process */
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    sscanf(argv[1],"%llu",&num_intervals);

    rect_width = PI / num_intervals;

    sum = 0;
    double local_sum = 0;

    long long start = (long long)(num_intervals * (float)(my_rank)/p) + 1;
    long long end = (long long)(num_intervals * (float)(my_rank+1)/p) + 1;

    for(i = start; i < end; i++){
        x_middle = (i - 0.5) * rect_width;
        area = sin(x_middle) * rect_width;
        local_sum = local_sum + area;
    }

    MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(my_rank == 0){
        printf("The total area is: %f\n", (float)sum);
    }

    MPI_Finalize();

    return 0;
}   
