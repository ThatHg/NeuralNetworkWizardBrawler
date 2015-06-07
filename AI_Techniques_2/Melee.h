#ifndef MELEE_H
#define MELEE_H

#include "Entity.h"
#include <queue>
#include <SFML\System\Clock.hpp>

class Melee : public Entity
{
public:
	Melee(const int id, const int type, const sf::Sprite& sprite, const sf::Vector2f& target, const sf::Vector2f& position, const Config& config);
	virtual	~Melee();

	virtual Melee*			Clone()	const;
	virtual void			Attack();

	virtual const int		GetNextSpell();
	virtual const double	GetAttackSpeed() const;

private:
	std::queue<int>	m_spells;
	sf::Clock		m_attackTimer;
	double			m_attackspeed;
};

#endif