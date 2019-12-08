#pragma once

#include "stdio.h"
#include "math.h"

#define TABLE_SIZE 50

typedef struct
{
    float data[ TABLE_SIZE ][ TABLE_SIZE ];
} FieldImage;


float f( int const x, int const y, float const rot )
{
    float const xT = x - ( float )( TABLE_SIZE ) / 2 + 0.5f;
    float const yT = y - ( float )( TABLE_SIZE ) / 2 + 0.5f;
    float const rRaw = sqrtf( xT * xT + yT * yT ) + 0.00001f;
    float const r = rRaw * 0.1f;
    float const a = atan2f( yT, xT );
    float const f = M_PI * 0.5f;
    float const k = 3.0f;
    return ( cos( f + k * r - M_PI / 2 ) / ( r * r * k ) + cos( f + k * r ) / r ) * sin( a + rot );
}

int clamp( int value, int minValue, int maxValue )
{
    if ( value < minValue ) return minValue;
    if ( value > maxValue ) return maxValue;
    return value;
}

void print_value( float const value )
{
    char const characters[] = " -~=+*xqwz%#@";

    float const highLimit = 2.f;
    int const numCharacters = sizeof(characters) - 1;

    int index = clamp( fabsf( value ) / highLimit * numCharacters, 0, numCharacters - 1 );
    printf( "\x1b[%dm%c\x1b[0m", value >= 0.f ? 32 : 31, characters[ index ] );
}