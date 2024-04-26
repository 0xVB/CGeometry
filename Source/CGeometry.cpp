#pragma once
#include "CGeometry.h"
float CGeometry::ClampAngle(float Angle)
{
	while (Angle > M_PI) Angle -= 2 * M_PI;
	while (Angle <= -M_PI) Angle += 2 * M_PI;
	return Angle;
}

float CGeometry::Clamp(float Value, float Min, float Max)
{
	return (Value > Max) ? Max : (Value < Min) ? Min : Value;
}