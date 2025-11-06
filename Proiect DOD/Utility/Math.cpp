#include "Math.h"

float Length(const Vector2& v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

float Distance(const Vector2& a, const Vector2& b)
{
	return Length(Vector2(b.x - a.x, b.y - a.y));
}

Vector2 Normalize(const Vector2& v)
{
	float len = Length(v);
	if (len == 0) return Vector2(0, 0);
	return Vector2(v.x / len, v.y / len);
}

float Dot(const Vector2& a, const Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}