#ifndef OBSTACLE_FIELD_H
#define OBSTACLE_FIELD_H
//------------------------------------------------------------------------------
#include "VGCVirtualGameConsole.h"
#include <vector>
//------------------------------------------------------------------------------
class Obstacle;
//------------------------------------------------------------------------------
class ObstacleField
{
public:
	typedef std::vector<Obstacle*> ObstacleVector;

	ObstacleField(int numObstacles, int areaWidth, int areaHeight, double minRadius, double maxRadius, double minCost, double maxCost);
	ObstacleField(const ObstacleField& obstacleField);
	~ObstacleField();
	ObstacleField& operator=(const ObstacleField& obstacleField);

	const	ObstacleVector& GetObstacles() const;
	const	std::vector<int> GetObstaclesAtPosition(const VGCVector& position) const;
	const	std::vector<int> GetObstaclesBetweenPositions(const VGCVector& from, const VGCVector& to) const;
	int		GetNumObstacles() const;
	double	GetObstacleCost(int index) const;
	int		GetWidth() const;
	int		GetHeight() const;
	double	GetMaxObstacleCost() const;


private:
	double GetLength(const VGCVector& from, const VGCVector& to) const;

	ObstacleVector	m_obstacles;
	int				m_width;
	int				m_height;
};
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------