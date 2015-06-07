#include "Edge.h"
#include "Node.h"
#include <math.h>

Edge::Edge(Node* first, Node* second):
	m_first(first),
	m_second(second)
{
}

Edge::~Edge()
{
}
void Edge::SetFirstNode(Node* first)
{
	m_first = first;
}
	

const Node* Edge::First() const
{
	return m_first;
}

Node* Edge::First()
{
	return m_first;
}

void Edge::SetSecondNode(Node* second)
{
	m_second = second;
}

const Node* Edge::Second() const
{
	return m_second;
}

Node* Edge::Second()
{
	return m_second;
}

double Edge::Distance()
{
	double xD = m_second->GetPosition().x - m_first->GetPosition().x;
	double yD = m_second->GetPosition().y - m_first->GetPosition().y;
	return std::sqrt(xD * xD + yD * yD);
}