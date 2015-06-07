#ifndef RANGER_H
#define RANGER_H

#include "Entity.h"
#include <queue>
#include <SFML\System\Clock.hpp>

class Ranger : public Entity
{
public:
	Ranger(const int id, const int type, const sf::Sprite& sprite, const sf::Vector2f& target, const sf::Vector2f& position, const Config& config);
	virtual	~Ranger();

	virtual Ranger*		Clone()	const;
	virtual void		Attack();

	virtual const int	GetNextSpell();
	const double		GetAttackSpeed()	const;

private:
	std::queue<int>	m_spells;
	sf::Clock		m_attackTimer;
	double			m_attackspeed;
};

#endif