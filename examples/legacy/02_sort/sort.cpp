#include <iostream>
#include <random>
#include <vector>

std::vector< int > generate_random_numbers( std::size_t size )
{
    std::vector< int > randomVector( size );

    std::random_device randomDevice;
    std::uniform_int_distribution< int > distribution( -100'000, 100'000 );

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

int intLess( void const * a, void const * b )
{
    auto const ia = * static_cast< int const * >( a );
    auto const ib = * static_cast< int const * >( b );
    return ia - ib;
}

int main()
{
    std::cout << "Sorting floats\n";

    std::size_t constexpr vectorSize = 1'000'000;

    std::vector< int > v1 = generate_random_numbers( vectorSize );
    std::vector< int > v2 = v1;

    timeOperation
    (
        "C sort",
        [ & ]()
        {
            std::qsort( v1.data(), v1.size(), sizeof( float ), intLess );
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