#define D2D_INPUT_COUNT 1
#define D2D_INPUT0_SIMPLE

#include "d2d1effecthelpers.hlsli"

float4 tint;

D2D_PS_ENTRY(main)
{
    float4 color = D2DGetInput(0);

    return color * tint;
}