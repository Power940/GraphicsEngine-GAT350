#pragma once
#include "Constants.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>


namespace STR_FALL
{
	struct Transform3D
	{
	public:
		glm::vec3 m_pos;
		glm::vec3 m_scale;
		glm::vec3 m_rot;
		glm::mat4 m_mat;

		inline Transform3D(const glm::vec3& pos = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f), const glm::vec3& rot = glm::vec3()) :
			m_pos(pos), m_scale(scale), m_rot(rot) {
			GetMatrix();
		}

		inline const glm::mat4& GetMatrix()
		{
			glm::mat4 mxt = glm::translate(m_pos);
			glm::mat4 mxr = glm::eulerAngleXYZ(m_rot.y, m_rot.x, m_rot.z);
			glm::mat4 mxs = glm::scale(m_scale);
			m_mat = mxt * mxr * mxs;
			return m_mat;
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
}