#pragma once

#include "stdio.h"
#include "math.h"

#define TABLE_SIZE 30

typedef struct
{
    float data[ TABLE_SIZE ][ TABLE_SIZE ];
} LookupTable;

float f(int x, int y)
{
    float const r = sqrtf( x*x + y*y ) * 0.25;
    return sinf( r ) * exp2f( -r );
}

void print_value( float const value )
{
    if ( value < -0.04f )
    {
        putc( ':', stdout );
    }
    else if ( value < 0.f )
    {
        putc( ' ', stdout );
    }
    else if ( value < 0.04f )
    {
        putc( '-', stdout );
    }
    else if ( value < 0.1f )
    {
        putc( '~', stdout );
    }
    else if ( value < 0.2f )
    {
        putc( '+', stdout );
    }
    else if ( value < 0.35f )
    {
        putc( '*', stdout );
    }
    else if ( value < 0.4f )
    {
        putc( '#', stdout );
    }
    else
    {
        putc( '@', stdout );
    }
}