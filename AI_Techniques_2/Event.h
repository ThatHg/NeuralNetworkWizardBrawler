#ifndef EVENT_H
#define EVENT_H

class Entity;

class Event
{
public:
	enum Type{ENTER, EXIT, IDLE, ATTACK, DAMAGE, DEATH, MOVE};
	Event(Type t) : m_type(t){};
	virtual ~Event(){};
	virtual void Execute(Entity* entity) = 0;

	inline const Type GetType() const {return m_type;};
private:
	Type m_type;
};

class Enter : public Event 
{
public:
	Enter() : Event(ENTER){};
	~Enter(){};

	void Execute(Entity* entity);
};

class Exit : public Event 
{
public:
	Exit() : Event(EXIT){};
	~Exit(){};

	void Execute(Entity* entity);
};

class Idle : public Event
{
public:
	Idle() : Event(IDLE){};
	~Idle(){};

	void Execute(Entity* entity);
};

class AttackEvent : public Event
{
public:
	AttackEvent() : Event(ATTACK){};
	~AttackEvent(){};

	void Execute(Entity* entity);
};

class DamageEvent : public Event
{
public:
	DamageEvent() : Event(DAMAGE){};
	~DamageEvent(){};

	void Execute(Entity* entity);
};

class DeathEvent : public Event
{
public:
	DeathEvent() : Event(DEATH){};
	~DeathEvent(){};

	void Execute(Entity* entity);
};

class MoveEvent : public Event
{
public:
	MoveEvent() : Event(MOVE){};
	~MoveEvent(){};

	void Execute(Entity* entity);
};

#endif