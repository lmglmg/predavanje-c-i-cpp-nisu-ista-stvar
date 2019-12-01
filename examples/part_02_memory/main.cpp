#include "lookup_table.h"
#include <stdlib.h>

#include <memory>

// // // //

void printTable( LookupTable const & table )
{
    for ( int i = 0; i < TABLE_SIZE; ++i )
    {
        for ( int j = 0; j < TABLE_SIZE; ++j )
        {
            print_value( table.data[ i ][ j ] );
            print_value( table.data[ i ][ j ] );
        }
        putc( '\n', stdout );
    }
}

// // // //

LookupTable const & generateTable_01()
{
    static LookupTable table;
    static int is_initialized = 0;

    if ( is_initialized )
    {
        return table;
    }
    else
    {
        for ( int i = 0; i < TABLE_SIZE; ++i )
        {
            for ( int j = 0; j < TABLE_SIZE; ++j )
            {
                table.data[ i ][ j ] = f( i, j );
            }
        }
        is_initialized = 1;
        return table;
    }
}

void main_01()
{
    LookupTable const & table = generateTable_01();
    printTable( table );
}

// // // //

std::unique_ptr< LookupTable > generateTable_02()
{
    std::unique_ptr< LookupTable > table = std::make_unique< LookupTable >();
    for ( int i = 0; i < TABLE_SIZE; ++i )
    {
        for ( int j = 0; j < TABLE_SIZE; ++j )
        {
            table->data[ i ][ j ] = f( i, j );
        }
    }
    return table;
}


void main_02()
{
    std::unique_ptr< LookupTable > table = generateTable_02();
    static_assert( sizeof( table ) == sizeof( void* ) );
    if ( table )
    {
         printTable( *table );
    }
}

// // // //

LookupTable generateTable_03()
{
    LookupTable result;
    for ( int i = 0; i < TABLE_SIZE; ++i )
    {
        for ( int j = 0; j < TABLE_SIZE; ++j )
        {
            result.data[ i ][ j ] = f( i, j );
        }
    }
    return result;
}

void main_03()
{
    LookupTable table = generateTable_03();
    printTable( table );
}

// // // //

int main()
{
    main_01();
    main_02();
    main_03();
}