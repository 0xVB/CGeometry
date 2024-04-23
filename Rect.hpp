#pragma once
template <typename T>

#ifndef IFDEF_RECT
#define IFDEF_RECT

struct Rect
{
    T X;
    T Y;
    T W;
    T H;

    Rect();
    Rect(T);
    Rect(T, T, T = 0, T = 0);
    Rect(Vector2<T>);
    Rect(Vector2<T>, Vector2<T>);

    Rect operator+(Rect);
    Rect operator-(Rect);
    Rect operator*(float);
    Rect operator/(float);

    operator Vector2<T>();
};

#include "Rect.cpp"
#endif