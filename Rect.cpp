#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Rect.h"

using namespace CGeometry;

#pragma region Constructors
Rect::Rect(float X, float Y, float W, float H)
{
	Position = Vector2(X, Y);
	Size = Vector2(W, H);
}

Rect::Rect(Vector2 Pos, Vector2 Sz)
{
	Position = Pos;
	Size = Sz;
}

Rect Rect::FromCenter(float X, float Y, float W, float H)
{
	X -= W / 2;
	Y -= H / 2;
	return Rect(X, Y, W, H);
}

Rect Rect::FromCenter(Vector2 Center, Vector2 Size)
{
	return Rect(
		Center - Size / 2,
		Size
	);
}

Rect Rect::FromExtent(Vector2 S, Vector2 E)
{
	return Rect(
		S,
		S - E
	);
}
#pragma endregion

#pragma region Methods
float Rect::GetArea()
{
	if (Size.X <= 0 || Size.Y <= 0) return 0;
	return Size.X * Size.Y;
}

float Rect::GetPerimeter()
{
	return Size.X + Size.Y;
}

Vector2 Rect::GetCenter()
{
	return Position + Size / 2;
}

Rect Rect::SetCenter(Vector2 Center)
{
	return Rect(
		Center - Size / 2,
		Size
	);
}

Rect Rect::Recenter(Vector2 Center)
{
	return Rect(
		Center - Size / 2,
		Size
	);
}

Rect Rect::GetIntersection(Rect O)
{
	using std::min;
	using std::min;

	Vector2 MyExtents = Position + Size;
	Vector2 OExtents = O.Position + O.Size;

	Vector2 IntPos;
	Vector2 IntExt;

	IntPos.X = max(Position.X, O.Position.X);
	IntPos.Y = max(Position.Y, O.Position.Y);
	IntExt.X = min(MyExtents.X, OExtents.X);
	IntExt.Y = min(MyExtents.Y, OExtents.Y);

	return FromExtent(IntPos, IntExt);
}

float Rect::IntersectionArea(Rect O)
{
	return GetIntersection(O).GetArea();
}

bool Rect::Intersects(Rect O)
{
	return IntersectionArea(O) > 0;
}

bool Rect::Contains(Rect O)
{
	Vector2 MyExtents = Position + Size;
	Vector2 OExtents = O.Position + O.Size;

	return Position.X <= O.Position.X &&
		Position.Y <= O.Position.Y &&
		MyExtents.X >= OExtents.X &&
		MyExtents.Y >= OExtents.Y;
}

bool Rect::ContainedBy(Rect O)
{
	return O.Contains(*this);
}

float Rect::GetDiameter()
{
	return sqrt(Size.X * Size.X + Size.Y * Size.Y);
}

Rect Rect::SetDiameter(float Diameter)
{
	float CD = GetDiameter();
	float Ratio = Diameter / CD;
	return *this * Ratio;
}
#pragma endregion

#pragma region Operators
Rect Rect::operator+(Vector2 V)
{
	return Rect(Position + V, Size);
}

Rect Rect::operator-(Vector2 V)
{
	return Rect(Position - V, Size);
}

Rect Rect::operator+(Rect R)
{
	return Rect(Position + R.Position, Size + R.Size);
}

Rect Rect::operator-(Rect R)
{
	return Rect(Position - R.Position, Size - R.Size);
}

Rect Rect::operator*(float F)
{
	auto NewSize = Size * F;
	auto SizeDelta = Size - NewSize;
	return Rect(Position + SizeDelta / 2, NewSize);
}

Rect Rect::operator/(float F)
{
	auto NewSize = Size / F;
	auto SizeDelta = Size - NewSize;
	return Rect(Position + SizeDelta / 2, NewSize);
}
#pragma endregion

#pragma region Conversions
Rect::operator tagRECT()
{
	tagRECT Ret;
	Ret.left = Position.X;
	Ret.top = Position.Y;
	Ret.right = Position.X + Size.X;
	Ret.bottom = Position.Y + Size.Y;
	return Ret;
}

Rect::operator IVector2()
{
	return IVector2(Position);
}

Rect::operator IVector3()
{
	return IVector3(Position.X, Position.Y, 0);
}

Rect::operator Vector2()
{
	return Position;
}

Rect::operator Vector3()
{
	return Vector3(Position.X, Position.Y, 0);
}

Rect::operator IRect()
{
	return IRect((IVector2)Position, (IVector2)Size);
}
#pragma endregion

#pragma region IRect
IRect::IRect(int X, int Y, int W, int H)
{
	Position = IVector2(X, Y);
	Size = IVector2(W, H);
}

IRect::IRect(IVector2 Pos, IVector2 Sz)
{
	Position = Pos;
	Size = Sz;
}

IRect::IRect(Rect Rc)
{
	Position = (IVector2)Rc.Position;
	Size = (IVector2)Rc.Size;
}

IRect::operator tagRECT()
{
	tagRECT Ret;
	Ret.left = Position.X;
	Ret.top = Position.Y;
	Ret.right = Position.X + Size.X;
	Ret.bottom = Position.Y + Size.Y;
	return Ret;
}

IRect::operator IVector2()
{
	return IVector2(Position);
}

IRect::operator IVector3()
{
	return IVector3(Position.X, Position.Y, 0);
}

IRect::operator Vector2()
{
	return Position;
}

IRect::operator Vector3()
{
	return Vector3(Position.X, Position.Y, 0);
}

IRect::operator Rect()
{
	return Rect(Position, Size);
}
#pragma endregion

Rect Rect::Zero = Rect();
IRect IRect::Zero = IRect();