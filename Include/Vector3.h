#pragma once
#include "CGeometry.h"

struct CGeometry::Vector3
{
	float X;
	float Y;
	float Z;

	Vector3(float X = 0, float Y = 0, float Z = 0);
	Vector3(Vector2 Vector);

	static Vector3 FromAngle(float HAngle, float VAngle, float Magnitude = 0);

	// Returns the magnitude of the vector.
	float GetMagnitude();
	// Returns a vector with equivalent direction but with the given new magnitude.
	Vector3 SetMagnitude(float);
	// Returns the vertical (ZY) direction of this vector in radians.
	float GetVDirection(bool DoClamp = true);
	// Returns the horizontal (XZ) direction of this vector in radians.
	float GetHDirection(bool DoClamp = true);
	// Returns the orbital (XY) direction of this vector in radians.
	float GetODirection(bool DoClamp);
	// Rotates the vector by the given horizontal (Across Y) and vertical (Across X) degrees in radians.
	Vector3 RotateBy(float H = 0, float V = 0);
	// Returns the basic unit direction of this vector.
	Vector3 GetUnit();
	// Returns a vector with the given unit direction but maintaining the magnitude of this vector.
	Vector3 SetUnit(Vector3);
	// Returns a vector lerped from this one to the target vector. Alpha is set to 0.5 by default, which returns the midpoint.
	Vector3 Lerp(Vector3 Target, float Alpha = 0.5);
	// Returns the cross product of the two given vectors.
	Vector3 Cross(Vector3);
	// Returns the dot product of the two given vectors.
	float Dot(Vector3);
	// Returns a lerped vector from `this` to `Target` with a magnitude amount as opposed to an alpha value.
	Vector3 Nudge(Vector3, float Amount, bool DoClamp = true);
	// Lerps to the `Target` vector's direction.
	Vector3 RadialLerp(Vector3 Target, float Alpha, bool LerpMagnitude = true);
	// Nudges to the `Target` vector's direction by the given amount.
	Vector3 RadialNudge(Vector3 Target, float Amount, bool NudgeMagnitude = true, bool DoClamp = true);
	// Returns the normal to this vector (perpendicular vector.)
	Vector3 Normal(float Angle = M_PI_2);
	// Returns a projected Vector2 value. Vector2(X, Y + Z). If InvertZ is true, it returns Vector2(X, Y - Z).
	Vector2 Project(bool InvertZ = Z_INVERTED);
	// Returns a string representation of this vector.
	std::string ToString(bool Brackets = true, bool Constructor = false);
	static Vector3 Zero;

	Vector3 operator+(Vector3);
	Vector3 operator-(Vector3);
	Vector3 operator*(float);
	Vector3 operator/(float);

	operator IVector3();
	operator IVector2();
	operator Vector2();
	operator IRect();
	operator Rect();
};

struct CGeometry::IVector3
{
	int X;
	int Y;
	int Z;

	IVector3(int X = 0, int Y = 0, int Z = 0);
	IVector3(Vector3);

	operator IVector2();
	operator Vector2();
	operator Vector3();
	operator IRect();
	operator Rect();

	static IVector3 Zero;
};