#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>
#include <sstream>

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

	virtual std::stringstream	GetDump();

	virtual				~Entity();

	virtual Entity*		Clone()				const = 0;
	virtual void		Attack()				  = 0;
	void				Move();

	void				Update(EntityStateManager* mgr);

	const bool			IsAlive()			const;
	const sf::Sprite&	GetSprite()			const;
	const sf::Vector2f&	GetLookAt()			const;
	const sf::Vector2f& GetTarget()			const;
	const sf::Vector2f&	GetPosition()		const;
	const float			GetRotation()		const;
	const double		GetWalkingSpeed()	const;
	const int			GetType()			const;
	const int			GetId()				const;

	void				SetSprite(const sf::Sprite& sprite);
	void				SetLookAt(const sf::Vector2f& lookAt);
	void				SetTarget(const sf::Vector2f& target);
	void				SetPosition(const sf::Vector2f& position);
	void				SetRotation(const float rotation);
	void				SetWalkingSpeed(const double walkingspeed);
	void				SetId(const int id);


protected:
	Entity(const int id, const int type, const sf::Sprite& sprite, const sf::Vector2f& position, const double walkingspeed);

private:

	bool			m_alive;
	int				m_type;
	sf::Sprite		m_sprite;
	sf::Vector2f	m_lookAt;
	sf::Vector2f	m_target;
	sf::Vector2f	m_position;
	float			m_rotation;
	double			m_walkingspeed;
	int				m_id;
};

#endif