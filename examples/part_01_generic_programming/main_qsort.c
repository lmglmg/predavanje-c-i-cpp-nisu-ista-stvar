#include "common_constants.h"

#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int intLess( void const * a, void const * b )
{
    int const ia = * ( int const * )( a );
    int const ib = * ( int const * )( b );
    return ia - ib;
}

int main()
{
    srand( time( NULL ) );

    int * arr = malloc( ARRAY_SIZE * sizeof( int ) );

    for ( int i = 0; i < ARRAY_SIZE; ++i )
    {
        arr[ i ] = ( rand() % ( 2 * ARRAY_MAX_VALUE ) ) - ARRAY_MAX_VALUE;
    }

    struct timespec t1;
    clock_gettime( CLOCK_MONOTONIC, &t1 );

    qsort( arr, ARRAY_SIZE, sizeof( int ), intLess );

    struct timespec t2;
    clock_gettime( CLOCK_MONOTONIC, &t2 );

    float seconds = ( float )( t2.tv_sec - t1.tv_sec ) + ( float )( t2.tv_nsec - t1.tv_nsec ) / 1e9f;

    printf( "%f\n", seconds );

    if ( !is_sorted( arr, ARRAY_SIZE ) )
    {
        printf( "ERROR!" );
    }

    free( arr );
}