#pragma once
#include <corecrt_math_defines.h>
#include <string>
#ifndef Z_INVERTED
#define Z_INVERTED 0
#endif // !Z_INVERTED

namespace CGeometry
{
	float Clamp(float Value, float Min, float Max);
	float ClampAngle(float Angle);

	struct IVector2;
	struct IVector3;
	struct IRect;

	struct Vector2;
	struct Vector3;
	struct Rect;
}