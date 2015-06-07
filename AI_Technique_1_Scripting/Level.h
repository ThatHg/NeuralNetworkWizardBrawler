#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include "lua.hpp"
#include "EntityStateManager.h"
#include "EntityRegister.h"

class Entity;

class Level
{
public:
	Level(const char* filename);
	~Level();

	void	Initialize();
	void	Render(sf::RenderWindow& window);
	void	Update();
	void	Spawn(const char* filename, const char* texture, int type);	// Spawn enemies until maxSpawenedEnemies is reached.
	int		GetTypeToSpawn();
	int		GetMaxEnemiesPerLevel();
	int		GetMaxEnemiesSpawend();	


private:
	typedef std::vector<Entity*> Entities;

	int					m_maxEnemiesPerLevel;
	int					m_maxEnemiesSpawend;
	Entities			m_entities;
	lua_State*			m_state;
	std::stack<int>		m_types;				// Pushes type of enemy to spawn on stack
	EntityStateManager	m_mgr;
	EntityRegister		m_register;

};

#endif