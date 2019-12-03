#pragma once

#include "stdio.h"
#include "math.h"

#define TABLE_SIZE 40

typedef struct
{
    float data[ TABLE_SIZE ][ TABLE_SIZE ];
} LookupTable;

float f( int const x, int const y, float const rot )
{
    float const xT = x - ( float )( TABLE_SIZE ) / 2;
    float const yT = y - ( float )( TABLE_SIZE ) / 2;
    float const r = sqrtf( xT * xT + yT * yT ) * 0.4;
    float const a = atan2f( yT, xT );
    return sinf( r ) * exp2f( -r * 0.5f ) * ( 0.9f - cosf( a + M_PI + rot ) );
}

int clamp( int value, int minValue, int maxValue )
{
    if ( value < minValue ) return minValue;
    if ( value > maxValue ) return maxValue;
    return value;
}

void print_value( float const value )
{
    char const * characters = "@#w*+=~- -~=+*w#@";

    float const lowLimit = -0.5;
    float const highLimit = 0.5f;
    int const numCharacters = 17;

    int index = clamp( ( value - lowLimit ) / ( highLimit - lowLimit ) * numCharacters, 0, numCharacters - 1 );
    if ( value >= 0.f ) {
        printf( "\x1b[32m%c\x1b[0m", characters[ index ] );
    } else {
        printf( "\x1b[31m%c\x1b[0m", characters[ index ] );
    }
}