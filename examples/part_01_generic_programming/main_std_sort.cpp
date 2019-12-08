#include "common_constants.h"

#include <cstdio>
#include <chrono>
#include <thread>
#include <vector>
#include <random>

int main()
{
    using namespace std::chrono;

    std::vector< int > v( ARRAY_SIZE );
    std::random_device randomDevice;
    std::mt19937 pseudoRanndomDevice( randomDevice() );
    std::uniform_int_distribution< int > distribution( -ARRAY_MAX_VALUE, ARRAY_MAX_VALUE );

    std::generate( begin( v ), end( v ), [ & ](){ return distribution( pseudoRanndomDevice ); } );
    auto const start = high_resolution_clock::now();

    std::sort( begin( v ), end( v ), []( int const a, int const b ){ return a < b; } );

    auto const end = high_resolution_clock::now();

    auto const seconds = duration_cast< duration< float, seconds::period > >( end - start ).count();

    if ( !is_sorted( v.data(), ARRAY_SIZE ) )
    {
        printf( "ERROR!" );
    }

    printf( "%f\n", seconds );
}