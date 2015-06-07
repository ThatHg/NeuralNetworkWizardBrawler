#ifndef AGENT_MANAGER_H
#define AGENT_MANAGER_H

#include <vector>
#include "AStar.h"

class Agent;

class AgentManager
{
public:
	typedef std::vector<Agent*> AgentVector;

	AgentManager();
	~AgentManager();

	void Update(sf::RenderWindow& rw);

private:
	void InitiateAgents();
	void Move();
	void ManageAgentTargets();
	void Paint(sf::RenderWindow& rw);

	AgentVector m_agents;
	AStar		m_astar;
};

#endif