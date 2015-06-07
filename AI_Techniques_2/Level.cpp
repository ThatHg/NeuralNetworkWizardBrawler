#include "Level.h"
#include "Entity.h"
#include "Melee.h"
#include "Ranger.h"
#include <iostream>
#include "AssetsManager.h"
#include "Helper.h"
#include "Player.h"
#include "Spell.h"

#include <sstream>

using namespace std;

static void lua_Spawn(Level* level, const char* filename, const char* texture, const int type)
{
	level->Spawn(filename, texture, type);
}

static int lua_SpawnWrapper(lua_State* state)
{
	const int arguments = lua_gettop(state);
	if(arguments != 4)
		cerr << "\nERROR: Invalid amount of arguments on stack. [" << arguments << "]";
	if(!lua_islightuserdata(state, 1))
		cerr << "\nERROR: First argument is not of type [light user data].";
	if(!lua_isstring(state, 2))
		cerr << "\nERROR: Second argument is not of type [string].";
	if(!lua_isstring(state, 3))
		cerr << "\nERROR: Third argument is not of type [string].";
	if(!lua_isnumber(state, 4))
		cerr << "\nERROR: Fourth argument is not of type [number].";

	Level* level			= (Level*)(lua_touserdata(state, 1));
	const char* filename	= lua_tostring(state, 2);
	const char*	texture		= lua_tostring(state, 3);
	const int type			= (int)lua_tonumber(state, 4);
	lua_Spawn(level, filename, texture, type);

	return 0;
}

static int lua_GetMaxEnemiesSpawned(Level* level)
{
	return level->GetMaxEnemiesSpawend();
}

static int lua_GetMaxEnemiesSpawnedWrapper(lua_State* state)
{

	const int arguments = lua_gettop(state);
	if(arguments != 1)
		cerr << "\nERROR: Invalid amount of arguments on stack. [" << arguments << "]";

	Level* level = (Level*)(lua_touserdata(state, 1));
	int number = lua_GetMaxEnemiesSpawned(level);
	lua_pushnumber(state, number);

	return 1;
}

static int lua_GetTypeToSpawn(Level* level)
{
	return level->GetTypeToSpawn();
}

static int lua_GetTypeToSpawnWrapper(lua_State* state)
{
	const int arguments = lua_gettop(state);
	if(arguments != 1)
		cerr << "\nERROR: Invalid amount of arguments on stack. [" << arguments << "]";

	Level* level = (Level*)(lua_touserdata(state, 1));
	int type = lua_GetTypeToSpawn(level);

	if(type == -1)
		cerr << "\nERROR: There are no types ready to spawn from stack.";

	lua_pushnumber(state, type);

	return 1;
}

Level::Level(const char* filename, Player* player) :
	m_state(luaL_newstate()),
	m_maxEnemiesPerLevel(20),
	m_maxEnemiesSpawend(6),
	m_entities(),
	m_types(),
	m_mgr(),
	m_register(),
	m_player(player),
	m_spells(),
	m_enemyCounter(0)
{
	if(m_state == 0)
		cerr << "\nERROR: Unable to create lua state." << endl;

	luaL_openlibs(m_state);
 
	if(luaL_dofile(m_state, filename))
	{
		const char* err = lua_tostring(m_state, -1);
		cerr << "\nERROR: " << err;
	}

	lua_register(m_state, "spawn", lua_SpawnWrapper);
	lua_register(m_state, "get_maxenemies", lua_GetMaxEnemiesSpawnedWrapper);
	lua_register(m_state, "get_typetospawn", lua_GetTypeToSpawnWrapper);
}

Level::~Level()
{
	while(!m_entities.empty())
	{
		delete m_entities.back();
		m_entities.pop_back();
	}
	lua_close(m_state);
	m_state = 0;
}

void Level::Initialize()
{
	// Initialize first wave of enemies
	lua_getglobal(m_state, "initialize");
	if(!lua_isfunction(m_state, -1))
		cerr << "\nERROR: Invalide function name [initialize]";

	lua_pushlightuserdata(m_state, this);
	lua_call(m_state, 1, 0);
}

void Level::Render(sf::RenderWindow& window)
{
	/*sf::Font font;
	font.loadFromFile("Assets/Fonts/consola.ttf");*/

	for(Entities::iterator eItr = m_entities.begin(); eItr != m_entities.end(); eItr++)
	{
		/*sf::Vector2f pos = (*eItr)->GetPosition();
		stringstream ss;
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(12);
		text.setColor(sf::Color(0,200,0));
		ss << (*eItr)->GetDump().str() << endl;
		text.setPosition((*eItr)->GetPosition());
		text.setString(ss.str());
		window.draw(text);*/
		window.draw((*eItr)->GetSprite());
		/*sf::Sprite sprite = (*eItr)->GetSprite();
		sprite.setPosition((*eItr)->GetTarget());
		sprite.setRotation(0);
		window.draw(sprite);*/
	}

	for(Spells::iterator sItr = m_spells.begin(); sItr != m_spells.end(); sItr++)
	{
		(*sItr)->Render(window);
	}

	for(Sprites::iterator sItr = m_walls.begin(); sItr != m_walls.end(); sItr++)
	{
		window.draw(*sItr);
	}
}

void Level::Update()
{
	if(m_entities.size() < m_maxEnemiesSpawend)
	{
		// Spawn new enemy
		lua_getglobal(m_state, "spawn_enemy");
		if(!lua_isfunction(m_state, -1))
			cerr << "\nERROR: Invalide function name [spawn_enemy]";

		lua_pushlightuserdata(m_state, this);
		lua_call(m_state, 1, 0);
	}

	sf::Vector2f target = m_player->GetPosition();
	for(Entities::iterator eItr = m_entities.begin(); eItr != m_entities.end(); eItr++)
	{
		(*eItr)->Update(&m_mgr);
		(*eItr)->SetTarget(target);
		switch((*eItr)->GetNextSpell())
		{
		case 4:
			cout << "\nMAGICS_ALERT: Ranger casts <ARROW>.";
			AddSpell(new Spell((*eItr)->GetDamage(), false, Spell::ARROW, sf::Sprite(AssetsManager::GetReference().GetTexture("arrow-up_red.png")), (*eItr)->GetPosition(), (*eItr)->GetLookAt()));
			break;
		case 5:
			AddSpell(new Spell((*eItr)->GetDamage(), false, Spell::FIST, sf::Sprite(AssetsManager::GetReference().GetTexture("clenched-fist-xl.png")), (*eItr)->GetPosition(), (*eItr)->GetLookAt()));
			break;
		default:
			break;
		}
	}

	for(Spells::iterator sItr = m_spells.begin(); sItr != m_spells.end(); sItr++)
	{
		(*sItr)->Update();
	}

	// If player has cast a spell. Then we should be able
	// to Spawn it here.
	switch (m_player->GetNextSpell())
	{
	case 0:
		cout << "\nMAGICS_ALERT: Player casts <FIRE>.";
		AddSpell(new Spell(m_player->GetDamage(), true, Spell::FIRE, sf::Sprite(AssetsManager::GetReference().GetTexture("fire.png")), m_player->GetPosition(), m_player->GetLookAt()));
		break;
	case 1:
		cout << "\nMAGICS_ALERT: Player casts <WATER>.";
		AddSpell(new Spell(m_player->GetDamage(), true, Spell::WATER, sf::Sprite(AssetsManager::GetReference().GetTexture("water.png")), m_player->GetPosition(), m_player->GetLookAt()));
		break;
	case 2:
		cout << "\nMAGICS_ALERT: Player casts <EARTH>.";
		AddSpell(new Spell(m_player->GetDamage(), true, Spell::EARTH, sf::Sprite(AssetsManager::GetReference().GetTexture("earth.png")), m_player->GetPosition(), m_player->GetLookAt()));
		break;
	case 3:
		cout << "\nMAGICS_ALERT: Player casts <AIR>.";
		AddSpell(new Spell(m_player->GetDamage(), true, Spell::AIR, sf::Sprite(AssetsManager::GetReference().GetTexture("air.png")), m_player->GetPosition(), m_player->GetLookAt()));
		break;
	default:
		break;
	}

	Collision();	// Handle collisions
	CleanUp();		// Clean up dead spells and enemies
}

void Level::CleanUp()
{
	for(Spells::iterator sItr = m_spells.begin(); sItr != m_spells.end();)
	{
		if((*sItr)->IsAlive())
		{
			sItr++;
		}
		else
		{
			delete *sItr;
			sItr = m_spells.erase(sItr);
		}
	}

	for(Entities::iterator eItr = m_entities.begin(); eItr != m_entities.end();)
	{
		if((*eItr)->IsAlive())
		{
			eItr++;
		}
		else
		{
			if(m_enemyCounter == m_maxEnemiesPerLevel)
			{
				m_types.push(int(Random(2,3.99999)));	// Spawn boss next time
				m_enemyCounter = 0;
			}
			else
			{
				m_types.push(int(Random(0,1.99999)));	// spawn regular enemy next time
			}
			// Delete enemy *********
			m_register.Unlist(*eItr, m_mgr); // Unlist from register unlink fram statemachine
			delete *eItr;
			eItr = m_entities.erase(eItr);
		}
	}
}

void Level::Collision()
{
	float rad1 = 0;
	float rad2 = 0;
	sf::Vector2f pos1;
	sf::Vector2f pos2;
	for(Spells::iterator sItr = m_spells.begin(); sItr != m_spells.end(); sItr++)
	{
		rad2 = (*sItr)->GetSprite().getTextureRect().width/2;
		pos2 = (*sItr)->GetSprite().getPosition();
		for(Entities::iterator eItr = m_entities.begin(); eItr != m_entities.end(); eItr++)
		{
			rad1 = (*eItr)->GetSprite().getTextureRect().width/2;
			pos1 = (*eItr)->GetSprite().getPosition();
			if((*sItr)->IsAlive() && (*sItr)->IsFriendly() && RadiusCollision(pos1, rad1, pos2, rad2))
			{
				if(int((*eItr)->GetImmunity()) != int((*sItr)->GetType()))
					(*eItr)->AddDamage((*sItr)->GetDamage());
				(*sItr)->SetAlive(false);
			}
		}
		rad1 = m_player->GetSprite().getTextureRect().width/2;
		pos1 = m_player->GetSprite().getPosition();
		if((*sItr)->IsAlive() && !(*sItr)->IsFriendly() && RadiusCollision(pos1, rad1, pos2, rad2))
		{
			m_player->DamagePlayer((*sItr)->GetDamage());
			(*sItr)->SetAlive(false);
		}
	}
}

bool Level::RadiusCollision(const sf::Vector2f& pos1, const float radius1, const sf::Vector2f& pos2, const float radius2)
{
	return Distance(pos1, pos2) <= radius1 + radius2;	
}

void Level::Spawn(const char* filename, const char* texture, int type)
{
	// Spawn new enemies
	float x = (float)Random(0, 1280);
	float y = (float)Random(0, 720);
	bool error = false;
	switch (type)
	{
	case 0:
		m_entities.push_back(new Melee(	m_entities.size(),
										type,
										sf::Sprite(AssetsManager::GetReference().GetTexture(texture)),
										sf::Vector2f(640.0f, 360.0f),
										sf::Vector2f(x,y),
										filename));
		break;
	case 1:
		m_entities.push_back(new Ranger(m_entities.size(),
										type,
										sf::Sprite(AssetsManager::GetReference().GetTexture(texture)),
										sf::Vector2f(640.0f, 360.0f),
										sf::Vector2f(x,y),
										filename));
		break;
	default:
		cerr << "\nERROR invalid type [" << type << "]";
		error = true;
		break;
	}

	if(!error)
	{
		m_enemyCounter++;
		m_register.List(m_entities.back(), m_mgr);	// Link an enemie to a statemachine
	}
}

int Level::GetMaxEnemiesPerLevel()
{
	return m_maxEnemiesPerLevel;
}

int Level::GetMaxEnemiesSpawend()
{
	return m_maxEnemiesSpawend;
}

int Level::GetTypeToSpawn()
{
	if(m_types.empty())
		return -1;

	int type = m_types.top();
	m_types.pop();

	return type;
}

void Level::AddSpell(Spell* spell)
{
	m_spells.push_back(spell);
}