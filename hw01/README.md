Programming Assignment I: Pthreads Programming
==============================================

About
-----
This project is the first coding assignment by NCTU Parallel Programming, lectured by Prof. Yi-Ping You. Written by c to implement Monte Carlo Method to estimate pi value. Also, this program is accelerated by Pthread Library.

Quick Start
-----------
This project is compiled by makefile. 
``` sh
make
```

There are two arguments here in this program, which is the number of using cores and the number of attemps in monte carlo method.
``` sh
./pi.out <number_of_cores> <number_of_throws>
```
ex:
``` sh
./pi.out 4 100000
```

Further
-------
#### Why we use rand_r() instead of rand() in random number generator?
rand() and rand_r() are almost the same. But when you dig deep into the source code. You will find that, in rand() function, it will call rand_r() as a random number generator. Furthermore, it not only rely on rand_r() but also has a mutex lock on access rand_r() value. So if you use rand() function as our program's random number generator, since this estimator use pthread as parallel library, each thread will be block while generating random number. It will cause a severe problem that using 2 cores is faster than 4 cores in our testing.
arogramming Assignment I: Pthreads Programming

