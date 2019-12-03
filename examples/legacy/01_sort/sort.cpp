#include <iostream>
#include <random>
#include <vector>

std::vector< float > generate_random_numbers( std::size_t size )
{
    std::vector< float > randomVector( size );

    std::random_device randomDevice;
    std::uniform_real_distribution< float > distribution( -1000.f, 1000.f );

    std::generate( begin( randomVector ), end( randomVector ), [ & ](){ return distribution( randomDevice ); } );

    return randomVector;
}

template< typename F >
void timeOperation( std::string_view description, F && operation )
{
    auto const startTime = std::chrono::high_resolution_clock::now();

    operation();

    auto const endTime = std::chrono::high_resolution_clock::now();

    auto const milliseconds = std::chrono::duration_cast< std::chrono::milliseconds >( endTime - startTime ).count();

    std::cout << description << " : " << milliseconds << " ms\n";
}

int floatCompare( void const * a, void const * b )
{
    auto const fa = * static_cast< float const * >( a );
    auto const fb = * static_cast< float const * >( b );
    return ( fa > fb ) - ( fa < fb );
}

int main()
{
    std::cout << "Sorting floats\n";

    std::size_t constexpr vectorSize = 10'000'000;

    std::vector< float > v1 = generate_random_numbers( vectorSize );
    std::vector< float > v2 = v1;

    timeOperation
    (
        "C sort",
        [ & ]()
        {
            std::qsort( v1.data(), v1.size(), sizeof( float ), floatCompare );
        }
    );

    timeOperation
    (
        "C++ sort",
        [ & ]()
        {
            std::sort( begin( v2 ), end( v2 ) );
        }
    );

    for ( std::size_t i  = 0; i < v1.size(); ++i )
    {
        if ( v1[ i ] != v2[ i ] )
        {
            std::cerr << "values at " << i << " are not equal!";
            std::cerr << v1[ i ] << " vs " << v2[ i ];
            std::terminate();
        }
    }
}