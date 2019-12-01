#include "lookup_table.h"
#include <stdlib.h>

// // // //

void printTable( LookupTable const * table )
{
    if ( !table ) return;

    for ( int i = 0; i < TABLE_SIZE; ++i )
    {
        for ( int j = 0; j < TABLE_SIZE; ++j )
        {
            print_value( table->data[ i ][ j ] );
            print_value( table->data[ i ][ j ] );
        }
        putc( '\n', stdout );
    }
}

// // // //

LookupTable const * generateTable_01()
{
    static LookupTable table;
    static int is_initialized = 0;

    if ( is_initialized )
    {
        return &table;
    }
    else
    {
        for ( int i = 0; i < TABLE_SIZE; ++i )
        {
            for ( int j = 0; j < TABLE_SIZE; ++j )
            {
                table.data[i][j] = f( i, j, 0.f );
            }
        }
        is_initialized = 1;
        return &table;
    }
}

void main_01()
{
    LookupTable const * table = generateTable_01();
    printTable( table );
}

// // // //

LookupTable * generateTable_02( float const rot )
{
    LookupTable * table = malloc( sizeof( LookupTable ) );
    for ( int i = 0; i < TABLE_SIZE; ++i )
    {
        for ( int j = 0; j < TABLE_SIZE; ++j )
        {
            table->data[i][j] = f( i, j, rot );
        }
    }
    return table;
}


void main_02()
{
    LookupTable * table = generateTable_02( M_PI * 0.5f );

    if ( table )
    {
        printTable( table );
        free( table );
        // Memory leak if free is missing
    }
}

// // // //

void generateTable_03( LookupTable * table, float const rot )
{
    if ( !table ) return;

    for ( int i = 0; i < TABLE_SIZE; ++i )
    {
        for ( int j = 0; j < TABLE_SIZE; ++j )
        {
            table->data[ i ][ j ] = f( i, j, rot);
        }
    }
}

void main_03()
{
    LookupTable table;
    generateTable_03( &table, M_PI * 0.75f );
    printTable( &table );
}

// // // //

void printAndClean( LookupTable * table )
{
    printTable( table );
    free( table );
}

void main_04()
{
    LookupTable * table = malloc( sizeof( LookupTable ) );
    generateTable_03( table, M_PI );
    printAndClean( table );
    // ERROR:
    // free( table );
}

// // // //

LookupTable generateTable_05( float const rot )
{
    LookupTable result;
    for ( int i = 0; i < TABLE_SIZE; ++i )
    {
        for ( int j = 0; j < TABLE_SIZE; ++j )
        {
            result.data[ i ][ j ] = f( i, j, rot);
        }
    }
    return result;
}

void main_05()
{
    LookupTable table = generateTable_05( M_PI * 1.25f );
    printTable( &table );
}

// // // //

int main()
{
    printf("Lookup table size : %lu bytes\n\n", sizeof( LookupTable ) );

    printf("\n\n 1:\n\n" ); main_01();
    printf("\n\n 2:\n\n" ); main_02();
    printf("\n\n 3:\n\n" ); main_03();
    printf("\n\n 4:\n\n" ); main_04();
    printf("\n\n 5:\n\n" ); main_05();
}