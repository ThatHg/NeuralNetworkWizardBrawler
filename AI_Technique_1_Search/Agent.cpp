#include "Agent.h"
#include "Node.h"

Agent::Agent(sf::Vector2f& position, sf::Vector2f& target, std::vector<const Node*> subtargets):
	m_position(position),
	m_target(target),
	m_subtargets(subtargets),
	m_nodeIndex(0)
{
}

Agent::~Agent()
{
}

void Agent::SetPosition(sf::Vector2f& position)
{
	m_position = position;
}

void Agent::SetTarget(sf::Vector2f& target)
{
	m_target = target;
}

void Agent::SetSubtarget(sf::Vector2f& subtarget)
{
	m_subtarget = subtarget;
}

void Agent::SetSubtargets(std::vector<const Node*>& subtargets)
{
	// if we update subtargets then reset the index too
	m_nodeIndex = 0;
	m_subtargets = subtargets;
}

const sf::Vector2f& Agent::GetPosition() const
{
	return m_position;
}

sf::Vector2f& Agent::GetPosition()
{
	return m_position;
}

const sf::Vector2f& Agent::GetTarget() const
{
	return m_target;
}

const Node* Agent::GetSubtarget() const
{
	return m_subtargets[m_nodeIndex];
}

const std::vector<const Node*>& Agent::GetSubtargets() const
{
	return m_subtargets;
}

void Agent::ChangeSubtarget()
{
	m_nodeIndex++;
}