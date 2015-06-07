#ifndef ENTITY_STATE_MANAGER_H
#define ENTITY_STATE_MANAGER_H

#include "Event.h"
#include <map>

class Entity;

class EntityStateManager
{
public:
	EntityStateManager();
	~EntityStateManager();

	typedef void (EntityStateManager::*State)(const Event& e, Entity* entity);
	
	void AddState(int ID);	// Map entity ID to a state
	void RemoveState(int ID);

	void Handle(const Event& e, Entity* entity);

private:
	typedef std::map<int, State> States;

	void Dispatch(const Event& e, Entity* entity);
	void Transit(State toState, Entity* entity);
	
	void HandleIdling(const Event& e, Entity* entity);
	void HandleAttacking(const Event& e, Entity* entity);
	void HandleMoving(const Event& e, Entity* entity);
	void HandleTakingDamage(const Event& e, Entity* entity);
	void HandleDies(const Event& e, Entity* entity);
	
	States	m_states;
};

#endif