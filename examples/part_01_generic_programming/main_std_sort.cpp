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
    std::uniform_int_distribution< int > distribution( -ARRAY_MAX_VALUE, ARRAY_MAX_VALUE );

    std::generate( begin( v ), end( v ), [ & ](){ return distribution( randomDevice ); } );

    auto const start = high_resolution_clock::now();

    std::sort( begin( v ), end( v ) );

    auto const end = high_resolution_clock::now();

    auto const seconds = duration_cast< duration< float, seconds::period > >( end - start ).count();

    printf( "%f\n", seconds );

    if ( !is_sorted( v.data(), ARRAY_SIZE ) )
    {
        printf( "ERROR!" );
    }
}