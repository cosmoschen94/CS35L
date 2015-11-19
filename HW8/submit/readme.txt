1. After learning the fundamentals of multithreading during lecture,
I first found it difficult to use those knowledge to a real application.

2. First I include <pthread.h> into the main.c. Then I read through the
main.c file and tried to understand where I can apply multithreading.
I got lost when I read through it at the first time. But at the second
time, I found that in the main function, there were four nested loops.
Then I realized I could do something here.

3. Since one ray per pixel, we can multithread the program such that
each thread works on different sets of the pixels. Therefore, I
partitioned the nested loops into different parts. If there are 2 threads,
one thread will work on the odd cases and the other one will work on the
even cases. If there are n threads, we can then partition outest loop into
n parts.

4. Then I picked out global shared variables and invited new local variables
in the main function as well as the thread routine function.

5. It is worth mentioning that I allocated an array of int named partition
to make the partition of the nested loop possible. For every thread, based
on the partition value, it is going to start at different value into the loop.
And by incrementing based on the value of nthreads, a global shared variable,
the program can now run on multithreads without worrying about race condition.

6. After finishing modification to main.c, I then checked Makefile and made
some changes in order for the make clean check to work properly.

7. After my implementatioan of SRT, the program can be multithreaded.
As we can see below, the performance is enhanced significantly when
more threads are created.

time ./srt 1-test.ppm >1-test.ppm.tmp
mv 1-test.ppm.tmp 1-test.ppm
real		  0m51.410s
user		  0m51.399s
sys		  0m0.002s

time ./srt 2-test.ppm >2-test.ppm.tmp
mv 2-test.ppm.tmp 2-test.ppm
real		  0m26.602s
user		  0m52.683s
sys		  0m0.000s

time ./srt 4-test.ppm >4-test.ppm.tmp
mv 4-test.ppm.tmp 4-test.ppm
real		  0m13.967s
user		  0m54.936s
sys		  0m0.015s

time ./srt 8-test.ppm >8-test.ppm.tmp
mv 8-test.ppm.tmp 8-test.ppm
real		  0m7.262s
user		  0m55.908s
sys		  0m0.002s

8. I used XQuartz to check the image
$ ssh -X chens@lnxsrv.seas.ucla.edu
$ which gimp
$ gimp 1-test.ppm

Output image as expected.


