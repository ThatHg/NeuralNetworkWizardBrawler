#include "Melee.h"

using namespace std;

Melee::Melee(const int id, const int type, const sf::Sprite& sprite, const sf::Vector2f& target, const sf::Vector2f& position, const Config& config) :
	Entity(id, type, sprite, target, position, config),
	m_spells(),
	m_attackspeed(config.GrabReal("ATTACK_SPEED"))
{
	m_attackTimer.restart();
}

Melee::~Melee()
{
}

Melee* Melee::Clone() const
{
	return new Melee(*this);
}

void Melee::Attack()
{
	if(m_attackTimer.getElapsedTime().asSeconds() >= m_attackspeed)
	{
		m_attackTimer.restart();
		m_spells.push(5);
	}
}

const int Melee::GetNextSpell()
{
	int spelltype = -1;
	if(!m_spells.empty())
	{
		 spelltype = m_spells.front();
		m_spells.pop();
	}

	return spelltype;
}

const double Melee::GetAttackSpeed() const
{
	return m_attackspeed;
}