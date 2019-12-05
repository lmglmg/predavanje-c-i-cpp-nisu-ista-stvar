#include "field_image.h"
#include <stdlib.h>

// // // //

void printTable( FieldImage const * table )
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

FieldImage const * generateTable_01()
{
    static FieldImage table;
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
    FieldImage const * table = generateTable_01();
    printTable( table );
}

// // // //

FieldImage * generateTable_02( float const rot )
{
    FieldImage * table = malloc( sizeof( FieldImage ) );
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
    FieldImage * table = generateTable_02( M_PI * 0.5f );

    if ( table )
    {
        printTable( table );
        free( table );
        // Memory leak if free is missing
    }
}

// // // //

void generateTable_03( FieldImage * table, float const rot )
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
    FieldImage table;
    generateTable_03( &table, M_PI * 0.75f );
    printTable( &table );
}

// // // //

void printAndClean( FieldImage * table )
{
    printTable( table );
    free( table );
}

void main_04()
{
    FieldImage * table = malloc( sizeof( FieldImage ) );
    generateTable_03( table, M_PI );
    printAndClean( table );
    // ERROR:
    // free( table );
}

// // // //

FieldImage generateTable_05( float const rot )
{
    FieldImage result;
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
    FieldImage table = generateTable_05( M_PI * 1.25f );
    printTable( &table );
}

// // // //

int main()
{
    printf("Lookup table size : %lu bytes\n\n", sizeof( FieldImage ) );

    printf("\n\n 1:\n\n" ); main_01();
    printf("\n\n 2:\n\n" ); main_02();
    printf("\n\n 3:\n\n" ); main_03();
    printf("\n\n 4:\n\n" ); main_04();
    printf("\n\n 5:\n\n" ); main_05();
}