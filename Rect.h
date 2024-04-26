#pragma once
#include "CGeometry.h"
#include <Windows.h>

struct CGeometry::Rect
{
	Vector2 Position;
	Vector2 Size;

	Rect(float X = 0, float Y = 0, float Width = 0, float Height = 0);
	Rect(Vector2 Position, Vector2 Size = Vector2::Zero);
	
	static Rect FromCenter(float CenterX = 0, float CenterY = 0, float Width = 0, float Height = 0);
	static Rect FromCenter(Vector2 Center, Vector2 Size = Vector2::Zero);
	static Rect FromExtent(Vector2 Min, Vector2 Max);

	// Returns the area.
	float GetArea();
	// Returns the perimeter.
	float GetPerimeter();
	// Returns the center of this rectangle.
	Vector2 GetCenter();
	// Returns a rectangle with the same width and height, with its center set at the new center.
	Rect SetCenter(Vector2 NewCenter);
	// Equivalent to SetCenter.
	Rect Recenter(Vector2 NewCenter);
	// Returns the rectangle of intersection between the two rectangles. If the rectangles do not intersect, the returned rect will have an area of 0.
	Rect GetIntersection(Rect Other);
	// Returns true if the two rectangles intersect.
	bool Intersects(Rect Other);
	// Returns the area of the intersection between the 2 rectangles. Returns 0 if they do not intersect.
	float IntersectionArea(Rect Other);
	// Returns true if this rect contains the other rectangle completely.
	bool Contains(Rect Other);
	// Returns true if this rect is contained by the other rectangle completely.
	bool ContainedBy(Rect Other);
	// Returns the diameter of a circle inscribed in this rectangle.
	float GetDiameter();
	// Returns a rectangle with the same center and widht:height ratio as this one, but resized to fit a circle with the given diameter.
	Rect SetDiameter(float NewDiameter);

	operator tagRECT();

	operator IVector2();
	operator IVector3();
	operator Vector2();
	operator Vector3();
	operator IRect();

	Rect operator+(Vector2);
	Rect operator-(Vector2);
	Rect operator*(float);
	Rect operator/(float);
	Rect operator+(Rect);
	Rect operator-(Rect);

	static Rect Zero;
};

struct CGeometry::IRect
{
	IVector2 Position;
	IVector2 Size;

	IRect(int X = 0, int Y = 0, int W = 0, int H = 0);
	IRect(IVector2 Position, IVector2 Size);
	IRect(Rect);

	operator tagRECT();

	operator IVector2();
	operator IVector3();
	operator Vector2();
	operator Vector3();
	operator Rect();

	static IRect Zero;
};