#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include "lua.hpp"
#include "EntityStateManager.h"
#include "EntityRegister.h"
#include "Actor.h"

class Entity;
class Player;
class Spell;

class Level
{
public:
	Level(const char* filename, Player* player);
	~Level();

	void	Initialize();
	void	Render(sf::RenderWindow& window);
	void	Update();

	void	Spawn(const char* filename, const char* texture, int type);	// Spawn enemies until maxSpawenedEnemies is reached.

	int		GetTypeToSpawn();
	int		GetMaxEnemiesPerLevel();
	int		GetMaxEnemiesSpawend();

	void	AddSpell(Spell* spell);

private:
	typedef std::vector<Entity*>	Entities;
	typedef std::vector<Spell*>		Spells;
	typedef std::vector<sf::Sprite>	Sprites;

	void	Collision();
	void	CleanUp();
	bool	RadiusCollision(const sf::Vector2f& pos1, const float radius1, const sf::Vector2f& pos2, const float radius2);

	int					m_maxEnemiesPerLevel;
	int					m_maxEnemiesSpawend;
	int					m_enemyCounter;
	Entities			m_entities;
	lua_State*			m_state;
	std::stack<int>		m_types;				// Pushes type of enemy to spawn on stack
	EntityStateManager	m_mgr;
	EntityRegister		m_register;
	Player*				m_player;
	Spells				m_spells;
	Sprites				m_walls;
};

#endif