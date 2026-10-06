#include "pch.h"
#include "Input.h"


using namespace STR_FALL;

bool Input::Initialize()
{
	int numKeys;
	const bool* keyState = SDL_GetKeyboardState(&numKeys);
	m_keyStates.resize(numKeys);

	std::copy(keyState, keyState + numKeys, m_keyStates.begin());
	m_prevKeyStates = m_keyStates;

	return true;
}

void Input::Update()
{
	m_prevKeyStates = m_keyStates;
	m_prevButtonStates = m_buttonStates;
	int numKeys;
	const bool* keyState = SDL_GetKeyboardState(&numKeys);
	if (numKeys != m_keyStates.size())
	{
		m_keyStates.resize(numKeys);

		std::copy(keyState, keyState + numKeys, m_keyStates.begin());
		m_prevKeyStates = m_keyStates;
	}
	else
	{
		std::copy(keyState, keyState + m_keyStates.size(), m_keyStates.begin());
	}

	m_buttonStates = SDL_GetMouseState(&m_mousePos.m_x, &m_mousePos.m_y);
}
