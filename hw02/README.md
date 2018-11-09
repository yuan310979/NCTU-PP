Programming Assignment II: OpenMP Programming 
==============================================

![Execution](https://imgur.com/eAVno4O.png)

About
-----
This project is the second coding assignment which aim to parallel Conjugate Gradient Descend Algorithm by openmp library. 

Quick Start
-----------
This project is compiled by makefile.
```sh
make
```

Run the program
```sh
./bin/cg
```

If you want to assign your program process to your CPU core, you can do
```sh
taskset -c 0,1,2,3 ./bin/cg
```
this command will assign your process to your CPU core #0 #1 #2 #3

Further
=======
#### Why I add all for loop into workaround construct but get a lower performance?
Since parallel programming will have overhead, especially when you assign parallel construct to a for loop which do not habe so much work. Therefore, you should find some hard loading paragraph in your code, do parallization, then you will get the correct boost to your result.
