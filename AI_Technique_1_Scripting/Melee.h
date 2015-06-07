#ifndef MELEE_H
#define MELEE_H

#include "Entity.h"
#include "Config.h"
#include <sstream>

class Melee : public Entity
{
public:
	Melee(const int id, const int type, const sf::Sprite& sprite, const sf::Vector2f& position, const Config& config);
	virtual	~Melee();

	virtual Melee*		Clone()				const;
	virtual void		Attack();

	double				GetRange()			const;
	double				GetDamage()			const;
	double				GetHealth()			const;
	const Immunity&		GetImmunity()		const;
	double				GetAttackSpeed()	const;
	std::stringstream	GetDump();

private:
	double			m_range;
	double			m_damage;
	double			m_health;
	Immunity		m_immunity;
	double			m_attackspeed;
};

#endif