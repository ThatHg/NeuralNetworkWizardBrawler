#ifndef ENTITY_REGISTER
#define ENTITY_REGISTER

#include <map>
#include <stack>

class EntityStateManager;
class Entity;

class EntityRegister
{
public:
	EntityRegister();
	~EntityRegister();
	EntityRegister(const EntityRegister& er);
	EntityRegister& operator=(const EntityRegister& er);
	
	void List(Entity* e, EntityStateManager& mgr);
	void Unlist(Entity* e, EntityStateManager& mgr);
	Entity* GetEntityByID(int ID);

private:
	typedef std::map<int, Entity*>	Entities;
	typedef std::stack<int>			IdStack;
	IdStack		m_oldIDs;
	Entities	m_entities;
	int			m_nextID;
};

#endif