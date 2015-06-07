#ifndef RANGER_H
#define RANGER_H

#include "Entity.h"
#include "Config.h"
#include <sstream>

class Ranger : public Entity
{
public:
	Ranger(const int id, const int type, const sf::Sprite& sprite, const sf::Vector2f& position, const Config& config);
	virtual	~Ranger();

	virtual Ranger*		Clone()				const;
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