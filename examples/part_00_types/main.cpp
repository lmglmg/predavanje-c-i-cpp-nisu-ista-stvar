#include <cstdio>
#include <chrono>
#include <thread>

int main()
{
    using namespace std::chrono;

    auto const start = high_resolution_clock::now();
    std::this_thread::sleep_for( milliseconds( 100 ) );
    auto const end = high_resolution_clock::now();

    auto const seconds = duration_cast< duration< float, seconds::period > >( end - start ).count();

    printf( "%f\n", seconds );
}