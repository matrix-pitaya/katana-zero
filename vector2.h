#pragma once
#include<cmath>
class Vector2
{
public:
	float x = 0;
	float y = 0;

	Vector2 operator-(const Vector2& vec)
	{
		return Vector2(x - vec.x, y - vec.y);
	}
	Vector2 operator*(float val)
	{
		return Vector2(x * val, y * val);
	}
	float length()
	{
		return sqrt(x * x + y * y);
	}
	Vector2 normalize()
	{
		float len = length();
		if (len == 0)
		{
			return Vector2(0, 0);
		}
		return Vector2(x / len, y / len);
	}

	Vector2() = default;
	~Vector2() = default;
	Vector2(float x, float y) :x(x), y(y){}
};