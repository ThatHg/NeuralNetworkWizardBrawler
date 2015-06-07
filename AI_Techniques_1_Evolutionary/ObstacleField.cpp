#include "ObstacleField.h"
#include "RNDRandom.h"
#include "Obstacle.h"
#include <math.h>
//------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------
/*
	Code taken from http://www.melloland.com/scripts-and-tutos/collision-detection-between-circles-and-lines
*/
bool lineInCircle(double ax, double ay, double bx, double by, double cx, double cy, double cr)
{
    double vx = bx - ax;
    double vy = by - ay;
    double xdiff = ax - cx;
    double ydiff = ay - cy;
    double a = pow(vx, 2) + pow(vy, 2);
    double b = 2 * ((vx * xdiff) + (vy * ydiff));
    double c = pow(xdiff, 2) + pow(ydiff, 2) - pow(cr, 2);
    double quad = pow(b, 2) - (4 * a * c);
    if (quad >= 0)
    {
        // An infinite collision is happening, but let's not stop here
        float quadsqrt=sqrt(quad);
        for (int i = -1; i <= 1; i += 2)
        {
            // Returns the two coordinates of the intersection points
            float t = (i * -b + quadsqrt) / (2 * a);
            float x = ax + (i * vx * t);
            float y = ay + (i * vy * t);
            // If one of them is in the boundaries of the segment, it collides
            if (x >= min(ax, bx) && x <= max(ax, bx) && y >= min(ay, by) && y <= max(ay, by)) return true;
        }
    }
    return false;
}
/************************************************************************/

//------------------------------------------------------------------------------
ObstacleField::ObstacleField(int numObstacles, int areaWidth, int areaHeight, double minRadius, double maxRadius, double minCost, double maxCost):
	m_width(areaWidth),
	m_height(areaHeight)
{
	// Generate random placed obstacles within the area
	RNDRandom random;
	for(int i=0; i<numObstacles; i++)
	{
		m_obstacles.push_back(new Obstacle(	VGCVector(random.generateUniformInteger(0, areaWidth), random.generateUniformInteger(0, areaHeight)),
											random.generateUniformReal(minCost, maxCost),
											random.generateUniformReal(minRadius, maxRadius)));
	}
}
//------------------------------------------------------------------------------
ObstacleField::ObstacleField(const ObstacleField& obstacleField):
	m_obstacles(obstacleField.m_obstacles)
{
}
//------------------------------------------------------------------------------
ObstacleField::~ObstacleField()
{
	while(!m_obstacles.empty())
	{
		delete m_obstacles.back();
		m_obstacles.pop_back();
	}
}
//------------------------------------------------------------------------------
ObstacleField& ObstacleField::operator=(const ObstacleField& obstacleField)
{
	m_obstacles = obstacleField.m_obstacles;
	return *this;
}
//------------------------------------------------------------------------------
const ObstacleField::ObstacleVector& ObstacleField::GetObstacles() const
{
	return m_obstacles;
}
//------------------------------------------------------------------------------
const vector<int> ObstacleField::GetObstaclesAtPosition(const VGCVector& position) const
{
	vector<int> obstacleIndexes;
	for(int i=0; i<m_obstacles.size(); i++)
	{
		double distance = GetLength(position, m_obstacles[i]->GetPosition());
		if(distance <= m_obstacles[i]->GetRadius())
		{
			obstacleIndexes.push_back(i);
		}
	}

	return obstacleIndexes;
}
//------------------------------------------------------------------------------
const vector<int> ObstacleField::GetObstaclesBetweenPositions(const VGCVector& from, const VGCVector& to) const
{
	vector<int> obstacleIndexes;
	for(int i=0; i<m_obstacles.size(); i++)
	{
		
		if(lineInCircle(from.getX(), from.getY(), to.getX(), to.getY(), m_obstacles[i]->GetPosition().getX(), m_obstacles[i]->GetPosition().getY(), m_obstacles[i]->GetRadius()))
		{
			obstacleIndexes.push_back(i);
		}
	}

	return obstacleIndexes;
}
//------------------------------------------------------------------------------
int ObstacleField::GetNumObstacles() const
{
	return m_obstacles.size();
}
//------------------------------------------------------------------------------
double ObstacleField::GetObstacleCost(int index) const
{
	if(index >= m_obstacles.size() || index < 0 || m_obstacles.size() == 0)
		return -1;

	return m_obstacles[index]->GetCost();
}
//------------------------------------------------------------------------------
int ObstacleField::GetWidth() const
{
	return m_width;
}
//------------------------------------------------------------------------------
int ObstacleField::GetHeight() const
{
	return m_height;
}
//------------------------------------------------------------------------------
double ObstacleField::GetMaxObstacleCost() const
{
	double maxCost = 0;
	double currentCost = 0;
	int obstacleCount = m_obstacles.size();
	for(int i=0; i<obstacleCount; i++)
	{
		currentCost = m_obstacles[i]->GetCost();
		for(int j=0; j<obstacleCount; j++)
		{
			if(GetLength(m_obstacles[j]->GetPosition(), m_obstacles[i]->GetPosition()) < (m_obstacles[i]->GetRadius() + m_obstacles[j]->GetRadius()))
			{
				currentCost += m_obstacles[j]->GetCost();
			}
		}
		if(maxCost < currentCost)
		{
			maxCost = currentCost;
		}
	}

	return maxCost;
}
//------------------------------------------------------------------------------
double ObstacleField::GetLength(const VGCVector& from, const VGCVector& to) const
{
	double xd = to.getX() - from.getX();
	double yd = to.getY() - from.getY();

	return sqrt((xd*xd) + (yd*yd));
}
//------------------------------------------------------------------------------