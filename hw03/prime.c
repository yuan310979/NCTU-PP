#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

//#define MAX_SIZE 1000000000
#define MAX_SIZE 10

int *isPrime;

void gen_prime_table(long long int size){
    for(int i = 0; i < size; i++)
        isPrime[i] = 1;
    for(int i = 2; i < size; i+=2){
        isPrime[i] = 0;
    }
    for(int i = 3; i < size; i+=2){
        if(isPrime[i]){
            for(int j = 2; i * j <= size; j++){
                isPrime[i*j] = 0;
            }
        }
    }
}

int isprime(int n) {
    int i,squareroot;
    if (n>10) {
        squareroot = (int) sqrt(n);
        for (i=3; i<=squareroot; i=i+2)
            if ((n%i)==0)
                return 0;
        return 1;
    }
    else
        return 0;
}

int main(int argc, char *argv[])
{
    int pc=0,       /* local prime counter */
        foundone,   /* most recent prime found */
        p,          /* number of process */
        my_rank;    /* rank of process */ 
    long long int n, limit, arr_size;


    /* start up MPI */
    MPI_Init(&argc, &argv);

    /* find out process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* find out number of process */
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    int *pc_recv;
    pc_recv = (int*) malloc(sizeof(int) * p);
    sscanf(argv[1],"%llu",&limit);	

    if(my_rank == 0){
        /**
         * Master
         * - generate prime table
         * - calculate the prime number under MAX_SIZE(use isPrime array)
         */
        arr_size = (limit+1 < MAX_SIZE) ? limit+1 : MAX_SIZE;
        /* dynamic allocate the prime table size */
        isPrime = (int*) malloc(sizeof(int) * (arr_size));
        gen_prime_table(arr_size);

        printf("Starting. Numbers to be scanned= %lld\n",limit);

        if(arr_size-1 >= 2)  pc++;
        for(n=3; n<=arr_size-1; n=n+2) {
            if (isPrime[n]) {
                pc++;
                foundone = n;
            }			
        }

        long long int recv[2];
        MPI_Status status;
        for(int i = 1; i < p; i++){
           MPI_Recv(recv, 2, MPI_UNSIGNED_LONG, i, 0, MPI_COMM_WORLD, &status); 
           pc += recv[0];
           foundone = (recv[1] > foundone) ? recv[1] : foundone;
        }

        printf("Done. Largest prime is %d Total primes %d\n",foundone,pc);
    }
    else{
        /**
         * Slave
         * - calculate the prime number over the MAX_SIZE(use isprime())
         */
        long long int total_slave,
            num_slave,
            from,
            to;

        if(limit >= MAX_SIZE){
            total_slave = p - 1;
            num_slave = my_rank - 1;
            from = MAX_SIZE + (limit-MAX_SIZE+1) * (num_slave) /total_slave;
            to = MAX_SIZE + (limit-MAX_SIZE+1) * (num_slave+1) / total_slave;
            // pass even number
            if(from % 2 == 0) from++;

            // execute prime check
            for(int n = from; n < to; n+=2){
                if(isprime(n)){
                    pc++;
                    foundone = n;
                } 
            }
        }
        long long int send[2] = {pc, foundone};
        MPI_Send(send, 2, MPI_UNSIGNED_LONG, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
} 
