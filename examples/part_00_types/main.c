#include <unistd.h>
#include <time.h>
#include <stdio.h>

#define SECONDS_TO_NANOSECONDS 1000000000

int main()
{
    struct timespec t1;
    clock_gettime( CLOCK_MONOTONIC, &t1 );

    sleep( 100 );

    struct timespec t2;
    clock_gettime( CLOCK_MONOTONIC, &t2 );

    float seconds = ( t2.tv_sec - t1.tv_sec ) + ( float )( t2.tv_nsec - t1.tv_nsec ) / SECONDS_TO_NANOSECONDS;

    printf( "%f\n", seconds );
}