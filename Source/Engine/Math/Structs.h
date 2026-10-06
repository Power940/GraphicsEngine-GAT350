#pragma once
#include "Constants.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ostream>


namespace STR_FALL
{
	struct Vector2;
	struct Vector3;
	struct Vector4;
	struct Matrix2;
	struct Matrix3;
	struct Matrix4;
	struct VertexUV3D;

	struct Vector2
	{
		float m_x;
		float m_y;

		inline Vector2(const float x = 0.0f, const float y = 0.0f) : m_x(x), m_y(y) {}
		inline Vector2(const Vector2& ip, const Vector2& fp) : m_x(fp.m_x - ip.m_x), m_y(fp.m_y - ip.m_y) {}
		Vector2(const Vector3& vect);
		Vector2(const Vector4& vect);

		float operator[](const unsigned int element) const { assert(element < 2); return (&m_x)[element]; }
		float& operator[](const unsigned int element) { assert(element < 2); return (&m_x)[element]; }

		inline Vector2 operator+(const Vector2& rhs) const { return Vector2(m_x + rhs.m_x, m_y + rhs.m_y); }
		inline Vector2 operator-(const Vector2& rhs) const { return Vector2(m_x - rhs.m_x, m_y - rhs.m_y); }
		inline Vector2 operator*(const Vector2& rhs) const { return Vector2(m_x * rhs.m_x, m_y * rhs.m_y); }
		inline Vector2 operator/(const Vector2& rhs) const { return Vector2(m_x / rhs.m_x, m_y / rhs.m_y); }
		inline Vector2 operator%(const Vector2& rhs) const { return Vector2(fmod(m_x, rhs.m_x), fmod(m_y, rhs.m_y)); }

		inline Vector2 operator+(const float rhs) const { return Vector2(m_x + rhs, m_y + rhs); }
		inline Vector2 operator-(const float rhs) const { return Vector2(m_x - rhs, m_y - rhs); }
		inline Vector2 operator*(const float rhs) const { return Vector2(m_x * rhs, m_y * rhs); }
		inline Vector2 operator/(const float rhs) const { return Vector2(m_x / rhs, m_y / rhs); }
		inline Vector2 operator%(const float rhs) const { return Vector2(fmod(m_x, rhs), fmod(m_y, rhs)); }

		inline Vector2& operator+=(const Vector2& rhs) { m_x += rhs.m_x; m_y += rhs.m_y; return *this; }
		inline Vector2& operator-=(const Vector2& rhs) { m_x -= rhs.m_x; m_y -= rhs.m_y; return *this; }
		inline Vector2& operator*=(const Vector2& rhs) { m_x *= rhs.m_x; m_y *= rhs.m_y; return *this; }
		inline Vector2& operator/=(const Vector2& rhs) { m_x /= rhs.m_x; m_y /= rhs.m_y; return *this; }
		inline Vector2& operator%=(const Vector2& rhs) { m_x = fmod(m_x, rhs.m_x); m_y = fmod(m_y, rhs.m_y); return *this; }

		inline Vector2& operator+=(const float rhs) { m_x += rhs; m_y += rhs; return *this; }
		inline Vector2& operator-=(const float rhs) { m_x -= rhs; m_y -= rhs; return *this; }
		inline Vector2& operator*=(const float rhs) { m_x *= rhs; m_y *= rhs; return *this; }
		inline Vector2& operator/=(const float rhs) { m_x /= rhs; m_y /= rhs; return *this; }
		inline Vector2& operator%=(const float rhs) { m_x = fmod(m_x, rhs); m_y = fmod(m_y, rhs); return *this; }

		Vector2 operator*(const Matrix2& rhs) const;
		Vector2& operator*=(const Matrix2& rhs);

		inline bool operator==(const Vector2& rhs) const { return (m_x == rhs.m_x) && (m_y == rhs.m_y); }
		inline bool operator!=(const Vector2& rhs) const { return (m_x != rhs.m_x) || (m_y != rhs.m_y); }

		inline friend std::ostream& operator<<(std::ostream& os, const Vector2& rhs) { os << "X: " << rhs.m_x << " | Y: " << rhs.m_y; return os; }

		inline void Clamp(const float min, const float max) { m_x = std::clamp(m_x, min, max); m_y = std::clamp(m_y, min, max); }
		inline void ClampMag(const float min, const float max)
		{
			if (Magnitude() > max) { m_x = (Normalize() * max).m_x; m_y = (Normalize() * max).m_y; }
			if (Magnitude() < min) { m_x = (Normalize() * min).m_x; m_y = (Normalize() * min).m_y; }
		}
		inline void ClampX(const float min, const float max) { m_x = std::clamp(m_x, min, max); }
		inline void ClampY(const float min, const float max) { m_y = std::clamp(m_y, min, max); }

		inline float Magnitude() const { return std::sqrt((m_x * m_x) + (m_y * m_y)); }
		inline float MagnitudeSqr() const { return (m_x * m_x) + (m_y * m_y); }
		inline float Dot(const Vector2& vect) const { return m_x * vect.m_x + m_y * vect.m_y; }
		inline float AngleBetween(const Vector2& vect) const { return std::acos(Dot(vect)); }
		inline float Angle() const { return std::atan2(m_y, m_x); }
		inline float Distance(const Vector2& vect) const
		{
			float dx = vect.m_x - m_x; float dy = vect.m_y - m_y;
			return std::sqrt(dx * dx + dy * dy);
		}
		inline Vector2 Normalize() const
		{
			float mag = std::sqrt((m_x * m_x) + (m_y * m_y));
			return (mag == 0.0f) ? Vector2() : *this / mag;
		}
		inline Vector2 Lerp(const Vector2& vect, const float t = 0.5f) const { return *this + (vect - *this) * t; }
		Vector2 Rotate(const float rad) const;
	};

	struct Vector3
	{
		float m_x;
		float m_y;
		float m_z;

		inline Vector3(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f) : m_x(x), m_y(y), m_z(z) {}
		inline Vector3(const Vector3& ip, const Vector3& fp) : m_x(fp.m_x - ip.m_x), m_y(fp.m_y - ip.m_y), m_z(fp.m_z - ip.m_z) {}
		Vector3(const Vector2& vect);
		Vector3(const Vector4& vect);
		Vector3(const VertexUV3D& vect);

		float operator[](const unsigned int element) const { assert(element < 3); return (&m_x)[element]; }
		float& operator[](const unsigned int element) { assert(element < 3); return (&m_x)[element]; }

		inline Vector3 operator+(const Vector3& rhs) const { return Vector3(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z); }
		inline Vector3 operator-(const Vector3& rhs) const { return Vector3(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z); }
		inline Vector3 operator*(const Vector3& rhs) const { return Vector3(m_x * rhs.m_x, m_y * rhs.m_y, m_z * rhs.m_z); }
		inline Vector3 operator/(const Vector3& rhs) const { return Vector3(m_x / rhs.m_x, m_y / rhs.m_y, m_z / rhs.m_z); }
		inline Vector3 operator%(const Vector3& rhs) const { return Vector3(fmod(m_x, rhs.m_x), fmod(m_y, rhs.m_y), fmod(m_z, rhs.m_z)); }

		inline Vector3 operator+(const float rhs) const { return Vector3(m_x + rhs, m_y + rhs, m_z + rhs); }
		inline Vector3 operator-(const float rhs) const { return Vector3(m_x - rhs, m_y - rhs, m_z - rhs); }
		inline Vector3 operator*(const float rhs) const { return Vector3(m_x * rhs, m_y * rhs, m_z * rhs); }
		inline Vector3 operator/(const float rhs) const { return Vector3(m_x / rhs, m_y / rhs, m_z / rhs); }
		inline Vector3 operator%(const float rhs) const { return Vector3(fmod(m_x, rhs), fmod(m_y, rhs), fmod(m_z, rhs)); }

		inline Vector3& operator+=(const Vector3& rhs) { m_x += rhs.m_x; m_y += rhs.m_y, m_z += rhs.m_z; return *this; }
		inline Vector3& operator-=(const Vector3& rhs) { m_x -= rhs.m_x; m_y -= rhs.m_y, m_z -= rhs.m_z; return *this; }
		inline Vector3& operator*=(const Vector3& rhs) { m_x *= rhs.m_x; m_y *= rhs.m_y, m_z *= rhs.m_z; return *this; }
		inline Vector3& operator/=(const Vector3& rhs) { m_x /= rhs.m_x; m_y /= rhs.m_y, m_z /= rhs.m_z; return *this; }
		inline Vector3& operator%=(const Vector3& rhs) { m_x = fmod(m_x, rhs.m_x); m_y = fmod(m_y, rhs.m_y); m_z = fmod(m_z, rhs.m_z); return *this; }

		inline Vector3& operator+=(const float rhs) { m_x += rhs; m_y += rhs, m_z += rhs; return *this; }
		inline Vector3& operator-=(const float rhs) { m_x -= rhs; m_y -= rhs, m_z -= rhs; return *this; }
		inline Vector3& operator*=(const float rhs) { m_x *= rhs; m_y *= rhs, m_z *= rhs; return *this; }
		inline Vector3& operator/=(const float rhs) { m_x /= rhs; m_y /= rhs, m_z /= rhs; return *this; }
		inline Vector3& operator%=(const float rhs) { m_x = fmod(m_x, rhs); m_y = fmod(m_y, rhs); m_z = fmod(m_z, rhs); return *this; }

		Vector3 operator*(const Matrix3& rhs) const;
		Vector3& operator*=(const Matrix3& rhs);

		inline bool operator==(const Vector3& rhs) const { return (m_x == rhs.m_x) && (m_y == rhs.m_y) && (m_z == rhs.m_z); }
		inline bool operator!=(const Vector3& rhs) const { return (m_x != rhs.m_x) || (m_y != rhs.m_y) || (m_z != rhs.m_z); }

		friend std::ostream& operator<<(std::ostream& os, const Vector3& rhs) { os << "X: " << rhs.m_x << " | Y: " << rhs.m_y << " | Z: " << rhs.m_z; return os; }

		inline void Clamp(const float min, const float max) { m_x = std::clamp(m_x, min, max); m_y = std::clamp(m_y, min, max); m_z = std::clamp(m_z, min, max); }
		inline void ClampMag(const float min, const float max)
		{
			if (Magnitude() > max) { m_x = (Normalize() * max).m_x; m_y = (Normalize() * max).m_y; m_z = (Normalize() * max).m_z; }
			if (Magnitude() < min) { m_x = (Normalize() * min).m_x; m_y = (Normalize() * min).m_y; m_z = (Normalize() * min).m_z; }
		}
		inline void ClampX(const float min, const float max) { m_x = std::clamp(m_x, min, max); }
		inline void ClampY(const float min, const float max) { m_y = std::clamp(m_y, min, max); }
		inline void ClampZ(const float min, const float max) { m_z = std::clamp(m_z, min, max); }

		inline float Magnitude() const { return std::sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z)); }
		inline float MagnitudeSqr() const { return (m_x * m_x) + (m_y * m_y) + (m_z * m_z); }
		inline float Dot(const Vector3& vect) const { return m_x * vect.m_x + m_y * vect.m_y + m_z * vect.m_z; }
		inline float Angle(const Vector3& vect) const { return std::acos(Dot(vect)); }
		inline float Distance(const Vector3& vect) const
		{
			float dx = vect.m_x - m_x;
			float dy = vect.m_y - m_y;
			float dz = vect.m_z - m_z;
			return std::sqrt(dx * dx + dy * dy + dz * dz);
		}
		inline Vector3 Cross(const Vector3& vect) const
		{
			return Vector3(
				m_y * vect.m_z - m_z * vect.m_y,
				m_z * vect.m_x - m_x * vect.m_z,
				m_x * vect.m_y - m_y * vect.m_x
			);
		}
		inline Vector3 Normalize() const
		{
			float mag = std::sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z));
			return (mag == 0.0f) ? Vector3() : *this / mag;
		}
		inline Vector3 Lerp(const Vector3& vect, const float t = 0.5f) const { return *this + (vect - *this) * t; }
	};

	struct Vector4
	{
		float m_x;
		float m_y;
		float m_z;
		float m_w;

		inline Vector4(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f, const float w = 0.0f) : m_x(x), m_y(y), m_z(z), m_w(w) {}
		inline Vector4(const Vector4& ip, const Vector4& fp) : m_x(fp.m_x - ip.m_x), m_y(fp.m_y - ip.m_y), m_z(fp.m_z - ip.m_z), m_w(fp.m_w - ip.m_w) {}
		Vector4(const Vector2& vect);
		Vector4(const Vector3& vect);

		float operator[](const unsigned int element) const { assert(element < 4); return (&m_x)[element]; }
		float& operator[](const unsigned int element) { assert(element < 4); return (&m_x)[element]; }

		inline Vector4 operator+(const Vector4& rhs) const { return Vector4(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z, m_w + rhs.m_w); }
		inline Vector4 operator-(const Vector4& rhs) const { return Vector4(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z, m_w - rhs.m_w); }
		inline Vector4 operator*(const Vector4& rhs) const { return Vector4(m_x * rhs.m_x, m_y * rhs.m_y, m_z * rhs.m_z, m_w * rhs.m_w); }
		inline Vector4 operator/(const Vector4& rhs) const { return Vector4(m_x / rhs.m_x, m_y / rhs.m_y, m_z / rhs.m_z, m_w / rhs.m_w); }
		inline Vector4 operator%(const Vector4& rhs) const { return Vector4(fmod(m_x, rhs.m_x), fmod(m_y, rhs.m_y), fmod(m_z, rhs.m_z), fmod(m_w, rhs.m_w)); }

		inline Vector4 operator+(const float rhs) const { return Vector4(m_x + rhs, m_y + rhs, m_z + rhs, m_w + rhs); }
		inline Vector4 operator-(const float rhs) const { return Vector4(m_x - rhs, m_y - rhs, m_z - rhs, m_w - rhs); }
		inline Vector4 operator*(const float rhs) const { return Vector4(m_x * rhs, m_y * rhs, m_z * rhs, m_w * rhs); }
		inline Vector4 operator/(const float rhs) const { return Vector4(m_x / rhs, m_y / rhs, m_z / rhs, m_w / rhs); }
		inline Vector4 operator%(const float rhs) const { return Vector4(fmod(m_x, rhs), fmod(m_y, rhs), fmod(m_z, rhs), fmod(m_w, rhs)); }

		inline Vector4& operator+=(const Vector4& rhs) { m_x += rhs.m_x; m_y += rhs.m_y; m_z += rhs.m_z; m_w += rhs.m_w; return *this; }
		inline Vector4& operator-=(const Vector4& rhs) { m_x -= rhs.m_x; m_y -= rhs.m_y; m_z -= rhs.m_z; m_w -= rhs.m_w; return *this; }
		inline Vector4& operator*=(const Vector4& rhs) { m_x *= rhs.m_x; m_y *= rhs.m_y; m_z *= rhs.m_z; m_w *= rhs.m_w; return *this; }
		inline Vector4& operator/=(const Vector4& rhs) { m_x /= rhs.m_x; m_y /= rhs.m_y; m_z /= rhs.m_z; m_w /= rhs.m_w; return *this; }
		inline Vector4& operator%=(const Vector4& rhs) { m_x = fmod(m_x, rhs.m_x); m_y = fmod(m_y, rhs.m_y); m_z = fmod(m_z, rhs.m_z); m_w = fmod(m_w, rhs.m_w); return *this; }

		inline Vector4& operator+=(const float rhs) { m_x += rhs; m_y += rhs; m_z += rhs; m_w += rhs; return *this; }
		inline Vector4& operator-=(const float rhs) { m_x -= rhs; m_y -= rhs; m_z -= rhs; m_w -= rhs; return *this; }
		inline Vector4& operator*=(const float rhs) { m_x *= rhs; m_y *= rhs; m_z *= rhs; m_w *= rhs; return *this; }
		inline Vector4& operator/=(const float rhs) { m_x /= rhs; m_y /= rhs; m_z /= rhs; m_w /= rhs; return *this; }
		inline Vector4& operator%=(const float rhs) { m_x = fmod(m_x, rhs); m_y = fmod(m_y, rhs); m_z = fmod(m_z, rhs); m_w = fmod(m_w, rhs); return *this; }

		inline bool operator==(const Vector4& rhs) const { return (m_x == rhs.m_x) && (m_y == rhs.m_y) && (m_z == rhs.m_z) && (m_w == rhs.m_w); }
		inline bool operator!=(const Vector4& rhs) const { return (m_x != rhs.m_x) || (m_y != rhs.m_y) || (m_z != rhs.m_z) || (m_w != rhs.m_w); }

		friend std::ostream& operator<<(std::ostream& os, const Vector4& rhs) { os << "X: " << rhs.m_x << " | Y: " << rhs.m_y << " | Z: " << rhs.m_z << " | W: " << rhs.m_w; return os; }

		inline void Clamp(const float min, const float max) { m_x = std::clamp(m_x, min, max); m_y = std::clamp(m_y, min, max); m_z = std::clamp(m_z, min, max); m_w = std::clamp(m_w, min, max); }
		inline void ClampMag(const float min, const float max)
		{
			if (Magnitude() > max) { m_x = (Normalize() * max).m_x; m_y = (Normalize() * max).m_y; m_z = (Normalize() * max).m_z; m_w = (Normalize() * max).m_w; }
			if (Magnitude() < min) { m_x = (Normalize() * min).m_x; m_y = (Normalize() * min).m_y; m_z = (Normalize() * min).m_z; m_w = (Normalize() * min).m_w; }
		}
		inline void ClampX(const float min, const float max) { m_x = std::clamp(m_x, min, max); }
		inline void ClampY(const float min, const float max) { m_y = std::clamp(m_y, min, max); }
		inline void ClampZ(const float min, const float max) { m_z = std::clamp(m_z, min, max); }
		inline void ClampW(const float min, const float max) { m_w = std::clamp(m_w, min, max); }

		inline float Magnitude() const { return std::sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z) + (m_w * m_w)); }
		inline float Dot(const Vector4& vect) const { return m_x * vect.m_x + m_y * vect.m_y + m_z * vect.m_z + m_w * vect.m_w; }
		inline float Distance(const Vector4& vect) const
		{
			float dx = vect.m_x - m_x;
			float dy = vect.m_y - m_y;
			float dz = vect.m_z - m_z;
			float dw = vect.m_w - m_w;
			return std::sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
		}
		inline Vector4 Normalize() const
		{
			float mag = std::sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z) + (m_w * m_w));
			return (mag == 0.0f) ? Vector4() : *this / mag;
		}
		inline Vector4 Lerp(const Vector4& vect, const float t = 0.5f) const { return *this + (vect - *this) * t; }
	};

	struct Matrix2
	{
		float m_m[2][2];

		inline Matrix2()
		{
			m_m[0][0] = 1; m_m[0][1] = 0;
			m_m[1][0] = 0; m_m[1][1] = 1;
		}
		inline Matrix2(float val)
		{
			m_m[0][0] = val; m_m[0][1] = val;
			m_m[1][0] = val; m_m[1][1] = val;
		}
		inline Matrix2(float m00, float m01, float m10, float m11)
		{
			m_m[0][0] = m00; m_m[0][1] = m01;
			m_m[1][0] = m10; m_m[1][1] = m11;
		}
		Matrix2(const Matrix3& m);

		inline float* operator[](int element) { return m_m[element]; }
		inline const float* operator[](int element) const { return m_m[element]; }
		inline Matrix2 operator*(const Matrix2& rhs) const
		{
			return Matrix2(
				m_m[0][0] * rhs[0][0] + m_m[0][1] * rhs[1][0], m_m[0][0] * rhs[0][1] + m_m[0][1] * rhs[1][1],
				m_m[1][0] * rhs[0][0] + m_m[1][1] * rhs[1][0], m_m[1][0] * rhs[0][1] + m_m[1][1] * rhs[1][1]
			);
		}
		inline Vector2 operator*(const Vector2& vect) const
		{
			return Vector2(
				m_m[0][0] * vect.m_x + m_m[0][1] * vect.m_y,
				m_m[1][0] * vect.m_x + m_m[1][1] * vect.m_y
			);
		}

		inline Matrix2 Abs() const
		{
			return Matrix2(
				std::abs(m_m[0][0]), std::abs(m_m[0][1]),
				std::abs(m_m[1][0]), std::abs(m_m[1][1])
			);
		}

		inline Vector2 Right() const { return Vector2(m_m[0][0], m_m[1][0]); }
		inline Vector2 Up() const { return Vector2(m_m[0][1], m_m[1][1]); }

		static Matrix2 RotationXY(float r)
		{
			float c = std::cos(r);
			float s = std::sin(r);
			return Matrix2
			(
				c, s,
				-s, c
			);
		}
	};

	struct Matrix3
	{
		float m_m[3][3];

		inline Matrix3()
		{
			m_m[0][0] = 1; m_m[0][1] = 0; m_m[0][2] = 0;
			m_m[1][0] = 0; m_m[1][1] = 1; m_m[1][2] = 0;
			m_m[2][0] = 0; m_m[2][1] = 0; m_m[2][2] = 1;
		}
		inline Matrix3(float val)
		{
			m_m[0][0] = val; m_m[0][1] = val; m_m[0][2] = val;
			m_m[1][0] = val; m_m[1][1] = val; m_m[1][2] = val;
			m_m[2][0] = val; m_m[2][1] = val; m_m[2][2] = val;
		}
		inline Matrix3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
		{
			m_m[0][0] = m00; m_m[0][1] = m01; m_m[0][2] = m02;
			m_m[1][0] = m10; m_m[1][1] = m11; m_m[1][2] = m12;
			m_m[2][0] = m20; m_m[2][1] = m21; m_m[2][2] = m22;
		}
		Matrix3(const Matrix2& m);

		inline float* operator[](int element) { return m_m[element]; }
		inline const float* operator[](int element) const { return m_m[element]; }
		inline Matrix3 operator*(const Matrix3& rhs) const
		{
			return Matrix3(
				m_m[0][0] * rhs[0][0] + m_m[0][1] * rhs[1][0] + m_m[0][2] * rhs[2][0], m_m[0][0] * rhs[0][1] + m_m[0][1] * rhs[1][1] + m_m[0][2] * rhs[2][1], m_m[0][0] * rhs[0][2] + m_m[0][1] * rhs[1][2] + m_m[0][2] * rhs[2][2],
				m_m[1][0] * rhs[0][0] + m_m[1][1] * rhs[1][0] + m_m[1][2] * rhs[2][0], m_m[1][0] * rhs[0][1] + m_m[1][1] * rhs[1][1] + m_m[1][2] * rhs[2][1], m_m[1][0] * rhs[0][2] + m_m[1][1] * rhs[1][2] + m_m[1][2] * rhs[2][2],
				m_m[2][0] * rhs[0][0] + m_m[2][1] * rhs[1][0] + m_m[2][2] * rhs[2][0], m_m[2][0] * rhs[0][1] + m_m[2][1] * rhs[1][1] + m_m[2][2] * rhs[2][1], m_m[2][0] * rhs[0][2] + m_m[2][1] * rhs[1][2] + m_m[2][2] * rhs[2][2]
			);
		}
		inline Vector3 operator*(const Vector3& vect) const
		{
			return Vector3(
				m_m[0][0] * vect.m_x + m_m[0][1] * vect.m_y + m_m[0][2] * vect.m_z,
				m_m[1][0] * vect.m_x + m_m[1][1] * vect.m_y + m_m[1][2] * vect.m_z,
				m_m[2][0] * vect.m_x + m_m[2][1] * vect.m_y + m_m[2][2] * vect.m_z
			);
		}

		inline Matrix3 Abs() const
		{
			return Matrix3(
				std::abs(m_m[0][0]), std::abs(m_m[0][1]), std::abs(m_m[0][2]),
				std::abs(m_m[1][0]), std::abs(m_m[1][1]), std::abs(m_m[1][2]),
				std::abs(m_m[2][0]), std::abs(m_m[2][1]), std::abs(m_m[2][2])
			);
		}

		inline Vector3 Right() const { return Vector3(m_m[0][0], m_m[1][0], m_m[2][0]); }
		inline Vector3 Up() const { return Vector3(m_m[0][1], m_m[1][1], m_m[2][1]); }
		inline Vector3 Forward() const { return Vector3(m_m[0][2], m_m[1][2], m_m[2][2]); }

		static Matrix3 RotationX(float r)
		{
			float c = std::cos(r);
			float s = std::sin(r);
			return Matrix3
			(
				1, 0, 0,
				0, c, -s,
				0, s, c
			);
		}
		static Matrix3 RotationY(float r)
		{
			float c = std::cos(r);
			float s = std::sin(r);
			return Matrix3
			(
				c, 0, s,
				0, 1, 0,
				-s, 0, c
			);
		}
		static Matrix3 RotationZ(float r)
		{
			float c = std::cos(r);
			float s = std::sin(r);
			return Matrix3
			(
				c, -s, 0,
				s, c, 0,
				0, 0, 1
			);
		}
		static Matrix3 RotationXYZ(float rx, float ry, float rz)
		{
			float cx = std::cos(rx);
			float sx = std::sin(rx);
			float cy = std::cos(ry);
			float sy = std::sin(ry);
			float cz = std::cos(rz);
			float sz = std::sin(rz);

			return Matrix3(
				cz * cy,
				cz * sy * sx - sz * cx,
				cz * sy * cx + sz * sx,
				sz * cy,
				sz * sy * sx + cz * cx,
				sz * sy * cx - cz * sx,
				-sy,
				cy * sx,
				cy * cx
			);
		}
		static Matrix3 RotationXYZ(const Vector3& r)
		{
			float cx = std::cos(r.m_x);
			float sx = std::sin(r.m_x);
			float cy = std::cos(r.m_y);
			float sy = std::sin(r.m_y);
			float cz = std::cos(r.m_z);
			float sz = std::sin(r.m_z);

			return Matrix3(
				cz * cy,
				cz * sy * sx - sz * cx,
				cz * sy * cx + sz * sx,
				sz * cy,
				sz * sy * sx + cz * cx,
				sz * sy * cx - cz * sx,
				-sy,
				cy * sx,
				cy * cx
			);
		}
		static Matrix3 RotationAxis(const Vector3& axis, float r)
		{
			float c = std::cos(r);
			float s = std::sin(r);
			float t = 1.0f - c;

			return Matrix3(
				t * axis.m_x * axis.m_x + c,
				t * axis.m_x * axis.m_y - s * axis.m_z,
				t * axis.m_x * axis.m_z + s * axis.m_y,

				t * axis.m_x * axis.m_y + s * axis.m_z,
				t * axis.m_y * axis.m_y + c,
				t * axis.m_y * axis.m_z - s * axis.m_x,

				t * axis.m_x * axis.m_z - s * axis.m_y,
				t * axis.m_y * axis.m_z + s * axis.m_x,
				t * axis.m_z * axis.m_z + c
			);
		}
	};

	// Add later if you feel like it
	//struct Matrix4
	//{
	//
	//};

	struct Triangle2D
	{
		Vector2 m_a;
		Vector2 m_b;
		Vector2 m_c;

		inline Triangle2D(const Vector2& a = Vector2(), const Vector2& b = Vector2(), const Vector2& c = Vector2()) : m_a(a), m_b(b), m_c(c) {}

		inline Vector2& operator[](int element)
		{
			if (element == 0) { return m_a; }
			if (element == 1) { return m_b; }
			if (element == 2) { return m_c; }
			return m_a;
		}
		const inline Vector2& operator[](int element) const
		{
			if (element == 0) { return m_a; }
			if (element == 1) { return m_b; }
			if (element == 2) { return m_c; }
			return m_a;
		}
	};

	struct Triangle3D
	{
		Vector3 m_a;
		Vector3 m_b;
		Vector3 m_c;

		inline Triangle3D(const Vector3& a = Vector3(), const Vector3& b = Vector3(), const Vector3& c = Vector3()) : m_a(a), m_b(b), m_c(c) {}

		inline Vector3& operator[](int element)
		{
			if (element == 0) { return m_a; }
			if (element == 1) { return m_b; }
			if (element == 2) { return m_c; }
			return m_a;
		}
		const inline Vector3& operator[](int element) const
		{
			if (element == 0) { return m_a; }
			if (element == 1) { return m_b; }
			if (element == 2) { return m_c; }
			return m_a;
		}

		inline Vector3 Normal() const
		{
			return Vector3(m_b, m_a).Cross(Vector3(m_b, m_c)).Normalize();
		}
	};

	struct Transform3D
	{
	public:
		Vector3 m_pos;
		Vector3 m_scale;
		Matrix3 m_rotMat;

		inline Transform3D(const Vector3& pos = Vector3(), const Vector3& scale = Vector3(1.0f, 1.0f, 1.0f), const Matrix3& rotMat = Matrix3()) :
			m_pos(pos), m_scale(scale), m_rotMat(rotMat) {
		}
	};

	struct Camera3D
	{
		static Camera3D Empty;
		Transform3D m_transform;
		float m_fov;
		Vector2 m_ScreenDim;
		float m_aspect;
		float m_fovScaling;

		inline Camera3D(const Transform3D& t = Transform3D(), const float fov = 90, const Vector2& screenDim = Vector2(256, 144)):
			m_transform(t), m_fov(fov), m_ScreenDim(screenDim),
			m_aspect(screenDim.m_x / screenDim.m_y),
			m_fovScaling(1 / std::tan((m_fov / 2) * F_DEG_RAD)) {}
	};

	struct Color : Vector4
	{
		inline Color(const float r = 1.0f, const float g = 1.0f, const float b = 1.0f, const float a = 1.0f) : Vector4(r, g, b, a) {}
		inline Color(const Vector4& rgba) : Vector4(rgba) {}
	};

	struct Vector2C : Vector2
	{
		Color m_color;

		inline Vector2C(float x, float y, const Color& color) : Vector2(x, y), m_color(color) {}
		inline Vector2C(const Vector2& p, const Color& color) : Vector2(p.m_x, p.m_y), m_color(color) {}
	};

	struct Line2D
	{
		Vector2 m_1;
		Vector2 m_2;

		inline Line2D(const Vector2& p1, const Vector2& p2) : m_1(p1), m_2(p2) {}
	};

	struct Line2DC : Line2D
	{
		Color m_color;

		inline Line2DC(const Vector2& p1, const Vector2& p2, const Color& color) : Line2D(p1, p2), m_color(color) {}
	};

	struct Triangle2DC : Triangle2D
	{
		Color m_color;

		inline Triangle2DC(const Vector2& a = Vector2(), const Vector2& b = Vector2(), const Vector2& c = Vector2(), const Color& color = Color()) :
			Triangle2D(a, b, c), m_color(color) {
		}
		inline Triangle2DC(const Triangle2D& tri, const Color& color) :
			Triangle2D(tri.m_a, tri.m_b, tri.m_c), m_color(color) {
		}
	};

	struct Triangle3DC : Triangle3D
	{
		Color m_color;

		inline Triangle3DC(const Vector3& a = Vector3(), const Vector3& b = Vector3(), const Vector3& c = Vector3(), const Color& color = Color()) :
			Triangle3D(a, b, c), m_color(color) {
		}
		inline Triangle3DC(const Triangle3D& tri, const Color& color) :
			Triangle3D(tri.m_a, tri.m_b, tri.m_c), m_color(color) {
		}
	};

	struct BitMaskInt
	{
		unsigned int m_bits;

		inline BitMaskInt(unsigned int mask = 0) : m_bits(mask) {}
		inline BitMaskInt(unsigned char section1, unsigned char section2, unsigned char section3, unsigned char section4) :
			m_bits((section1 << 24) + (section2 << 16) + (section3 << 8) + (section4)) {}
		inline BitMaskInt(
			unsigned char b31, unsigned char b30, unsigned char b29, unsigned char b28, unsigned char b27, unsigned char b26, unsigned char b25, unsigned char b24,
			unsigned char b23, unsigned char b22, unsigned char b21, unsigned char b20, unsigned char b19, unsigned char b18, unsigned char b17, unsigned char b16,
			unsigned char b15, unsigned char b14, unsigned char b13, unsigned char b12, unsigned char b11, unsigned char b10, unsigned char b9,  unsigned char b8,
			unsigned char b7,  unsigned char b6,  unsigned char b5,  unsigned char b4,  unsigned char b3,  unsigned char b2,  unsigned char b1,  unsigned char b0 ) :
			m_bits((b31 << 31)+(b30 << 30)+(b29 << 29)+(b28 << 28)+(b27 << 27)+(b26 << 26)+(b25 << 25)+(b24 << 24)+
				(b23 << 23)+(b22 << 22)+(b21 << 21)+(b20 << 20)+(b19 << 19)+(b18 << 18)+(b17 << 17)+(b16 << 16)+
				(b15 << 15)+(b14 << 14)+(b13 << 13)+(b12 << 12)+(b11 << 11)+(b10 << 10)+(b9 << 9)+(b8 << 8)+
				(b7 << 7)+(b6 << 6)+(b5 << 5)+(b4 << 4)+(b3 << 3)+(b2 << 2)+(b1 << 1)+b0)
		{}

		const bool inline operator[](int index) const { return (m_bits & (1 << index)); }
		const bool inline operator==(const BitMaskInt& rhs) const { return m_bits == rhs.m_bits; }

		const bool inline AnyMatch(const BitMaskInt& rhs) const { return (m_bits & rhs.m_bits) > 0; }

		friend std::ostream& operator<<(std::ostream& os, const BitMaskInt& rhs)
		{
			os << (int)(rhs[31]) << (int)(rhs[30]) << (int)(rhs[29]) << (int)(rhs[28]) << (int)(rhs[27]) << (int)(rhs[26]) << (int)(rhs[25]) << (int)(rhs[24]) << " "
				<< (int)(rhs[23]) << (int)(rhs[22]) << (int)(rhs[21]) << (int)(rhs[20]) << (int)(rhs[19]) << (int)(rhs[18]) << (int)(rhs[17]) << (int)(rhs[16]) << " "
				<< (int)(rhs[15]) << (int)(rhs[14]) << (int)(rhs[13]) << (int)(rhs[12]) << (int)(rhs[11]) << (int)(rhs[10]) << (int)(rhs[9]) << (int)(rhs[8]) << " "
				<< (int)(rhs[7]) << (int)(rhs[6]) << (int)(rhs[5]) << (int)(rhs[4]) << (int)(rhs[3]) << (int)(rhs[2]) << (int)(rhs[1]) << (int)(rhs[0]);
			return os;
		}
	};

	struct VertexUV3D
	{
		Vector3 m_pos;
		Vector2 m_uv;

		inline VertexUV3D(const Vector3& pos) : m_pos(pos), m_uv(Vector2()) {}
		inline VertexUV3D(const Vector3& pos, const Vector2& uv) : m_pos(pos), m_uv(uv) {}
		inline VertexUV3D(const float x, const float y, const float z, const float u, const float v) : m_pos(x, y, z), m_uv(u, v) {}
	};

	struct VertexUV2D
	{
		Vector2 m_pos;
		Vector2 m_uv;

		inline VertexUV2D(const Vector2& pos) : m_pos(pos), m_uv(Vector2()) {}
		inline VertexUV2D(const Vector2& pos, const Vector2& uv) : m_pos(pos), m_uv(uv) {}
		inline VertexUV2D(const float x, const float y, const float u, const float v) : m_pos(x, y), m_uv(u, v) {}
	};

	struct Rect2D
	{
		float m_x = 0.0f, m_y = 0.0f, m_w = 0.0f, m_h = 0.0f;

		Rect2D(float x = 0.0f, float y = 0.0f, float w = 0.0f, float h = 0.0f) : m_x(x), m_y(y), m_w(w), m_h(h) {}
	};
}