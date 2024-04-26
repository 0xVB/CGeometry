#pragma once

#include <corecrt_math_defines.h>
#include <string>

namespace Geometry
{
    template <typename T>
    struct Vector2;
    template <typename T>
    struct Vector3;
    template <typename T>
    struct Rect;

    #define IRect Rect<int>
    #define FRect Rect<float>
    #define IVec2 Vector2<int>
    #define IVec3 Vector3<int>
    #define FVec2 Vector2<float>
    #define FVec3 Vector3<float>

    #include "Vector2.hpp"
    #include "Vector3.hpp"
    #include "Rect.hpp"
}