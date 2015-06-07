#include "Obstacle.h"
//------------------------------------------------------------------------------
Obstacle::Obstacle(VGCVector& position, double cost, double radius):
	m_position(position),
	m_cost(cost),
	m_raidus(radius)
{
}
//------------------------------------------------------------------------------
Obstacle::Obstacle(const Obstacle& obstacle):
	m_position(obstacle.m_position),
	m_cost(obstacle.m_cost),
	m_raidus(obstacle.m_raidus)
{
}
//------------------------------------------------------------------------------
Obstacle::~Obstacle()
{
}
//------------------------------------------------------------------------------
Obstacle& Obstacle::operator=(const Obstacle& obstacle)
{
	m_position	= obstacle.m_position;
	m_cost		= obstacle.m_cost;
	m_raidus	= obstacle.m_raidus;

	return *this;
}
//------------------------------------------------------------------------------
const VGCVector& Obstacle::GetPosition() const
{
	return m_position;
}
//------------------------------------------------------------------------------
double Obstacle::GetCost() const
{
	return m_cost;
}
//------------------------------------------------------------------------------
double Obstacle::GetRadius() const
{
	return m_raidus;
}
//------------------------------------------------------------------------------