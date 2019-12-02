#pragma once

#define ARRAY_SIZE 10000000
#define ARRAY_MAX_VALUE 1000

inline int is_sorted( int const * arr, int size )
{
    for ( int i = 1; i < size; ++i )
    {
        if ( arr[ i - 1 ] > arr[ i ] )
        {
            return 0;
        }
    }
    return 1;
}