#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Config.h"
#include <queue>
#include "Animation.h"

class Player
{
public:
	Player(const sf::Vector2f& position, const Config& config);
	~Player();
	Player(const Player& player);
	Player& operator=(const Player& player);

	void				Update(const sf::Vector2f& target);
	void				Render(sf::RenderWindow& window);
	void				Attack(int type);

	const int			GetNextSpell();
	const sf::Sprite&	GetSprite()			const;
	const sf::Vector2f&	GetPosition()		const;
	const sf::Vector2f& GetTarget()			const;
	const sf::Vector2f& GetLookAt()			const;
	const float			GetRotation()		const;
	const double		GetDamage()			const;
	const double		GetHealth()			const;
	const double		GetAttackspeed()	const;
	const double		GetWalkingspeed()	const;
	const double		GetConcentration()	const;
	const Animation&	GetAnimation()		const;
	const int			GetPoints()			const;

	void				DamagePlayer(const double damage);

	void				SetSprite(const sf::Sprite& sprite);
	void				SetPosition(const sf::Vector2f& position);
	void				SetTarget(const sf::Vector2f& target);
	void				SetLookAt(const sf::Vector2f& lookAt);
	void				SetRotation(const float rotation);
	void				SetDamage(const double damage);
	void				SetHealth(const double health);
	void				SetAttackspeed(const double attackspeed);
	void				SetWalkingspeed(const double walkingspeed);
	void				SetConcentration(const double concentration);
	void				SetAnimation(const Animation& animation);
	void				SetPoints(const int points);
	void				AddToPoints(const int points);

private:
	void Move();

	sf::Sprite		m_sprite;
	Animation		m_animation;
	sf::Vector2f	m_position;
	sf::Vector2f	m_target;
	sf::Vector2f	m_lookAt;
	float			m_rotation;
	double			m_damage;
	double			m_health;
	double			m_attackspeed;
	double			m_walkingspeed;
	double			m_concentration;
	std::queue<int>	m_spells;
	int				m_points;
};

#endif