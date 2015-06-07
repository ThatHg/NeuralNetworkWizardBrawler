#ifndef OBSTACLE_H
#define OBSTACLE_H
//------------------------------------------------------------------------------
#include "VGCVirtualGameConsole.h"
//------------------------------------------------------------------------------
class Obstacle
{
public:
	Obstacle(VGCVector& position, double cost, double radius);
	Obstacle(const Obstacle& obstacle);
	~Obstacle();

	Obstacle& operator=(const Obstacle& obstacle);

	const VGCVector&	GetPosition() const;
	double				GetCost() const;
	double				GetRadius() const;

private:
	VGCVector	m_position;
	double		m_cost;
	double		m_raidus;
};
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------