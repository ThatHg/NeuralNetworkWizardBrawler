#include "GlobalClock.h"

GlobalClock GlobalClock::m_instance;
GlobalClock& GlobalClock::Ref()
{
	return m_instance;
}

GlobalClock::GlobalClock() :
	m_multiplier(1)
{
	m_clock.restart();
}

GlobalClock::~GlobalClock()
{
}

sf::Time GlobalClock::ElapsedTime()
{
	return m_clock.getElapsedTime() * m_multiplier;
}

void GlobalClock::Reset()
{
	m_clock.restart();
}

void GlobalClock::SetMultiplier(const float multiplier)
{
	m_multiplier = multiplier;
}