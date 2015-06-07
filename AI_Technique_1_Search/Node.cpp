#include "Node.h"

Node::Node(int index, sf::Vector2f position) : 
	m_index(index),
	m_position(position),
	m_costToRoot(-1.0),
	m_costToTarget(-1.0),
	m_parent(NULL)
{
}

Node::~Node()
{
}

int Node::GetIndex() const
{
	return m_index;
}

const sf::Vector2f& Node::GetPosition() const
{
	return m_position;
}

const double Node::GetCostToTarget() const
{
	return m_costToTarget;
}

const double Node::GetCostToRoot() const
{
	return m_costToRoot;
}

double Node::GetCostToTarget()
{
	return m_costToTarget;
}

double Node::GetCostToRoot()
{
	return m_costToRoot;
}

const Node* Node::GetParent() const
{
	return m_parent;
}

void Node::SetIndex(int index)
{
	m_index = index;
}

void Node::SetPosition(sf::Vector2f& position)
{
	m_position = position;
}

void Node::SetCostToTarget(double cost)
{
	m_costToTarget = cost;
}

void Node::SetCostToRoot(double cost)
{
	m_costToRoot = cost;
}

void Node::SetParent(const Node* node)
{
	m_parent = node;
}