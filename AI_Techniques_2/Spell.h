#ifndef SPELL_H
#define SPELL_H

#include <SFML/Graphics.hpp>

class Spell
{
public:
	enum Type{FIRE, WATER, EARTH, AIR, ARROW, FIST};

	Spell(const double damage, const bool friendly, const Type type, const sf::Sprite& sprite, const sf::Vector2f& position, const sf::Vector2f& lookAt);
	~Spell();
	Spell(const Spell& spell);
	Spell& operator=(const Spell& spell);

	void Update();
	void Render(sf::RenderWindow& window);

	const bool			IsAlive()		const;
	const double		GetDamage()		const;
	const float			GetRotation()	const;
	const sf::Vector2f&	GetPosition()	const;
	const sf::Vector2f&	GetLookAt()		const;
	const sf::Sprite&	GetSprite()		const;
	const bool			IsFriendly()	const;
	const Type			GetType()		const;

	void				SetAlive(const bool alive);
	void				SetDamage(const double damage);
	void				SetRotation(const float rotation);
	void				SetPosition(const sf::Vector2f& position);
	void				SetLookAt(const sf::Vector2f& lookAt);
	void				SetSprite(const sf::Sprite& sprite);
	void				SetFriendlyness(const bool friendly);
	void				SetType(const Type type);

private:
	void Move();

	bool			m_alive;
	double			m_damage;
	float			m_rotation;
	sf::Vector2f	m_position;
	sf::Vector2f	m_lookAt;
	sf::Sprite		m_sprite;
	bool			m_friendly;
	Type			m_type;
};

#endif