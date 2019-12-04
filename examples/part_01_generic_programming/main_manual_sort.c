#include "common_constants.h"

#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void swap_values( int * a, int * b )
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition_array( int * arr, int start_index, int end_index )
{
    int const pivot_value = arr[ end_index ];

    int pivot_index = start_index;

    for ( int i = start_index; i < end_index; ++i )
    {
        if ( arr[ i ] < pivot_value )
        {
            swap_values( &arr[ pivot_index ], &arr[ i ] );
            ++pivot_index;
        }
    }
    swap_values( &arr[ pivot_index ], &arr[ end_index ] );
    return pivot_index;
}

void quick_sort( int * arr, int start_index, int end_index )
{
    if ( start_index >= end_index ) return;

    int partition_index = partition_array( arr, start_index, end_index );
    int left_pivot = partition_index - 1;
    int right_pivot = partition_index + 1;

    while ( left_pivot > start_index && !( arr[ left_pivot ] < arr[ partition_index ] ) )
    {
        --left_pivot;
    }
    while ( right_pivot < end_index && !( arr[ partition_index ] < arr[ right_pivot ] ) )
    {
        ++right_pivot;
    }

    quick_sort( arr, start_index, left_pivot );
    quick_sort( arr, right_pivot, end_index );
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

    quick_sort( arr, 0, ARRAY_SIZE - 1 );

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