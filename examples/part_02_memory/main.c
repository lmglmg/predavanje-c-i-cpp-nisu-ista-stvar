#include "field_image.h"
#include <stdlib.h>

// // // //

void printTable( FieldImage const * image )
{
    if ( !image ) return;

    for ( int i = 0; i < TABLE_SIZE; ++i )
    {
        for ( int j = 0; j < TABLE_SIZE; ++j )
        {
            print_value( image->data[ i ][ j ] );
            print_value( image->data[ i ][ j ] );
        }
        putc( '\n', stdout );
    }
}

// // // //

FieldImage const * generateImage_01()
{
    static FieldImage image;
    static int is_initialized = 0;

    if ( is_initialized )
    {
        return &image;
    }
    else
    {
        for ( int i = 0; i < TABLE_SIZE; ++i )
        {
            for ( int j = 0; j < TABLE_SIZE; ++j )
            {
                image.data[ i ][ j ] = f( i, j, 0.f );
            }
        }
        is_initialized = 1;
        return &image;
    }
}

void main_01()
{
    FieldImage const * image = generateImage_01();
    if ( !image ) return;
    printTable( image );
}

// // // //

FieldImage * generateImage_02( float const rot )
{
    FieldImage * image = malloc( sizeof( FieldImage ) );
    for ( int i = 0; i < TABLE_SIZE; ++i )
    {
        for ( int j = 0; j < TABLE_SIZE; ++j )
        {
            image->data[ i ][ j ] = f( i, j, rot );
        }
    }
    return image;
}


void main_02()
{
    FieldImage * image = generateImage_02( M_PI * 0.5f );
    if ( !image ) return;
    printTable( image );
    free( image );
    // Memory leak if free is missing
}

// // // //

void generateImage_03( FieldImage * image, float const rot )
{
    if ( !image ) return;

    for ( int i = 0; i < TABLE_SIZE; ++i )
    {
        for ( int j = 0; j < TABLE_SIZE; ++j )
        {
            image->data[ i ][ j ] = f( i, j, rot);
        }
    }
}

void main_03()
{
    FieldImage image;
    generateImage_03( &image, M_PI * 0.75f );
    printTable( &image );
}

// // // //

void printAndClean( FieldImage * image )
{
    if ( !image ) return;
    printTable( image );
    free( image );
}

void main_04()
{
    FieldImage * image = malloc( sizeof( FieldImage ) );
    generateImage_03( image, M_PI );
    printAndClean( image );
    // ERROR:
    // free( image );
}

// // // //

FieldImage generateImage_05( float const rot )
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
    FieldImage image = generateImage_05( M_PI * 1.25f );
    printTable( &image );
}

// // // //

int main()
{
    printf("Lookup image size : %lu bytes\n\n", sizeof( FieldImage ) );

    printf("\n\n 1:\n\n" ); main_01();
    printf("\n\n 2:\n\n" ); main_02();
    printf("\n\n 3:\n\n" ); main_03();
    printf("\n\n 4:\n\n" ); main_04();
    printf("\n\n 5:\n\n" ); main_05();
}