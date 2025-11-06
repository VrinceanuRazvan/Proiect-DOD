#pragma once

#include <cmath>
#include "Vector2.h"

float Length(const Vector2& v);
float Distance(const Vector2& a, const Vector2& b);
Vector2 Normalize(const Vector2& v);
float Dot(const Vector2& a, const Vector2& b);