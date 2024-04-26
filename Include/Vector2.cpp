#include "Vector2.h"
#include "Vector3.h"
#include "Rect.h"

using namespace CGeometry;

#pragma region Constructors
Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
}

Vector2::Vector2(Vector3 Vector)
{
	X = Vector.X;
	Y = Vector.Y;
}

Vector2::Vector2(Rect Rectangle)
{
    *this = Rectangle.Position;
}

Vector2 Vector2::FromAngle(float Angle, float Magnitude)
{
    return Vector2(
        cos(Angle) * Magnitude,
        sin(Angle) * Magnitude
    );
}
#pragma endregion

#pragma region Methods
Vector2 Vector2::Rotate(float Rad)
{
    float NX = X * cos(Rad) - Y * sin(Rad);
    float NY = X * sin(Rad) + Y * cos(Rad);
    return Vector2(NX, NY);
}

std::string Vector2::ToString(bool B, bool C)
{
    std::string Result = "";
    if (C) Result = "Vector2";
    if (B) Result += "(";
    Result += std::to_string(X) + ", " + std::to_string(Y);
    if (B) Result += ")";
    return Result;
}

float Vector2::GetMagnitude()
{
    return sqrt(X * X + Y * Y);
}

Vector2 Vector2::Cross(Vector2 Other)
{
    return Vector2(Y * Other.Y, X * Other.X);
}

float Vector2::Dot(Vector2 Other) {
    return X * Other.X + Y * Other.Y;
}

Vector2 Vector2::Lerp(Vector2 Target, float Alpha)
{
    return Vector2(
        X + (Target.X - X) * Alpha,
        Y + (Target.Y - Y) * Alpha
    );
}

Vector2 Vector2::Nudge(Vector2 Target, float Amount, bool DoClamp)
{
    float MagDelta = Target.GetMagnitude() - GetMagnitude();
    float Alpha = Amount / MagDelta;
    if (DoClamp)
        Alpha = Clamp(Alpha, -1, 1);

    return Lerp(Target, Alpha);
}

Vector2 Vector2::SetMagnitude(float NewMag)
{
    auto Direction = GetUnit();
    return Direction * NewMag;
}

Vector2 Vector2::GetUnit()
{
    float Mag = GetMagnitude();
    if (Mag == 0) return Zero;

    return Vector2(
        X / Mag,
        Y / Mag
    );
}

Vector2 Vector2::Normal(bool Clockwise)
{
    if (Clockwise)
        return Vector2(
            Y,
            -X
        );

    return Vector2(
        -Y,
        X
    );
}

float Vector2::GetDirection(bool Clamp)
{
    if (Clamp)
        return ClampAngle(atan2(Y, X));
    else
        return atan2(Y, X);
}

Vector2 Vector2::SetDirection(float NewDir)
{
    float Magnitude = GetMagnitude();
    return Vector2(
        X * cos(NewDir),
        Y * sin(NewDir)
    );
}

Vector2 Vector2::SetUnit(Vector2 NewUnit)
{
    return NewUnit * GetMagnitude();
}

Vector2 Vector2::RadialLerp(Vector2 Target, float Alpha, bool LerpMagnitude)
{
    float MyDir = GetDirection(false);
    float TDir = Target.GetDirection(false);
    float DirDelta = ClampAngle(TDir - MyDir);
    float NewDir = MyDir + DirDelta * Alpha;
    float NewMag = GetMagnitude();

    if (LerpMagnitude)
        NewMag = NewMag + (Target.GetMagnitude() - NewMag) * Alpha;
    return Vector2::FromAngle(NewDir, NewMag);
}

Vector2 Vector2::RadialNudge(Vector2 Target, float Amount, bool LerpMagnitude, bool DoClamp)
{
    float MyDir = GetDirection(false);
    float TDir = Target.GetDirection(false);
    float DirDelta = ClampAngle(TDir - MyDir);
    float Alpha = Amount / DirDelta;
    if (DoClamp) Alpha = Clamp(Alpha, -1, 1);
    float NewDir = MyDir + DirDelta * Alpha;
    float NewMag = MyDir;

    if (LerpMagnitude)
        NewMag = MyDir + (Target.GetMagnitude() - MyDir) * Alpha;
    return Vector2::FromAngle(NewDir, NewMag);
}
#pragma endregion

#pragma region Operators
Vector2 Vector2::operator+(Vector2 Other)
{
    return Vector2(X + Other.X, Y + Other.Y);
}

Vector2 Vector2::operator-(Vector2 Other)
{
    return Vector2(X - Other.X, Y - Other.Y);
}

Vector2 Vector2::operator*(float F)
{
    return Vector2(X * F, Y * F);
}

Vector2 Vector2::operator/(float F)
{
    if (F == 0) return *this;
    return Vector2(X / F, Y / F);
}

void Vector2::operator=(Vector2 Other)
{
    X = Other.X;
    Y = Other.Y;
}
#pragma endregion

#pragma region Converters
Vector2::operator IVector2()
{
    return IVector2(X, Y);
}

Vector2::operator Vector3()
{
    return Vector3(X, Y, 0);
}

Vector2::operator IVector3()
{
    return IVector3(X, Y, 0);
}

Vector2::operator Rect()
{
    return Rect(X, Y, 0, 0);
}

Vector2::operator IRect()
{
    return IRect(X, Y, 0, 0);
}
#pragma endregion

#pragma region IVector2
IVector2::IVector2(int x, int y)
{
    X = x;
    Y = y;
}

IVector2::IVector2(Vector2 Vec)
{
    X = Vec.X;
    Y = Vec.Y;
}

IVector2::operator Vector2()
{
    return Vector2(X, Y);
}

IVector2::operator Vector3()
{
    return Vector3(X, Y, 0);
}

IVector2::operator IVector3()
{
    return IVector3(X, Y, 0);
}

IVector2::operator Rect()
{
    return Rect(X, Y, 0, 0);
}

IVector2::operator IRect()
{
    return IRect(X, Y, 0, 0);
}
#pragma endregion

Vector2 Vector2::Zero = Vector2();
IVector2 IVector2::Zero = IVector2();