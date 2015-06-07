#include "Event.h"
#include "Entity.h"

void Enter::Execute(Entity* entity)
{

}

void Exit::Execute(Entity* entity)
{
	
}

void Idle::Execute(Entity* entity)
{
	// Dont do anything with entity cause it's idling :3
}

void AttackEvent::Execute(Entity* entity)
{
	entity->Attack();
}

void DamageEvent::Execute(Entity* entity)
{
	double damage = entity->GetLatestDamage();
	while(damage != -1) 
	{
		entity->SetHealth(entity->GetHealth() - damage);
		damage = entity->GetLatestDamage();
	}
}

void DeathEvent::Execute(Entity* entity)
{
	// Do some cool death stuff
}

void MoveEvent::Execute(Entity* entity)
{
	entity->Move();
}