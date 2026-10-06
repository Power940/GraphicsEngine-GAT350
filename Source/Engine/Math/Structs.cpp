#include "pch.h"
#include "Structs.h"


using namespace STR_FALL;

Vector2::Vector2(const Vector3& vect) : m_x(vect.m_x), m_y(vect.m_y) {}
Vector2::Vector2(const Vector4& vect) : m_x(vect.m_x), m_y(vect.m_y) {}
Vector3::Vector3(const Vector2& vect) : m_x(vect.m_x), m_y(vect.m_y), m_z(0.0f) {}
Vector3::Vector3(const Vector4& vect) : m_x(vect.m_x), m_y(vect.m_y), m_z(vect.m_z) {}
Vector4::Vector4(const Vector2& vect) : m_x(vect.m_x), m_y(vect.m_y), m_z(0.0f), m_w(0.0f) {}
Vector4::Vector4(const Vector3& vect) : m_x(vect.m_x), m_y(vect.m_y), m_z(vect.m_z), m_w(0.0f) {}

Vector3::Vector3(const VertexUV3D& vect) : m_x(vect.m_pos.m_x), m_y(vect.m_pos.m_y), m_z(vect.m_pos.m_z) {}

Vector2 Vector2::operator*(const Matrix2& rhs) const {
	return Vector2(
		rhs.m_m[0][0] * m_x + rhs.m_m[0][1] * m_y,
		rhs.m_m[1][0] * m_x + rhs.m_m[1][1] * m_y
	);
}
Vector2& Vector2::operator*=(const Matrix2& rhs) {
	float x, y;
	x = rhs.m_m[0][0] * m_x + rhs.m_m[0][1] * m_y;
	y = rhs.m_m[1][0] * m_x + rhs.m_m[1][1] * m_y;
	m_x = x; m_y = y;
	return *this;
}
Vector3 Vector3::operator*(const Matrix3& rhs) const {
	return Vector3(
		rhs.m_m[0][0] * m_x + rhs.m_m[0][1] * m_y + rhs.m_m[0][2] * m_z,
		rhs.m_m[1][0] * m_x + rhs.m_m[1][1] * m_y + rhs.m_m[1][2] * m_z,
		rhs.m_m[2][0] * m_x + rhs.m_m[2][1] * m_y + rhs.m_m[2][2] * m_z
	);
}
Vector3& Vector3::operator*=(const Matrix3& rhs) {
	float x, y, z;
	x = rhs.m_m[0][0] * m_x + rhs.m_m[0][1] * m_y + rhs.m_m[0][2] * m_z;
	y = rhs.m_m[1][0] * m_x + rhs.m_m[1][1] * m_y + rhs.m_m[1][2] * m_z;
	z = rhs.m_m[2][0] * m_x + rhs.m_m[2][1] * m_y + rhs.m_m[2][2] * m_z;
	m_x = x; m_y = y; m_z = z;
	return *this;
}

Vector2 Vector2::Rotate(const float rad) const { return *this * Matrix2::RotationXY(rad); }

Matrix2::Matrix2(const Matrix3& m)
{
	m_m[0][0] = m[0][0]; m_m[0][1] = m[0][1];
	m_m[1][0] = m[1][0]; m_m[1][1] = m[1][1];
}
Matrix3::Matrix3(const Matrix2& m)
{
	m_m[0][0] = m[0][0]; m_m[0][1] = m[0][1]; m_m[0][2] = 0;
	m_m[1][0] = m[1][0]; m_m[1][1] = m[1][1]; m_m[1][2] = 0;
	m_m[2][0] = 0; m_m[2][1] = 0; m_m[2][2] = 1;
}

Camera3D Camera3D::Empty {};