#pragma once
#include "Constants.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ostream>
#include <Editor/Editor.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace STR_FALL
{
	struct Transform3D : public IGUI
	{
	public:
		glm::vec3 m_pos;
		glm::vec3 m_scale;
		glm::quat m_rot = glm::identity<glm::quat>();

		inline Transform3D(const glm::vec3& pos = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f), const glm::vec3& rot = glm::vec3()) :
			m_pos(pos), m_scale(scale), m_rot(rot) {
			GetMatrix();
		}

		void SetRotation(const glm::vec3& eular) { m_rot = glm::quat(eular); }
		void SetRotation(const glm::quat& quat) { m_rot = glm::normalize(quat); }
		glm::vec3 GetRotation() const { return glm::eulerAngles(m_rot); }

		inline glm::mat4 GetMatrix() const
		{
			glm::mat4 mxt = glm::translate(m_pos);
			glm::mat4 mxr = glm::toMat4(m_rot);
			glm::mat4 mxs = glm::scale(m_scale);
			return mxt * mxr * mxs;
		}

		inline glm::vec3 Forward() const { return m_rot * glm::vec3(0, 0, -1); }
		inline glm::vec3 Up() const { return m_rot * glm::vec3(0, 1, 0); }
		inline glm::vec3 Right() const { return m_rot * glm::vec3(1, 0, 0); }

		void UpdateGui() override
		{
			ImGui::DragFloat3("Position", glm::value_ptr(m_pos), 0.1f);
			glm::vec3 euler = GetRotation();
			if (ImGui::DragFloat3("Rotation", glm::value_ptr(euler), 0.1f))
			{
				SetRotation(euler);
			}
			ImGui::DragFloat3("Scale", glm::value_ptr(m_scale), 0.1f);
		}
	};

	struct BitMaskInt32
	{
		uint32_t m_bits;

		inline BitMaskInt32(uint32_t mask = 0) : m_bits(mask) {}
		inline BitMaskInt32(uint8_t section1, uint8_t section2, uint8_t section3, uint8_t section4) :
			m_bits((section1 << 24) + (section2 << 16) + (section3 << 8) + (section4)) {}
		inline BitMaskInt32(
			uint8_t b31, uint8_t b30, uint8_t b29, uint8_t b28, uint8_t b27, uint8_t b26, uint8_t b25, uint8_t b24,
			uint8_t b23, uint8_t b22, uint8_t b21, uint8_t b20, uint8_t b19, uint8_t b18, uint8_t b17, uint8_t b16,
			uint8_t b15, uint8_t b14, uint8_t b13, uint8_t b12, uint8_t b11, uint8_t b10, uint8_t b9,  uint8_t b8,
			uint8_t b7,  uint8_t b6,  uint8_t b5,  uint8_t b4,  uint8_t b3,  uint8_t b2,  uint8_t b1,  uint8_t b0 ) :
			m_bits((b31 << 31)+(b30 << 30)+(b29 << 29)+(b28 << 28)+(b27 << 27)+(b26 << 26)+(b25 << 25)+(b24 << 24)+
				(b23 << 23)+(b22 << 22)+(b21 << 21)+(b20 << 20)+(b19 << 19)+(b18 << 18)+(b17 << 17)+(b16 << 16)+
				(b15 << 15)+(b14 << 14)+(b13 << 13)+(b12 << 12)+(b11 << 11)+(b10 << 10)+(b9 << 9)+(b8 << 8)+
				(b7 << 7)+(b6 << 6)+(b5 << 5)+(b4 << 4)+(b3 << 3)+(b2 << 2)+(b1 << 1)+b0)
		{}

		const bool inline operator[](int index) const { return (m_bits & (1 << index)); }
		const bool inline operator==(const BitMaskInt32& rhs) const { return m_bits == rhs.m_bits; }

		const bool inline AnyMatch(const BitMaskInt32& rhs) const { return (m_bits & rhs.m_bits) > 0; }

		friend std::ostream& operator<<(std::ostream& os, const BitMaskInt32& rhs)
		{
			os << (int)(rhs[31]) << (int)(rhs[30]) << (int)(rhs[29]) << (int)(rhs[28]) << (int)(rhs[27]) << (int)(rhs[26]) << (int)(rhs[25]) << (int)(rhs[24]) << " "
				<< (int)(rhs[23]) << (int)(rhs[22]) << (int)(rhs[21]) << (int)(rhs[20]) << (int)(rhs[19]) << (int)(rhs[18]) << (int)(rhs[17]) << (int)(rhs[16]) << " "
				<< (int)(rhs[15]) << (int)(rhs[14]) << (int)(rhs[13]) << (int)(rhs[12]) << (int)(rhs[11]) << (int)(rhs[10]) << (int)(rhs[9]) << (int)(rhs[8]) << " "
				<< (int)(rhs[7]) << (int)(rhs[6]) << (int)(rhs[5]) << (int)(rhs[4]) << (int)(rhs[3]) << (int)(rhs[2]) << (int)(rhs[1]) << (int)(rhs[0]);
			return os;
		}
	};
}