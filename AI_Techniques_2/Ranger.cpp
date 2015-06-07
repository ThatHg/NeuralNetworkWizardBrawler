#include "Ranger.h"

using namespace std;

Ranger::Ranger(const int id, const int type, const sf::Sprite& sprite, const sf::Vector2f& target, const sf::Vector2f& position, const Config& config) :
	Entity(id, type, sprite, target, position, config),
	m_spells(),
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
	if(m_attackTimer.getElapsedTime().asSeconds() >= m_attackspeed)
	{
		m_attackTimer.restart();
		m_spells.push(4);
	}
}

const int Ranger::GetNextSpell()
{
	int spelltype = -1;
	if(!m_spells.empty())
	{
		 spelltype = m_spells.front();
		m_spells.pop();
	}

	return spelltype;
}

const double Ranger::GetAttackSpeed() const
{
	return m_attackspeed;
}