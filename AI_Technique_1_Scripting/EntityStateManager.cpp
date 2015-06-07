#include "EntityStateManager.h"
#include "Entity.h"
#include <iostream>

using namespace std;

EntityStateManager::EntityStateManager()
{
}

EntityStateManager::~EntityStateManager()
{
}

void EntityStateManager::AddState(int ID)
{
	m_states[ID] = (&EntityStateManager::HandleIdling);
}

void EntityStateManager::RemoveState(int ID)
{
	m_states.erase(ID);
}

void EntityStateManager::Handle(const Event& e, Entity* entity)
{
	Dispatch(e, entity);
}

void EntityStateManager::Dispatch(const Event& e, Entity* entity)
{
	(this->*m_states[entity->GetId()])(e, entity);
}

void EntityStateManager::Transit(State toState, Entity* entity)
{
	Dispatch(Exit(), entity);
	m_states[entity->GetId()] = toState;
	Dispatch(Enter(), entity);
}

void EntityStateManager::HandleIdling(const Event& e, Entity* entity)
{
	switch (e.GetType())
	{
	case Event::ENTER:
		cout << "\nALERT: Entering [Idle] state.";
		if(Enter* enter = (Enter*)&e) { enter->Execute(entity); }
		break;
	case Event::EXIT:
		cout << "\nALERT: Exiting [Idle] state.";
		if(Exit* exit = (Exit*)&e) { exit->Execute(entity); }
		break;
	case Event::ATTACK:
		Transit(&EntityStateManager::HandleAttacking, entity);
		break;
	case Event::DAMAGE:
		Transit(&EntityStateManager::HandleTakingDamage, entity);
		break;
	case Event::DEATH:
		Transit(&EntityStateManager::HandleDies, entity);
		break;
	case Event::MOVE:
		Transit(&EntityStateManager::HandleMoving, entity);
		break;
	case Event::IDLE:
		if(Idle* idle = (Idle*)&e) { idle->Execute(entity); }
		break;
	default:
		break;
	}
}

void EntityStateManager::HandleAttacking(const Event& e, Entity* entity)
{
	switch (e.GetType())
	{
	case Event::ENTER:
		cout << "\nALERT: Entering [Attacking] state.";
		if(Enter* enter = (Enter*)&e) { enter->Execute(entity); }
		break;
	case Event::EXIT:
		cout << "\nALERT: Exiting [Attacking] state.";
		if(Exit* exit = (Exit*)&e) { exit->Execute(entity); }
		break;
	case Event::ATTACK:
		if(AttackEvent* attack = (AttackEvent*)&e) { attack->Execute(entity); }
		break;
	case Event::DAMAGE:
		Transit(&EntityStateManager::HandleTakingDamage, entity);
		break;
	case Event::DEATH:
		Transit(&EntityStateManager::HandleDies, entity);
		break;
	case Event::MOVE:
		Transit(&EntityStateManager::HandleMoving, entity);
		break;
	case Event::IDLE:
		Transit(&EntityStateManager::HandleIdling, entity);
		break;
	default:
		break;
	}
}

void EntityStateManager::HandleMoving(const Event& e, Entity* entity)
{
	switch (e.GetType())
	{
	case Event::ENTER:
		cout << "\nALERT: Entering [Moving] state.";
		if(Enter* enter = (Enter*)&e) { enter->Execute(entity); }
		break;
	case Event::EXIT:
		cout << "\nALERT: Exiting [Moving] state.";
		if(Exit* exit = (Exit*)&e) { exit->Execute(entity); }
		break;
	case Event::ATTACK:
		Transit(&EntityStateManager::HandleAttacking, entity);
		break;
	case Event::DAMAGE:
		Transit(&EntityStateManager::HandleTakingDamage, entity);
		break;
	case Event::DEATH:
		Transit(&EntityStateManager::HandleDies, entity);
		break;
	case Event::MOVE:
		if(MoveEvent* move = (MoveEvent*)&e) { move->Execute(entity); }
		break;
	case Event::IDLE:
		Transit(&EntityStateManager::HandleIdling, entity);
		break;
	default:
		break;
	}
}

void EntityStateManager::HandleTakingDamage(const Event& e, Entity* entity)
{
	switch (e.GetType())
	{
	case Event::ENTER:
		cout << "\nALERT: Entering [Taking Damage] state.";
		if(Enter* enter = (Enter*)&e) { enter->Execute(entity); }
		break;
	case Event::EXIT:
		cout << "\nALERT: Exiting [Taking Damage] state.";
		if(Exit* exit = (Exit*)&e) { exit->Execute(entity); }
		break;
	case Event::ATTACK:
		Transit(&EntityStateManager::HandleAttacking, entity);
		break;
	case Event::DAMAGE:
		if(DamageEvent* damage = (DamageEvent*)&e) { damage->Execute(entity); }
		break;
	case Event::DEATH:
		Transit(&EntityStateManager::HandleDies, entity);
		break;
	case Event::MOVE:
		Transit(&EntityStateManager::HandleMoving, entity);
		break;
	case Event::IDLE:
		Transit(&EntityStateManager::HandleIdling, entity);
		break;
	default:
		break;
	}
}

void EntityStateManager::HandleDies(const Event& e, Entity* entity)
{
	switch (e.GetType())
	{
	case Event::ENTER:
		cout << "\nALERT: Entering [Death] state.";
		if(Enter* enter = (Enter*)&e) { enter->Execute(entity); }
		break;
	case Event::EXIT:
		cout << "\nALERT: Exiting [Death] state.";
		if(Exit* exit = (Exit*)&e) { exit->Execute(entity); }
		break;
	case Event::ATTACK:
		Transit(&EntityStateManager::HandleAttacking, entity);
		break;
	case Event::DAMAGE:
		Transit(&EntityStateManager::HandleTakingDamage, entity);
		break;
	case Event::DEATH:
		if(DeathEvent* death = (DeathEvent*)&e) { death->Execute(entity); }
		break;
	case Event::MOVE:
		Transit(&EntityStateManager::HandleMoving, entity);
		break;
	case Event::IDLE:
		Transit(&EntityStateManager::HandleIdling, entity);
		break;
	default:
		break;
	}
}