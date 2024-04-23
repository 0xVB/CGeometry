#pragma once

#ifndef IFDEF_VECTOR3
#define IFDEF_VECTOR3

template <typename T>
struct Vector3
{
    T X;
    T Y;
    T Z;

    Vector3();
    Vector3(T);
    Vector3(T, T, T = 0);
    Vector3(Vector2<T>);

    Vector3 operator+(Vector3);
    Vector3 operator-(Vector3);
    Vector3 operator*(float);
    Vector3 operator/(float);

    operator Vector2<T>();
};

#include "Vector3.cpp"
#endif