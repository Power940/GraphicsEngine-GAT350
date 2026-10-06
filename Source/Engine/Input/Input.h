#pragma once
#include <Math/Structs.h>
#include <cstdint>
#include <vector>


namespace STR_FALL
{
	class Input
	{
	private:
		int m_numKeys = 0;

		std::vector<bool> m_keyStates;
		std::vector<bool> m_prevKeyStates;

		uint32_t m_buttonStates = 0;
		uint32_t m_prevButtonStates = 0;

		Vector2 m_mousePos = Vector2();
	public:
		enum MouseButton
		{
			LEFT = 0b0001,
			MIDDLE = 0b0010,
			RIGHT = 0b0100
		};

		bool Initialize();

		void Update();

		bool GetKeyDown(int key) const { return m_keyStates.at(key); }
		bool GetKeyPrevDown(int key) const { return m_prevKeyStates.at(key); }
		bool GetKeyPressed(int key) const { return !m_prevKeyStates.at(key) && m_keyStates.at(key); }
		bool GetKeyReleased(int key) const { return m_prevKeyStates.at(key) && !m_keyStates.at(key); }

		bool GetMouseDown(MouseButton button) const { return m_buttonStates & button; }
		bool GetMousePrevDown(MouseButton button) const { return m_prevButtonStates & button; }
		bool GetMousePressed(MouseButton button) const { return !(m_prevButtonStates & button) && (m_buttonStates & button); }
		bool GetMouseReleased(MouseButton button) const { return (m_prevButtonStates & button) && !(m_buttonStates & button); }

		Vector2 GetMousePos() const { return m_mousePos; }
        int GetKeyDiff(int pos, int neg) const { return m_keyStates.at(pos) - m_keyStates.at(neg); }
        Vector2 GetKeyDir(int posX, int negX, int posY, int negY) const { return Vector2(static_cast<float>(m_keyStates.at(posX) - m_keyStates.at(negX)), static_cast<float>(m_keyStates.at(posY) - m_keyStates.at(negY))); }

		enum KeyCodes
		{
            // taken from SDL3\include\SDL3\SDL_scancode.h
            // if more are needed look though there and add them here, or use the SDL_SCANCODE_{key}
            VK_A = 4, 
            VK_B = 5,
            VK_C = 6,
            VK_D = 7,
            VK_E = 8,
            VK_F = 9,
            VK_G = 10,
            VK_H = 11,
            VK_I = 12,
            VK_J = 13,
            VK_K = 14,
            VK_L = 15,
            VK_M = 16,
            VK_N = 17,
            VK_O = 18,
            VK_P = 19,
            VK_Q = 20,
            VK_R = 21,
            VK_S = 22,
            VK_T = 23,
            VK_U = 24,
            VK_V = 25,
            VK_W = 26,
            VK_X = 27,
            VK_Y = 28,
            VK_Z = 29,

            VK_1 = 30,
            VK_2 = 31,
            VK_3 = 32,
            VK_4 = 33,
            VK_5 = 34,
            VK_6 = 35,
            VK_7 = 36,
            VK_8 = 37,
            VK_9 = 38,
            VK_0 = 39,
            VK_F1 = 58,
            VK_F2 = 59,
            VK_F3 = 60,
            VK_F4 = 61,
            VK_F5 = 62,
            VK_F6 = 63,
            VK_F7 = 64,
            VK_F8 = 65,
            VK_F9 = 66,
            VK_F10 = 67,
            VK_F11 = 68,
            VK_F12 = 69,
            VK_F13 = 104,
            VK_F14 = 105,
            VK_F15 = 106,
            VK_F16 = 107,
            VK_F17 = 108,
            VK_F18 = 109,
            VK_F19 = 110,
            VK_F20 = 111,
            VK_F21 = 112,
            VK_F22 = 113,
            VK_F23 = 114,
            VK_F24 = 115,

            VK_RETURN = 40,
            VK_ESCAPE = 41,
            VK_BACKSPACE = 42,
            VK_TAB = 43,
            VK_SPACE = 44,
            VK_RIGHT = 79,
            VK_LEFT = 80,
            VK_DOWN = 81,
            VK_UP = 82,
            VK_LSHIFT = 225,
            VK_LCTRL = 224,
            VK_LALT = 226,
            VK_LWIN = 227,
            VK_RSHIFT = 229,
            VK_RCTRL = 228,
            VK_RALT = 230,
            VK_RWIN = 231
		};
	};
}