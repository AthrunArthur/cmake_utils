#!/bin/tcsh

echo "tail recursion, no locking"
g++-6 -g -O2 -std=c++11 fib2.cc -lpthread -o t
repeat 5 /usr/local/bin/gtime -f "%U user %S system %E real" /Users/xuepengfan/projects/cs/t
echo "tail recursion, locking"
g++-6 -g -O2 -std=c++11 fib2.cc -lpthread -DLOCKING
repeat 5 /usr/local/bin/gtime -f "%U user %S system %E real" /Users/xuepengfan/projects/cs/t
echo "recursion, no locking"
g++-6 -g -O2 -std=c++11 fib2.cc -lpthread -DRECURSIVE
repeat 5 /usr/local/bin/gtime -f "%U user %S system %E real" /Users/xuepengfan/projects/cs/a.out
echo "recursion, locking"
g++-6 -g -O2 -std=c++11 fib2.cc -lpthread -DRECURSIVE -DLOCKING
repeat 5 /usr/local/bin/gtime -f "%U user %S system %E real" /Users/xuepengfan/projects/cs/a.out
