#include "Player.h"
#include "AssetsManager.h"
#include <iostream>
#include "Helper.h"
#include "GlobalClock.h"

using namespace std;

Player::Player(const sf::Vector2f& position, const Config& config) :
	m_sprite(AssetsManager::GetReference().GetTexture(config.GrabString("PICTURE"))),
	m_position(position),
	m_lookAt(),
	m_rotation(0),
	m_damage(config.GrabReal("DAMAGE")),
	m_health(config.GrabReal("HEALTH")),
	m_attackspeed(config.GrabReal("ATTACK_SPEED")),
	m_walkingspeed(config.GrabReal("WALKING_SPEED")),
	m_concentration(config.GrabReal("CONCENTRATION")),
	m_animation(m_sprite, 8, true, 0.1f),
	m_points(0)
{
	m_sprite = m_animation.GetSprite();
	m_sprite.setOrigin(m_sprite.getTextureRect().width/2, m_sprite.getTextureRect().height/2);
}

Player::~Player()
{
}

Player::Player(const Player& player) :
	m_sprite(player.m_sprite),
	m_animation(player.m_animation),
	m_position(player.m_position),
	m_target(player.m_target),
	m_lookAt(player.m_lookAt),
	m_rotation(player.m_rotation),
	m_damage(player.m_damage),
	m_health(player.m_health),
	m_attackspeed(player.m_attackspeed),
	m_walkingspeed(player.m_walkingspeed),
	m_concentration(player.m_concentration),
	m_spells(player.m_spells),
	m_points(player.m_points)
{
}

Player& Player::operator=(const Player& player)
{
	m_sprite		= player.m_sprite;
	m_animation		= player.m_animation;
	m_position		= player.m_position;
	m_target		= player.m_target;
	m_lookAt		= player.m_lookAt;
	m_rotation		= player.m_rotation;
	m_damage		= player.m_damage;
	m_health		= player.m_health;
	m_attackspeed	= player.m_attackspeed;
	m_walkingspeed	= player.m_walkingspeed;
	m_concentration	= player.m_concentration;
	m_spells		= player.m_spells;
	m_points		= player.m_points;

	return *this;
}

void Player::Update(const sf::Vector2f& target)
{
	Move();
	m_sprite.setOrigin(m_sprite.getTextureRect().width/2, m_sprite.getTextureRect().height/2);
	m_rotation = RotationDeg2D(m_position, target);

	if(m_rotation >= 360 || m_rotation < 0)
		m_rotation = 0;

	m_sprite.setRotation(m_rotation);

	m_lookAt = target - m_position;
	Normalize(m_lookAt);
}

void Player::Render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void Player::Attack(int type)
{
	if(type >= 0 && type <= 3)
	{
		m_spells.push(type);
	}
	else cerr << "\nERROR: Player hasn't learned that type of spell yet.";
}

void Player::Move()
{
	sf::Vector2f toThis(0.f, 0.f);
	/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		toThis += m_lookAt;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		toThis += m_lookAt * -1.f;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		toThis += sf::Vector2f(m_lookAt.y, -m_lookAt.x);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		toThis += sf::Vector2f(m_lookAt.y, -m_lookAt.x) * -1.f;
	}*/

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		toThis += sf::Vector2f(0.f,-1.f);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		toThis += sf::Vector2f(0.f,1.f);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		toThis += sf::Vector2f(-1.f,0.f);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		toThis += sf::Vector2f(1.f,0.f);
	}

	sf::Vector2f position = toThis * float(m_walkingspeed * GlobalClock::Ref().ElapsedTime().asSeconds() * 500);
	if(m_position != m_position + position)
	{
		m_position += position;
		m_sprite = m_animation.GetNext();
	}

	m_sprite.setPosition(m_position);
}

const int Player::GetNextSpell()
{
	int spelltype = -1;
	if(!m_spells.empty())
	{
		 spelltype = m_spells.front();
		m_spells.pop();
	}

	return spelltype;
}

const sf::Sprite& Player::GetSprite() const
{
	return m_sprite;
}

const sf::Vector2f&	Player::GetPosition() const
{
	return m_position;
}

const sf::Vector2f& Player::GetTarget() const
{
	return m_target;
}

const sf::Vector2f& Player::GetLookAt() const
{
	return m_lookAt;
}

const float Player::GetRotation() const
{
	return m_rotation;
}

const double Player::GetDamage() const
{
	return m_damage;
}

const double Player::GetHealth() const
{
	return m_health;
}

const double Player::GetAttackspeed() const
{
	return m_attackspeed;
}

const double Player::GetWalkingspeed() const
{
	return m_walkingspeed;
}

const double Player::GetConcentration() const
{
	return m_concentration;
}

const Animation& Player::GetAnimation() const
{
	return m_animation;
}

const int Player::GetPoints() const
{
	return m_points;
}

void Player::DamagePlayer(const double damage)
{
	m_health -= damage;
}

void Player::SetSprite(const sf::Sprite& sprite)
{
	m_sprite = sprite;
}

void Player::SetPosition(const sf::Vector2f& position)
{
	m_position = position;
}

void Player::SetTarget(const sf::Vector2f& target)
{
	m_target = target;
}

void Player::SetLookAt(const sf::Vector2f& lookAt)
{
	m_lookAt = lookAt;
}

void Player::SetRotation(const float rotation)
{
	m_rotation = rotation;
}

void Player::SetDamage(const double damage)
{
	m_damage = damage;
}

void Player::SetHealth(const double health)
{
	m_health = health;
}

void Player::SetAttackspeed(const double attackspeed)
{
	m_attackspeed = attackspeed;
}

void Player::SetWalkingspeed(const double walkingspeed)
{
	m_walkingspeed = walkingspeed;
}

void Player::SetConcentration(const double concentration)
{
	m_concentration = concentration;
}

void Player::SetAnimation(const Animation& animation)
{
	m_animation = animation;
}

void Player::SetPoints(const int points)
{
	m_points = points;
}

void Player::AddToPoints(const int points)
{
	m_points += points;
}