#include <unistd.h>
#include <time.h>
#include <stdio.h>

#define SECONDS_TO_NANOSECONDS 1000000000
#define SECONDS_TO_MICROSECONDS 1000000
#define SECONDS_TO_MILLISECONDS 1000

int main()
{
    struct timespec t1;
    clock_gettime( CLOCK_MONOTONIC, &t1 );

    usleep( 100  * SECONDS_TO_MICROSECONDS / SECONDS_TO_MILLISECONDS );

    struct timespec t2;
    clock_gettime( CLOCK_MONOTONIC, &t2 );

    printf("%ld %ld %ld %ld\n", t2.tv_sec, t1.tv_sec , t2.tv_nsec, t1.tv_nsec  );
    float seconds = ( t2.tv_sec - t1.tv_sec ) + ( float )( t2.tv_nsec - t1.tv_nsec ) / SECONDS_TO_NANOSECONDS;

    printf( "%f\n", seconds );
}