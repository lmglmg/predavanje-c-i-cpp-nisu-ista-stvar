#include <iostream>
#include <random>
#include <vector>
#include <cmath>

struct TriangleSides
{
    float a;
    float b;
    float c;
};

float area( TriangleSides const & triangle )
{
    auto const s = ( triangle.a + triangle.b + triangle.c ) / 2.f;
    return std::sqrt( s * ( s - triangle.a) * ( s - triangle.b ) * ( s - triangle.c ) );
}

std::vector< TriangleSides > generateRandomTriangleSides( std::size_t size )
{
    std::vector< TriangleSides > randomVector( size );

    std::random_device randomDevice;
    std::uniform_real_distribution< float > distribution( 1'000, 1'000 );

    std::generate
    (
        begin( randomVector ),
        end( randomVector ),
        [ & ](){ return TriangleSides{ distribution( randomDevice ), distribution( randomDevice ), distribution( randomDevice ) }; }
    );

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

int areaCompare( void const * a, void const * b )
{
    auto const areaA = area( * static_cast< TriangleSides const * >( a ) );
    auto const areaB = area( * static_cast< TriangleSides const * >( b ) );
    return ( areaA > areaB ) - ( areaA < areaB );
}

int main()
{
    std::cout << "Sorting triangles\n";

    std::size_t constexpr vectorSize = 10'000'000;

    std::vector< TriangleSides > v1 = generateRandomTriangleSides( vectorSize );
    std::vector< TriangleSides > v2 = v1;

    timeOperation
    (
        "C sort",
        [ & ]()
        {
            std::qsort( v1.data(), v1.size(), sizeof( TriangleSides ), areaCompare );
        }
    );

    timeOperation
    (
        "C++ sort",
        [ & ]()
        {
            std::sort
            (
                begin( v2 ),
                end( v2 ),
                []( TriangleSides const & a, TriangleSides const & b ){ return area( a ) < area( b ); }
            );
        }
    );

    for ( std::size_t i  = 0; i < v1.size(); ++i )
    {
        if ( area( v1[ i ] ) != area( v2[ i ] ) )
        {
            std::cerr << "values at " << i << " are not equal!";
            std::terminate();
        }
    }
}