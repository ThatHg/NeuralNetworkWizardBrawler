#include "Entity.h"
#include "Helper.h"
#include "GlobalClock.h"
#include "EntityStateManager.h"

using namespace std;

Entity::Entity(const int id, const int type, const sf::Sprite& sprite, const sf::Vector2f& position, const double walkingspeed) :
	m_alive(true),
	m_type(type),
	m_sprite(sprite),
	m_lookAt(sf::Vector2f(0.0f, 1.0f)),
	m_target(sf::Vector2f(640.0f, 360.0f)),
	m_position(position),
	m_rotation(0),
	m_walkingspeed(walkingspeed),
	m_id(id)
{
}

Entity::~Entity()
{}

void Entity::Update(EntityStateManager* mgr)
{
	m_rotation = RotationDeg2D(m_position, m_target);

	if(m_rotation >= 360 || m_rotation < 0)
		m_rotation = 0;

	m_sprite.setRotation(m_rotation);

	m_lookAt = m_target - m_position;
	Normalize(m_lookAt);
	mgr->Handle(MoveEvent(), this);
	//mgr->Handle(AttackEvent(), this);
}

void Entity::Move()
{
	m_position += m_lookAt * float(m_walkingspeed * GlobalClock::Ref().ElapsedTime().asSeconds()) * 10000.0f;
	m_sprite.setPosition(m_position);
}

const bool Entity::IsAlive() const
{
	return m_alive;
}

const sf::Sprite& Entity::GetSprite() const
{
	return m_sprite;
}

const sf::Vector2f& Entity::GetLookAt() const
{
	return m_lookAt;
}

const sf::Vector2f& Entity::GetTarget() const
{
	return m_target;
}

const sf::Vector2f&	Entity::GetPosition() const
{
	return m_position;
}

const float Entity::GetRotation() const
{
	return m_rotation;
}

const double Entity::GetWalkingSpeed() const
{
	return m_walkingspeed;
}

const int Entity::GetType() const
{
	return m_type;
}

stringstream Entity::GetDump()
{
	return stringstream();
}

const int Entity::GetId() const
{
	return m_id;
}

void Entity::SetSprite(const sf::Sprite& sprite)
{
	m_sprite = sprite;
}

void Entity::SetLookAt(const sf::Vector2f& lookAt)
{
	m_lookAt = lookAt;
}

void Entity::SetTarget(const sf::Vector2f& target)
{
	m_target = target;
}

void Entity::SetPosition(const sf::Vector2f& position)
{
	m_position = position;
}

void Entity::SetRotation(const float rotation)
{
	m_rotation = rotation;
}

void Entity::SetWalkingSpeed(const double walkingspeed)
{
	m_walkingspeed = walkingspeed;
}

void Entity::SetId(const int id)
{
	m_id = id;
}