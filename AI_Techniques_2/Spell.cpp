#include "Spell.h"
#include "GlobalClock.h"
#include "Helper.h"

Spell::Spell(const double damage, const bool friendly, const Type type, const sf::Sprite& sprite, const sf::Vector2f& position, const sf::Vector2f& lookAt) :
	m_alive(true),
	m_damage(damage),
	m_rotation(0),
	m_position(position),
	m_lookAt(lookAt),
	m_sprite(sprite),
	m_friendly(friendly),
	m_type(type)
{
	m_sprite.setOrigin(m_sprite.getTextureRect().width/2, m_sprite.getTextureRect().height/2);
}

Spell::~Spell()
{
}

Spell::Spell(const Spell& spell) :
	m_alive(spell.m_alive),
	m_damage(spell.m_damage),
	m_rotation(spell.m_rotation),
	m_position(spell.m_position),
	m_lookAt(spell.m_lookAt),
	m_sprite(spell.m_sprite),
	m_friendly(spell.m_friendly),
	m_type(spell.m_type)
{

}

Spell& Spell::operator=(const Spell& spell)
{
	m_alive		= spell.m_alive;
	m_damage	= spell.m_damage;
	m_rotation	= spell.m_rotation;
	m_position	= spell.m_position;
	m_lookAt	= spell.m_lookAt;
	m_sprite	= spell.m_sprite;
	m_friendly	= spell.m_friendly;
	m_type		= spell.m_type;

	return *this;
}

void Spell::Update()
{
	Move();
	m_sprite.setOrigin(m_sprite.getTextureRect().width/2, m_sprite.getTextureRect().height/2);
	m_rotation = RotationDeg2D(m_position, m_position + m_lookAt);

	if(m_rotation >= 360 || m_rotation < 0)
		m_rotation = 0;

	m_sprite.setRotation(m_rotation);
}

void Spell::Render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void Spell::Move()
{
	float speed	= GlobalClock::Ref().ElapsedTime().asSeconds() * 1000.0f;
	m_position	= m_position + m_lookAt * speed;
	m_sprite.setPosition(m_position);
}

const bool Spell::IsAlive() const
{
	return m_alive;
}

const double Spell::GetDamage() const
{
	return m_damage;
}

const float Spell::GetRotation() const
{
	return m_rotation;
}
const sf::Vector2f& Spell::GetPosition() const
{
	return m_position;
}

const sf::Vector2f& Spell::GetLookAt() const
{
	return m_lookAt;
}

const sf::Sprite& Spell::GetSprite() const
{
	return m_sprite;
}

const bool Spell::IsFriendly() const
{
	return m_friendly;
}

const Spell::Type Spell::GetType() const
{
	return m_type;
}

void Spell::SetAlive(const bool alive)
{
	m_alive = alive;
}

void Spell::SetDamage(const double damage)
{
	m_damage = damage;
}

void Spell::SetRotation(const float rotation)
{
	m_rotation = rotation;
}

void Spell::SetPosition(const sf::Vector2f& position)
{
	m_position = position;
}

void Spell::SetLookAt(const sf::Vector2f& lookAt)
{
	m_lookAt = lookAt;
}

void Spell::SetSprite(const sf::Sprite& sprite)
{
	m_sprite = sprite;
}

void Spell::SetFriendlyness(const bool friendly)
{
	m_friendly = friendly;
}

void Spell::SetType(const Type type)
{
	m_type = type;
}