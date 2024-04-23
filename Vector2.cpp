#include "Geometry.hpp"
#define P template <typename T>

#pragma region Constructors
P
Vector2<T>::Vector2()
{
    X = 0;
    Y = 0;
}

P
Vector2<T>::Vector2(T N)
{
    X = N;
    Y = N;
}

P
Vector2<T>::Vector2(T _X, T _Y)
{
    X = _X;
    Y = _Y;
}

P
Vector2<T>::Vector2(Rect<T> R)
{
    X = R.X;
    Y = R.Y;
}

P
Vector2<T>::Vector2(Vector3<T> V3)
{
    X = V3.X;
    Y = V3.Y;
}
#pragma endregion

#pragma region Operators
P
Vector2<T> Vector2<T>::operator+(Vector2<T> Other)
{
    return Vector2<T>(X + Other.X, Y + Other.Y);
}

P
Vector2<T> Vector2<T>::operator-(Vector2<T> Other)
{
    return Vector2<T>(X - Other.X, Y - Other.Y);
}

P
Vector2<T> Vector2<T>::operator*(float F)
{
    return Vector2<T>(X * F, Y * F);
}

P
Vector2<T> Vector2<T>::operator/(float F)
{
    return Vector2<T>(X / F, Y / F);
}

P
void Vector2<T>::operator=(Vector2<T> Other)
{
    X = Other.X;
    Y = Other.Y;
}
#pragma endregion

#pragma region Converters
P
Vector2<T>::operator Vector3<T>()
{
    return Vector3<T>(X, Y, 0);
}

P
Vector2<T>::operator Rect<T>()
{
    return Rect<T>(X, Y, 0, 0);
}
#pragma endregion

#pragma region Methods
P
Vector2<T> Vector2<T>:: Rotate(float Rad)
{
    T NX = X * cos(Rad) - Y * sin(Rad);
    T NY = X * sin(Rad) + Y * cos(Rad);
    return Vector2<T>(NX, NY);
}

P
std::string Vector2<T>::ToString(bool B, bool C)
{
    std::string Result = "";
    if (C) Result = "Vector2";
    if (B) Result += "(";
    Result += std::to_string(X) + ", " + std::to_string(Y);
    if (B) Result += ")";
    return Result;
}

P
float Vector2<T>::GetMagnitude()
{
    return sqrt(X * X + Y * Y);
}

P
Vector2<T> Vector2<T>::Cross(Vector2 Other)
{
    return Vector2<T>(Y * Other.Y, X * Other.X);
}

P
float Vector2<T>::Dot(Vector2 Other) {
    return X * Other.X + Y * Other.Y;
}

P
Vector2<T> Vector2<T>::Lerp(Vector2<T> Target, float Alpha)
{
    return Vector2<T>(
        X + (Target.X - X) * Alpha,
        Y + (Target.Y - Y) * Alpha
    );
}

P
Vector2<T> Vector2<T>::Nudge(Vector2<T> Target, float Amount)
{
    float MagDelta = Target.GetMagnitude() - GetMagnitude();
    return Lerp(Target, Amount / MagDelta);
}

P
Vector2<T> Vector2<T>::SetMagnitude(float NewMag)
{
    auto Direction = Unit();
    return Direction * NewMag;
}

P
Vector2<T> Vector2<T>::Unit()
{
    float Mag = GetMagnitude();
    if (Mag == 0) return Zero;

    return Vector2<T>(
        X / Mag,
        Y / Mag
    );
}

P
Vector2<T> Vector2<T>::Normal(bool Clockwise)
{
    if (Clockwise)
        return Vector2<T>(
            Y,
            -X
        );

    return Vector2<T>(
        -Y,
        X
    );
}

P
Vector2<T> Vector2<T>::RadialLerp(Vector2<T> Target, float Alpha, bool LerpMagnitude) {
    // Calculate the angle between this vector and the target vector
    float Angle = atan2(Target.Y, Target.X) - atan2(Y, X);

    // Ensure the angle is between -pi and pi
    while (Angle > M_PI) Angle -= 2 * M_PI;
    while (Angle <= -M_PI) Angle += 2 * M_PI;

    // Interpolate the angle
    float LerpedAngle = Angle * Alpha;

    // Calculate the new direction vector
    float NewX = cos(atan2(Y, X) + LerpedAngle);
    float NewY = sin(atan2(Y, X) + LerpedAngle);

    // Optionally interpolate the magnitude
    if (LerpMagnitude)
    {
        float MagnitudeDifference = Target.GetMagnitude() - GetMagnitude();
        float LerpedMagnitude = GetMagnitude() + MagnitudeDifference * Alpha;
        return Vector2<T>(NewX * LerpedMagnitude, NewY * LerpedMagnitude);
    }
    else
    {
        return Vector2<T>(NewX, NewY);
    }
}
#pragma endregion

template<>
Vector2<int> Vector2<int>::Zero = Vector2<int>();

template<>
Vector2<float> Vector2<float>::Zero = Vector2<float>();

template<>
Vector2<double> Vector2<double>::Zero = Vector2<double>();

template<>
Vector2<short> Vector2<short>::Zero = Vector2<short>();

template<>
Vector2<char> Vector2<char>::Zero = Vector2<char>();