#include "Math.h"
#include <math.h>

#include <algorithm>

void Math::SetXMFLOAT4(XMFLOAT4 xmf4, float x, float y, float z, float w)
{
    xmf4.x = x;
    xmf4.y = y;
    xmf4.z = z;
    xmf4.w = w;
}
void Math::SetXMFLOAT3(XMFLOAT3 xmf3, float x, float y, float z)
{
    xmf3.x = x;
    xmf3.y = y;
    xmf3.z = z;
}

XMINT3 Math::ToXMINT(XMFLOAT3 vec)
{
    return { (int)vec.x, (int)vec.y, (int)vec.z };
}

int Math::RandInt(int a, int b)
{
    int num = (b - a) + 1;

    return (rand() % num) + a;
}