#ifndef CONFIG_H
#define CONFIG_H

#include "lua.hpp"
#include <iostream>

class Config
{
public:
	Config(const char* filename) : m_state(luaL_newstate())
	{
		if(m_state == 0)
			std::cerr << "\nERROR: Unable to create lua state." << std::endl;

		luaL_openlibs(m_state);
 
		if(luaL_dofile(m_state, filename))
		{
			const char* err = lua_tostring(m_state, -1);
			std::cerr << "\nERROR: " << err;
		}
	}

	~Config()	{ lua_close(m_state); }

	inline double Config::GrabReal(const char* name) const
	{
		lua_getglobal(m_state, name);
		if(!lua_isnumber(m_state, -1))
			std::cerr << "\nERROR: [" << name << "] Invalid real.";

		const double real = lua_tonumber(m_state, -1);
		lua_pop(m_state, 1);
		return real;
	}

	inline const char* Config::GrabString(const char* name) const
	{
		lua_getglobal(m_state, name);
		if(!lua_isstring(m_state, -1))
			std::cerr << "\nERROR: [" << name << "] Invalid string.";

		const char* string = lua_tostring(m_state, -1);
		lua_pop(m_state, 1);
		return string;
	}

	inline bool Config::GrabBoolean(const char* name) const
	{
		lua_getglobal(m_state, name);
		if(!lua_isboolean(m_state, -1))
			std::cerr << "\nERROR: [" << name << "] Invalid boolean.";

		const bool boolean = lua_toboolean(m_state, -1);
		lua_pop(m_state, 1);
		return boolean;
	}

	inline int Config::GrabInteger(const char* name) const
	{
		lua_getglobal(m_state, name);
		if(!lua_isnumber(m_state, -1))
			std::cerr << "\nERROR: [" << name << "] Invalid integer";

		const int integer = int(lua_tonumber(m_state, -1));
		lua_pop(m_state, 1);
		return integer;
	}

private:
	lua_State*	m_state;
};

#endif