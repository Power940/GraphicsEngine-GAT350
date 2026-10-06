#include "pch.h"
#include "StarTime.h"


using namespace STR_FALL;

Time::Time()
{
	m_startTicks = SDL_GetTicksNS();
}
void Time::Reset()
{
	m_startTicks = SDL_GetTicksNS();
	m_frameTicks = SDL_GetTicksNS();
	m_currentTicks = SDL_GetTicksNS();
}
void Time::Tick()
{
	m_currentTicks = SDL_GetTicksNS();
	m_deltaTicks = m_currentTicks - m_frameTicks;
	m_frameTicks = m_currentTicks;

}