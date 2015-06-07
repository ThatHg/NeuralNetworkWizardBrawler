#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>
#include <sstream>
#include "Config.h"

class EntityStateManager;

class Entity
{
public:
	enum Immunity
	{
		FIRE,
		WATER,
		EARTH,
		AIR
	};

	std::stringstream	GetDump();

	virtual				~Entity();

	virtual Entity*		Clone()				const = 0;
	virtual void		Attack()				  = 0;
	void				Move();

	void				Update(EntityStateManager* mgr);

	// Get Next spell, return -1 if there is no spell to cast.
	virtual const int	GetNextSpell();

	const bool			IsAlive()			const;
	const sf::Sprite&	GetSprite()			const;
	const sf::Vector2f&	GetLookAt()			const;
	const sf::Vector2f& GetTarget()			const;
	const sf::Vector2f&	GetPosition()		const;
	const float			GetRotation()		const;
	const double		GetWalkingSpeed()	const;
	const double		GetRange()			const;
	const double		GetDamage()			const;
	const double		GetHealth()			const;
	const Immunity&		GetImmunity()		const;
	virtual const double GetAttackSpeed()	const;
	const int			GetType()			const;
	const int			GetId()				const;

	// Get latest damage returns -1 when the damagevector is empty
	const double		GetLatestDamage();
	// Add damage to damagevector which later uses for dealing damage to this entity
	void				AddDamage(const double damage);

	void				SetSprite(const sf::Sprite& sprite);
	void				SetLookAt(const sf::Vector2f& lookAt);
	void				SetTarget(const sf::Vector2f& target);
	void				SetPosition(const sf::Vector2f& position);
	void				SetRotation(const float rotation);
	void				SetWalkingSpeed(const double walkingspeed);
	void				SetRange(const double range);
	void				SetDamage(const double damage);
	void				SetHealth(const double health);
	void				SetImmunity(const Immunity& immunity);
	virtual void		SetAttackSpeed(const double attackspeed);
	void				SetId(const int id);

protected:
	Entity(const int id, const int type, const sf::Sprite& sprite, const sf::Vector2f& target, const sf::Vector2f& position, const Config& config);

private:
	typedef std::vector<double> Damages;

	bool			m_alive;
	int				m_type;
	sf::Sprite		m_sprite;
	sf::Vector2f	m_lookAt;
	sf::Vector2f	m_target;
	sf::Vector2f	m_position;
	float			m_rotation;
	double			m_walkingspeed;
	double			m_range;
	double			m_damage;
	double			m_health;
	Immunity		m_immunity;
	int				m_id;
	Damages			m_damages;
};

#endif