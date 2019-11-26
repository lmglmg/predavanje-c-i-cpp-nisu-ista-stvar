#include <unistd.h>
#include <time.h>
#include <stdio.h>

int main()
{
    struct timespec t1;
    clock_gettime( CLOCK_MONOTONIC, &t1 );

    sleep(100);

    struct timespec t2;
    clock_gettime( CLOCK_MONOTONIC, &t2 );

    float seconds = ( float )( t2.tv_sec - t1.tv_sec ) + ( float )( t2.tv_nsec - t1.tv_nsec ) / 1e9f;

    printf( "%f\n", seconds );
}