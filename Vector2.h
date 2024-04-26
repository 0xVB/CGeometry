#pragma once
#include "CGeometry.h"

struct CGeometry::Vector2
{
	float X;
	float Y;

	Vector2(float X = 0, float Y = 0);
	Vector2(Vector3 Vector);
	Vector2(Rect Rectangle);

	static Vector2 FromAngle(float Angle, float Magnitude = 1);

	// Returns the magnitude of the vector.
	float GetMagnitude();
	// Returns a vector with equivalent direction but with the given new magnitude.
	Vector2 SetMagnitude(float);
	// Returns the basic unit direction of this vector.
	Vector2 GetUnit();
	// Returns a vector with the given unit direction but maintaining the magnitude of this vector.
	Vector2 SetUnit(Vector2);
	// Returns the direction of this vector in radians.
	float GetDirection(bool Clamp = true);
	// Returns a vector with the same magnitude but the given direction in radians.
	Vector2 SetDirection(float);
	// Rotates the vector by the given amount in radians.
	Vector2 Rotate(float);
	// Returns a vector lerped from this one to the target vector. Alpha is set to 0.5 by default, which returns the midpoint.
	Vector2 Lerp(Vector2 Target, float Alpha = 0.5);
	// Returns the cross product of the two given vectors.
	Vector2 Cross(Vector2);
	// Returns the dot product of the two given vectors.
	float Dot(Vector2);
	// Returns a lerped vector from `this` to `Target` with a magnitude amount as opposed to an alpha value.
	Vector2 Nudge(Vector2, float Amount, bool DoClamp = true);
	// Lerps to the `Target` vector's direction.
	Vector2 RadialLerp(Vector2 Target, float Alpha, bool LerpMagnitude = true);
	// Nudges to the `Target` vector's direction by the given amount.
	Vector2 RadialNudge(Vector2 Target, float Amount, bool NudgeMagnitude = true, bool DoClamp = true);
	// Returns the normal to this vector (perpendicular vector.)
	Vector2 Normal(bool Clockwise = false);
	// Returns a string representation of this vector.
	std::string ToString(bool Brackets = true, bool Constructor = false);
	// A the zero vector.
	static Vector2 Zero;

	void operator=(Vector2);
	Vector2 operator+(Vector2);
	Vector2 operator-(Vector2);
	Vector2 operator*(float);
	Vector2 operator/(float);

	operator IVector2();
	operator IVector3();
	operator Vector3();
	operator IRect();
	operator Rect();
};

struct CGeometry::IVector2
{
	int X;
	int Y;

	IVector2(int X = 0, int Y = 0);
	IVector2(Vector2);
	static IVector2 Zero;

	operator IVector3();
	operator Vector3();
	operator Vector2();
	operator IRect();
	operator Rect();
};