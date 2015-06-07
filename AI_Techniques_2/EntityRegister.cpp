#include "EntityRegister.h"
#include "EntityStateManager.h"
#include "Entity.h"

EntityRegister::EntityRegister() : m_nextID(0)
{
}

EntityRegister::~EntityRegister()
{
}

void EntityRegister::List(Entity* e, EntityStateManager& mgr)
{
	// This links a state to a entity
	int ID = m_nextID;
	if(m_oldIDs.size() > 0)
	{
		ID = m_oldIDs.top();
		m_oldIDs.pop();
	}
	else
		m_nextID++;

	e->SetId(ID);
	m_entities[ID] = e;
	mgr.AddState(ID);
}

void EntityRegister::Unlist(Entity* e, EntityStateManager& mgr)
{
	// Unlink state and entity
	m_oldIDs.push(e->GetId());
	m_entities.erase(e->GetId());
	mgr.RemoveState(e->GetId());
}

Entity* EntityRegister::GetEntityByID(int ID)
{
	return m_entities.find(ID)->second;
}