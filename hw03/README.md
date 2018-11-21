Programming Assignment III: MPI Programming 
==============================================
# Problem 1 - Prime
![Execution Prime](https://imgur.com/gItt7pZ.png)

# Problem 2 - Integrate
![Execution Integrate](https://imgur.com/8q2SYn2.png)

About
-----
The purpose of this assignment is aimed to familiar with MPI library.
We will use MPI library to do CPU level parallel programming on different machine simultaneously.

Quick Start
-----------
## Environment Setup
- install MPI library and add it's directory of binary to PATH varaible
- build your hostfile which contains all the host you can have
- setup ssh key and add yours hosts to authorized host to prevent logging with password(optional)

This project is compiled by makefile.
```sh
make
```

Run the program
```sh
mpiexec -n <# of CPUcore> -hostfile hostfile --map-by node bin/prime 10000000
```
```sh
mpiexec -n <# of CPUcore> -hostfile hostfile --map-by node bin/integrate 10000000
```

Futhermore
==========
## Prime
In order to improve the performance, I rewrite the prime program based on Sieve Algorithm.<br>
Reference: https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
