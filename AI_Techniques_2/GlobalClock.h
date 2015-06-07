#ifndef GLOBAL_CLOCK_H
#define GLOBAL_CLOCK_H

#include <SFML\System\Clock.hpp>
#include <SFML\System\Time.hpp>

class GlobalClock
{
public:
	static GlobalClock& Ref();
	~GlobalClock();
	sf::Time	ElapsedTime();
	void		Reset();
	void		SetMultiplier(const float multi);

private:
	GlobalClock();
	sf::Clock			m_clock;
	static GlobalClock	m_instance;
	float				m_multiplier;
};

#endif