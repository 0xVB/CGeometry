#pragma once
#include "Geometry.hpp"

#ifndef IFDEF_VECTOR2
#define IFDEF_VECTOR2

template <typename T>
struct Vector2
{
    T X;
    T Y;

    Vector2();
    Vector2(T);
    Vector2(T, T);
    Vector2(Rect<T>);
    Vector2(Vector3<T>);

    void operator=(Vector2<T>);
    Vector2 operator+(Vector2);
    Vector2 operator-(Vector2);
    Vector2 operator*(float);
    Vector2 operator/(float);

    operator Vector3<T>();
    operator Rect<T>();

    // Rotates the vector by the given angle.
    Vector2 Rotate(float Radians);
    
    // Returns the cross-product of the 2 vectors.
    Vector2 Cross(Vector2 Other);

    // Returns the dot-product of the 2 vectors.
    float Dot(Vector2 Other);

    // Returns a vector lerped from `this` to `Target`.
    Vector2 Lerp(Vector2 Target, float Alpha);

    // Returns a lerped vector from `this` to `Target` with a magnitude amount as opposed to an alpha value.
    Vector2 Nudge(Vector2 Target, float Amount);

    // Returns the magnitude of the vector.
    float GetMagnitude();

    // Returns a vector with the given magnitude value, maintaining the direction of this one.
    Vector2 SetMagnitude(float NewMag = 1);

    // Equivalent to SetMagnitude but NewMag = 1.
    Vector2 Unit();

    // Lerps to the `Target` vector's direction.
    Vector2 RadialLerp(Vector2 Target, float Amount, bool LerpMagnitude = true);

    // Returns the normal to this vector (perpendicular vector.)
    Vector2 Normal(bool Clockwise = false);

    // Returns a string representation of this vector.
    std::string ToString(bool Brackets = true, bool Constructor = false);

    static Vector2 Zero;
};

#include "Vector2.cpp"
#endif