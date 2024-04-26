#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Rect.h"

using namespace CGeometry;

#pragma region Constructors
Vector3::Vector3(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

Vector3::Vector3(Vector2 Vector)
{
	X = Vector.X;
	Y = Vector.Y;
	Z = 0;
}

Vector3 Vector3::FromAngle(float H, float V, float Mag)
{
	return Vector3(
		cos(H) * cos(V) * Mag,
		sin(H) * cos(V) * Mag,
		sin(V) * Mag
	);
}
#pragma endregion

#pragma region Methods
float Vector3::GetMagnitude()
{
	return sqrt(X * X + Y * Y + Z * Z);
}

Vector3 Vector3::SetMagnitude(float NewMag)
{
	return GetUnit() * NewMag;
}

float Vector3::GetVDirection(bool DoClamp)
{
	if (DoClamp)
		return ClampAngle(atan2(Z, Y));
	return atan2(Z, Y);
}

float Vector3::GetHDirection(bool DoClamp)
{
	if (DoClamp)
		return ClampAngle(atan2(Z, X));
	return atan2(Z, X);
}

float Vector3::GetODirection(bool DoClamp)
{
	if (DoClamp)
		return ClampAngle(atan2(Y, X));
	return atan2(Y, X);
}

Vector3 Vector3::GetUnit()
{
	float Mag = GetMagnitude();
	if (Mag == 0) return Zero;

	return Vector3(
		X / Mag,
		Y / Mag,
		Z / Mag
	);
}

Vector3 Vector3::SetUnit(Vector3 NewUnit)
{
	return NewUnit * GetMagnitude();
}

Vector3 Vector3::Cross(Vector3 Other)
{
	return Vector3(
		Y * Other.Z - Z * Other.Y,
		Z * Other.X - X * Other.Z,
		X * Other.Y - Y * Other.X
	);
}

float Vector3::Dot(Vector3 Other)
{
	return X * Other.X + Y * Other.Y + Z * Other.Z;
}

std::string Vector3::ToString(bool Brackets, bool Constructor)
{
	std::string Result = "";
	if (Constructor) Result = "Vector3";
	if (Brackets) Result += "(";
	Result += std::to_string(X) + ", " + std::to_string(Y) + ", " + std::to_string(Z);
	if (Brackets) Result += ")";
	return Result;
}

Vector3 Vector3::RotateBy(float H, float V)
{
	return Vector3::FromAngle(GetHDirection() + H, GetVDirection() + V, GetMagnitude());
}

Vector3 Vector3::Lerp(Vector3 Target, float Alpha)
{
	return Vector3(
		X + (Target.X - X) * Alpha,
		Y + (Target.Y - Y) * Alpha,
		Z + (Target.Z - Z) * Alpha
	);
}

Vector3 Vector3::Nudge(Vector3 Target, float Amount, bool DoClamp)
{
	float MagDelta = Target.GetMagnitude() - GetMagnitude();
	float Alpha = Amount / MagDelta;
	if (DoClamp)
		Alpha = Clamp(Alpha, -1, 1);

	return Lerp(Target, Alpha);
}

Vector3 Vector3::RadialLerp(Vector3 Target, float Alpha, bool LerpMagnitude)
{
	float HDir = GetHDirection(false);
	float VDir = GetVDirection(false);
	float HDel = ClampAngle(Target.GetHDirection() - HDir);
	float VDel = ClampAngle(Target.GetVDirection() - VDir);
	float Mag = GetMagnitude();
	if (LerpMagnitude)
		Mag = Mag + (Target.GetMagnitude() - Mag) * Alpha;
	return Vector3::FromAngle(
		HDir + HDel * Alpha,
		VDir + VDel * Alpha,
		Mag
	);
}

Vector3 Vector3::RadialNudge(Vector3 Target, float Amount, bool NudgeMagnitude, bool DoClamp)
{
	float HDir = GetHDirection(false);
	float VDir = GetVDirection(false);
	float HDel = ClampAngle(Target.GetHDirection() - HDir);
	float VDel = ClampAngle(Target.GetVDirection() - VDir);
	float TDel = sqrt(HDel * HDel + VDel * VDel);
	float Alpha = Amount / TDel;
	float Mag = GetMagnitude();
	if (NudgeMagnitude)
		Mag = Mag + (Target.GetMagnitude() - Mag) * Alpha;
	return Vector3::FromAngle(
		HDir + HDel * Alpha,
		VDir + VDel * Alpha,
		Mag
	);
}

Vector3 Vector3::Normal(float Angle)
{
	return Cross(Vector3(cos(Angle), sin(Angle), 0)).GetUnit();
}

Vector2 Vector3::Project(bool InvertZ)
{
	if (InvertZ)
		return Vector2(X, Y - Z);
	return Vector2(X, Y + Z);
}
#pragma endregion

#pragma region Operators
Vector3 Vector3::operator+(Vector3 Other)
{
	return Vector3(X + Other.X, Y + Other.Y, Z + Other.Z);
}

Vector3 Vector3::operator-(Vector3 Other)
{
	return Vector3(X - Other.X, Y - Other.Y, Z - Other.Z);
}

Vector3 Vector3::operator*(float F)
{
	return Vector3(X * F, Y * F, Z * F);
}

Vector3 Vector3::operator/(float F)
{
	if (F == 0) return *this;
	return Vector3(X / F, Y / F, Z / F);
}
#pragma endregion

#pragma region Conversion
Vector3::operator IVector3()
{
	return IVector3(X, Y, Z);
}

Vector3::operator Vector2()
{
	return Vector2(X, Y);
}

Vector3::operator IVector2()
{
	return IVector2(X, Y);
}

Vector3::operator Rect()
{
	return Rect(X, Y, 0, 0);
}

Vector3::operator IRect()
{
	return IRect(X, Y, 0, 0);
}
#pragma endregion

#pragma region IVector3
IVector3::IVector3(int x, int y, int z)
{
	X = x;
	Y = y;
	Z = z;
}

IVector3::IVector3(Vector3 Vec)
{
	X = Vec.X;
	Y = Vec.Y;
	Z = Vec.Z;
}

IVector3::operator IVector2()
{
	return IVector2(X, Y);
}

IVector3::operator Vector2()
{
	return Vector2(X, Y);
}

IVector3::operator Vector3()
{
	return Vector3(X, Y, Z);
}

IVector3::operator IRect()
{
	return IRect(X, Y, 0, 0);
}

IVector3::operator Rect()
{
	return Rect(X, Y, 0, 0);
}
#pragma endregion

Vector3 Vector3::Zero = Vector3();
IVector3 IVector3::Zero = IVector3();