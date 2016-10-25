#define _GNU_SOURCE
#define __USE_GNU

#include <cstdlib>                                      // rand
#include <cerrno>                                       // errno
#include <cstdio>                                       // perror
#include <cstdint>                                      // uintptr_t
using namespace std;
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sched.h>


//#define RECURSIVE
//#define LOCKING

#ifdef RECURSIVE
#define TIMES 10000
unsigned int fibr( int n ) {
   if ( n == 0 ) {
        return 0;
   } else if ( n == 1 ) {
        return 1;
   } else {
        return fibr( n - 1 ) + fibr( n - 2 );
   } // if
} // fib
#else
// tail recusive fibonacci numbers
#define TIMES 10000000
unsigned long int fibtr( unsigned long int i, unsigned long int a, unsigned long int b ) {
   if ( i == 0 ) return a;
   return fibtr( i - 1, b, a + b );
} // fibtr
#endif // RECURSIVE

pthread_mutex_t locks[4];

void fib() {
   const unsigned long int
        F = rand() % 6 + 26,                           // random between 25..30 inclusive
        L = rand() % 4;                                // random between 0..3

#ifdef LOCKING
   pthread_mutex_lock( &locks[L] );                    // acquire random lock
#endif // LOCKING

#ifdef RECURSIVE
   fibr( F );
#else
   fibtr( F, 0, 1 );                                   // compute random fibonacci number
#endif // RECURSIVE

#ifdef LOCKING
   pthread_mutex_unlock( &locks[L] );                  // release random lock
#endif // LOCKING
} // fib

#define WORK for ( int i = 0; i < TIMES; i += 1 ) fib()
void * worker( void * arg ) {
   WORK;
}; // worker

void affinity( pthread_t thread, int cpu ) {
   cpu_set_t mask;

   CPU_ZERO( &mask );
   CPU_SET( cpu, &mask );
   int rc = pthread_setaffinity_np( thread, sizeof(cpu_set_t), &mask );
   if ( rc != 0 ) {
        errno = rc;
        perror( "setaffinity" );
        abort();
   } // if
} // affinity

#define CPU_OFFSET 16
#define THREADS 4 - 1

int main() {
   affinity( pthread_self(), CPU_OFFSET );

   pthread_t workers[THREADS];
   for ( uintptr_t tid = 0; tid < THREADS; tid += 1 ) {
        if ( pthread_create( &workers[tid], NULL, worker, (void *)(tid + 1) ) < 0 ) {
            abort();
        } // if
        affinity( workers[tid], tid + CPU_OFFSET + 1 );
   } // for

   WORK;

   for ( int tid = 0; tid < THREADS; tid += 1 ) {
        if ( pthread_join( workers[tid], NULL ) < 0 ) {
            abort();
        } // if
   } // for
} // main

// Local Variables: //
// compile-command: "g++-6 -g -O2 -std=c++11 fib2.cc -lpthread" //
// End: //
