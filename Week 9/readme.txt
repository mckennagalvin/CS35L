McKenna Galvin
604290168
readme.txt
CS 35L week 9

This project involved modifying the ray tracer code so that it was
multithreaded. In order to do this, I had to create a new function
that would perform all of the tasks that the threads do, and move
some of the variables into the global scope so they could be accessed
by my new function.

One of the issues I ran into was figuring out how to store the new
values of all of the pixels after they had been processed by the ray
tracer to reflect new values. I decided to create my own struct that
would store the Red, Green, and Blue values of each pixel, and to
create an array of pointers to such structs so that I could easily
print out all of the pixels at the end of the main function.

Another problem I ran into was dealing with all of the variables that
were used in the thread function. These needed to be declared as
global variables in order to avoid compiler errors, since the
variables need to be declared before they are used.

Judging by the results of the time command, multithreading
significantly improves performace!

1 thread:
real    0m46.531s
user    0m46.533s
sys     0m0.001s

2 threads:
real    0m24.118s
user    0m47.305s
sys     0m0.003s

4 threads:
real    0m15.675s
user    0m46.709s
sys     0m0.003s

8 threads:
real    0m10.071s
user    0m48.513s
sys     0m0.003s

The time saved isn't exactly proportional to the number of threads
used, because there are some commands that are performed before the
threads are created that take up more time. Nevertheless, creating
threads saves a lot of time!
