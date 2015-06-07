#include "Entity.h"
#include "Helper.h"
#include "GlobalClock.h"
#include "EntityStateManager.h"

using namespace std;

Entity::Entity(const int id, const int type, const sf::Sprite& sprite, const sf::Vector2f& target, const sf::Vector2f& position, const Config& config) :
	m_alive(true),
	m_type(type),
	m_sprite(sprite),
	m_lookAt(sf::Vector2f(0.0f, 1.0f)),
	m_target(target),
	m_position(position),
	m_rotation(0),
	m_walkingspeed(config.GrabReal("WALKING_SPEED")),
	m_range(config.GrabReal("RANGE")),
	m_damage(config.GrabReal("DAMAGE")),
	m_health(config.GrabReal("HEALTH")),
	m_immunity(Immunity(config.GrabInteger("IMMUNITY"))),
	m_id(id),
	m_damages()
{
	m_sprite.setOrigin(m_sprite.getTextureRect().width/2, m_sprite.getTextureRect().height/2);
}

Entity::~Entity()
{}

void Entity::Update(EntityStateManager* mgr)
{
	if(m_health <= 0)
		m_alive = false;

	m_rotation = RotationDeg2D(m_position, m_target);

	if(m_rotation >= 360 || m_rotation < 0)
		m_rotation = 0;

	m_sprite.setRotation(m_rotation);

	m_lookAt = m_target - m_position;
	Normalize(m_lookAt);
	if(!m_damages.empty())
		mgr->Handle(DamageEvent(), this);
	else if(!m_alive)
		mgr->Handle(DeathEvent(), this);
	else if(Distance(m_position, m_target) <= m_range)
		mgr->Handle(AttackEvent(), this);
	else
		mgr->Handle(MoveEvent(), this);
}

void Entity::Move()
{
	float speed	= float(m_walkingspeed * GlobalClock::Ref().ElapsedTime().asSeconds()) * 100.0f;
	m_position	+= m_lookAt * speed;
	m_sprite.setPosition(m_position);
}

const int Entity::GetNextSpell()
{
	return -1;
}

const double Entity::GetLatestDamage()
{
	double damage = -1;
	if(!m_damages.empty())
	{
		damage = m_damages.back();
		m_damages.pop_back();
	}

	return damage;
}

void Entity::AddDamage(const double damage)
{
	m_damages.push_back(damage);
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

const double Entity::GetRange() const
{
	return m_range;
}

const double Entity::GetDamage() const
{
	return m_damage;
}

const double Entity::GetHealth() const
{
	return m_health;
}

const Entity::Immunity& Entity::GetImmunity() const
{
	return m_immunity;
}

const double Entity::GetAttackSpeed()	const
{
	return -1;
}

const int Entity::GetType() const
{
	return m_type;
}

stringstream Entity::GetDump()
{
	stringstream ss;
	switch (m_type)
	{
	case 0:		ss << "Type: Melee Trainee"		<< endl; break;
	case 1:		ss << "Type: Ranger Trainee"	<< endl; break;
	case 2:		ss << "Type: Melee Boss"		<< endl; break;
	case 3:		ss << "Type: Ranger Boss"		<< endl; break;
	default:	ss << "Type: Undefined"			<< endl; break;
	}
	ss << "LookAt: ("		<< m_lookAt.x << ", " << m_lookAt.y << ")" << endl;
	ss << "Position: ("		<< m_position.x << ", " << m_position.y << ")" << endl;
	ss << "Rotation: "		<< m_rotation << endl;
	ss << "Target: ("		<< m_target.x << ", " << m_target.y << ")" << endl;
	ss << "Walking Speed: " << m_walkingspeed << endl;
	ss << "Is Alive: "		<< m_alive << endl;
	ss << "Range: "			<< m_range << endl;
	ss << "Damage: "		<< m_damage << endl;
	ss << "Health: "		<< m_health << endl;
	switch (m_immunity)
	{
	case 0:		ss << "Immunity: FIRE"		<< endl; break;
	case 1:		ss << "Immunity: WATER"		<< endl; break;
	case 2:		ss << "Immunity: EARTH"		<< endl; break;
	case 3:		ss << "Immunity: AIR"		<< endl; break;
	default:	ss << "Immunity: Undefined"	<< endl; break;
	}
	return ss;
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

void Entity::SetRange(const double range)
{
	m_range = range;
}

void Entity::SetDamage(const double damage)
{
	m_damage = damage;
}

void Entity::SetHealth(const double health)
{
	m_health = health;
}

void Entity::SetImmunity(const Immunity& immunity)
{
	m_immunity = immunity;
}

void Entity::SetAttackSpeed(const double attackspeed)
{
}

void Entity::SetId(const int id)
{
	m_id = id;
}