#pragma once
#include "Direct3D.h"
#include <Math.h>

#define _USE_MATH_DEFINES

//���S�Ƀ��������J�����邽�߂̃}�N��
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

//�[��
static const int   ZERO          = 0;
//360��
static const float TWOPI_DEGREES = 360.f;
//180��
static const float PI_DEGREES    = 180.f;
//1�b
static const int   ONE_SECOND = 60;

//XMFLOAT4�Z�b�g
static void SetXMFLOAT4(XMFLOAT4 xmf4, float x, float y, float z, float w)
{
    xmf4.x = x;
    xmf4.y = y;
    xmf4.z = z;
    xmf4.w = w;
}

//XMFLOAT3�Z�b�g
static void SetXMFLOAT3(XMFLOAT3 xmf3, float x, float y, float z)
{
    xmf3.x = x;
    xmf3.y = y;
    xmf3.z = z;
}

//XMFLOAT3 TO XMINT3
static XMINT3 ToXMINT(XMFLOAT3 vec)
{
    return { (int)vec.x, (int)vec.y, (int)vec.z };
}

//�����_������
static int RandInt(int a, int b)
{
    int num = (b - a) + 1;

    return (rand() % num) + a;
}

//XMFLOAT3���m�̈����Z
static XMFLOAT3 SubXMFLOAT3(XMFLOAT3 vec, XMFLOAT3 vec2)
{
    return XMFLOAT3(vec.x - vec2.x, vec.y - vec2.y, vec.z - vec2.z);
}

//�����v�Z
static float CalcDist(XMFLOAT3 vec, XMFLOAT3 vec2)
{
    XMFLOAT3 vec3 = SubXMFLOAT3(vec, vec2);

    return sqrtf((vec3.x * vec3.x) + (vec3.y * vec3.y) + (vec3.z * vec3.z));
}

//XMVECTOR TO XMFLOAT3
static XMFLOAT3 VectorToFloat3(XMVECTOR v_)
{
    XMFLOAT3 xmf3;
    XMStoreFloat3(&xmf3, v_);

    return xmf3;
}