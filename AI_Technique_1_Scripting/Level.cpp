#include "Level.h"
#include "Entity.h"
#include "Melee.h"
#include "Ranger.h"
#include <iostream>
#include "AssetsManager.h"
#include "Helper.h"
#include "GlobalClock.h"

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

Level::Level(const char* filename) :
	m_state(luaL_newstate()),
	m_maxEnemiesPerLevel(100),
	m_maxEnemiesSpawend(6),
	m_entities(),
	m_types(),
	m_mgr(),
	m_register()
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
	sf::Font font;
	font.loadFromFile("Assets/Fonts/consola.ttf");

	for(Entities::iterator eItr = m_entities.begin(); eItr != m_entities.end(); eItr++)
	{
		sf::Vector2f pos = (*eItr)->GetPosition();
		stringstream ss;
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(12);
		text.setColor(sf::Color(0,200,0));

		switch ((*eItr)->GetType())
		{
		case 0:		ss << "Type: Melee Trainee"		<< endl; break;
		case 1:		ss << "Type: Ranger Trainee"	<< endl; break;
		case 2:		ss << "Type: Melee Boss"		<< endl; break;
		case 3:		ss << "Type: Ranger Boss"		<< endl; break;
		default:	ss << "Type: Undefined"			<< endl; break;
		}
		ss << "LookAt: (" << (*eItr)->GetLookAt().x << ", " << (*eItr)->GetLookAt().y << ")" << endl;
		ss << "Position: (" << (*eItr)->GetPosition().x << ", " << (*eItr)->GetPosition().y << ")" << endl;
		ss << "Rotation: " << (*eItr)->GetRotation() << endl;
		ss << "Target: (" << (*eItr)->GetTarget().x << ", " << (*eItr)->GetTarget().y << ")" << endl;
		ss << "Walking Speed: " << (*eItr)->GetWalkingSpeed() << endl;
		ss << "Is Alive: " << (*eItr)->IsAlive() << endl;
		ss << (*eItr)->GetDump().str() << endl;
		text.setPosition((*eItr)->GetPosition());
		text.setString(ss.str());
		window.draw(text);
		window.draw((*eItr)->GetSprite());
		sf::Sprite sprite = (*eItr)->GetSprite();
		sprite.setPosition((*eItr)->GetTarget());
		sprite.setRotation(0);
		window.draw(sprite);
	}
}

void Level::Update()
{
	GlobalClock::Ref().Reset();

	for(Entities::iterator eItr = m_entities.begin(); eItr != m_entities.end(); eItr++)
	{
		if(!(*eItr)->IsAlive())
		{
			m_types.push((*eItr)->GetType());

			// Delete enemy *********
			m_register.Unlist(*eItr, m_mgr);
			eItr = m_entities.erase(eItr);

			lua_getglobal(m_state, "spawn_enemy");
			if(!lua_isfunction(m_state, -1))
				cerr << "\nERROR: Invalide function name [spawn_enemy]";

			lua_pushlightuserdata(m_state, this);
			lua_call(m_state, 1, 0);

		}
		else
			(*eItr)->Update(&m_mgr);
	}
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
										sf::Vector2f(x,y),
										filename));
		break;
	case 1:
		m_entities.push_back(new Ranger(m_entities.size(),
										type,
										sf::Sprite(AssetsManager::GetReference().GetTexture(texture)),
										sf::Vector2f(x,y),
										filename));
		break;
	default:
		cerr << "\nERROR invalid type [" << type << "]";
		error = true;
		break;
	}

	if(!error)
		m_register.List(m_entities.back(), m_mgr);

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