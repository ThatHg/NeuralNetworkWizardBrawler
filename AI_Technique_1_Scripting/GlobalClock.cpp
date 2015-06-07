#include "GlobalClock.h"

GlobalClock GlobalClock::m_instance;
GlobalClock& GlobalClock::Ref()
{
	return m_instance;
}

GlobalClock::GlobalClock()
{
	m_clock.restart();
}

GlobalClock::~GlobalClock()
{
}

sf::Time GlobalClock::ElapsedTime()
{
	return m_clock.getElapsedTime();
}

void GlobalClock::Reset()
{
	m_clock.restart();
}