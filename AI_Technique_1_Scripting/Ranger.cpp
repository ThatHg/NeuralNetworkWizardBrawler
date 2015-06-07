#include "Ranger.h"

using namespace std;

Ranger::Ranger(const int id, const int type, const sf::Sprite& sprite, const sf::Vector2f& position, const Config& config) :
	Entity(id, type, sprite, position, config.GrabReal("WALKING_SPEED")),
	m_range(config.GrabReal("RANGE")),
	m_damage(config.GrabReal("DAMAGE")),
	m_health(config.GrabReal("HEALTH")),
	m_immunity(Immunity(config.GrabInteger("IMMUNITY"))),
	m_attackspeed(config.GrabReal("ATTACK_SPEED"))
{
}

Ranger::~Ranger()
{
	
}

Ranger* Ranger::Clone() const
{
	return new Ranger(*this);
}

void Ranger::Attack()
{
	// Do some special ranger attack moves!
}

double Ranger::GetRange() const
{
	return m_range;
}

double Ranger::GetDamage() const
{
	return m_damage;
}

double Ranger::GetHealth() const
{
	return m_health;
}

const Entity::Immunity& Ranger::GetImmunity() const
{
	return m_immunity;
}

double Ranger::GetAttackSpeed() const
{
	return m_attackspeed;
}

stringstream Ranger::GetDump()
{
	stringstream ss;
	ss << "Range: " << m_range << endl;
	ss << "Damage: " << m_damage << endl;
	ss << "Health: " << m_health << endl;
	switch (m_immunity)
	{
	case 0:		ss << "Immunity: FIRE"		<< endl; break;
	case 1:		ss << "Immunity: WATER"		<< endl; break;
	case 2:		ss << "Immunity: EARTH"		<< endl; break;
	case 3:		ss << "Immunity: AIR"		<< endl; break;
	default:	ss << "Immunity: Undefined" << endl; break;
	}
	ss << "Attack Speed: " << m_attackspeed << endl;

	return ss;
}