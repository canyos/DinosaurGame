#pragma once
#include "CommonInclude.h"

namespace p
{
	namespace math{
#define PI 3.141592f		
		static float ConvertDegree(float radian) { return (radian*(180 / PI)); }
		struct Vector2
		{
			static Vector2 Rotate(Vector2 vector, float degree) {
				float radian = (degree / 180.0f)*PI;
				vector = vector.normalize();
				float x = cosf(radian) * vector.x - sinf(radian) *vector.y;
				float y = cosf(radian) * vector.x + sinf(radian) *vector.y;

				return Vector2(x, y);
			}
			static float Dot(Vector2& v1, Vector2& v2) {
				return v1.x * v2.x + v1.y * v2.y;
			}
			static float Cross(Vector2& v1, Vector2& v2) {
				return v1.x * v2.y - v1.y * v2.x;
			}

			static Vector2 One;
			static Vector2 Zero;
			static Vector2 Right;
			static Vector2 Left;
			static Vector2 Up;
			static Vector2 Down;

			float x;
			float y;

			Vector2()
				: x(0.0f)
				, y(0.0f)
			{

			}

			Vector2(float _x, float _y)
				: x(_x)
				, y(_y)
			{

			}
			Vector2 operator+(Vector2 other) {
				return Vector2(x + other.x, y + other.y);
			}
			void operator+=(Vector2 other) {
				x += other.x, y += other.y;
			}
			void operator-=(Vector2 other) {
				x -= other.x, y -= other.y;
			}
			void operator*=(Vector2 other) {
				x *= other.x, y *= other.y;
			}
			void operator*=(float f) {
				x *= f, y *= f;
			}
			Vector2 operator-() {
				return Vector2(-x,-y);
			}
			Vector2 operator-(Vector2 other) {
				return Vector2(x - other.x, y - other.y);
			}
			Vector2 operator* (float f) {
				return Vector2(x * f, y * f);
			}
			Vector2 operator*(Vector2 v) {
				return Vector2(x * v.x, y * v.y);
			}
			Vector2 operator/(float f) {
				return Vector2(x /f, y/f);
			}
			bool operator==(Vector2 other) {
				return x == other.x && y == other.y;
			}
			void clear() {
				x = 0.0f;
				y = 0.0f;
			}

			float length() {
				return sqrt(x*x + y * y);
			}

			Vector2 normalize() {
				float len = length();
				x /= len;
				y /= len;

				return *this;
			}
			
		};

	}
}

