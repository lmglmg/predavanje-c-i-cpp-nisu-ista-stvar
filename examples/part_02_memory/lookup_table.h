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
    float const r = sqrtf( xT * xT + yT * yT ) + 0.00001f;
    float const a = atan2f( yT, xT );
    float const f = 0.23f;
    float const k = 0.5f;
    return sin( f + k * r ) / ( r * r ) * sin( a + rot ) + sin( f + M_PI / 2 + k * r ) / r * sin( a + rot );
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

    float const lowLimit = -0.25;
    float const highLimit = 0.25f;
    int const numCharacters = 17;

    int index = clamp( ( value - lowLimit ) / ( highLimit - lowLimit ) * numCharacters, 0, numCharacters - 1 );
    if ( value >= 0.f ) {
        printf( "\x1b[32m%c\x1b[0m", characters[ index ] );
    } else {
        printf( "\x1b[31m%c\x1b[0m", characters[ index ] );
    }
}