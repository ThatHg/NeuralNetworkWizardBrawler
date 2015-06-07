#ifndef HELPER_H
#define HELPER_H

#include <math.h>
#include <random>
#include <SFML\Graphics.hpp>

#define PI (3.141592653589793)
#define E_CONSTANT (2.71828182845904523536028747135266250)

inline float min(float a, float b)
{
	if(a < b)
		return a;

	return b;
}

inline float max(float a, float b)
{
	if(a > b)
		return a;

	return b;
}

inline double Length(const sf::Vector2f& vector)
{
	return std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

inline double Distance(const sf::Vector2f& source, const sf::Vector2f& target)
{
	double xD = target.x - source.x;
	double yD = target.y - source.y;
	return std::sqrt(xD * xD + yD * yD);
}

inline void Normalize(sf::Vector2f& vector)
{
	double length = Length(vector);
	if(length != 0)
	{
		vector.x = vector.x/float(length);
		vector.y = vector.y/float(length);
	}
}

inline float RotationDeg2D(sf::Vector2f& from, sf::Vector2f to)
{
	float dx = to.x - from.x;
	float dy = to.y - from.y;

	sf::Vector2f up(0.0f, -1.0f);

	float angle_a = std::atan2(up.y, up.x);
	float angle_b = std::atan2(dy, dx);

	float radian_aTob = angle_b - angle_a;

	float degree = float(radian_aTob * (180/PI));
	if(degree < 0)
		degree += 360;

	return degree;
}

inline double RotationRad2D(sf::Vector2f from, sf::Vector2f to)
{
	float dx = to.x - from.x;
	float dy = to.y - from.y;

	sf::Vector2f up(0.0f, -1.0f);

	float angle_a = std::atan2(up.y, up.x);
	float angle_b = std::atan2(dy, dx);

	float radian_aTob = angle_b - angle_a;
	return radian_aTob;
}

inline double Random(double a, double b)
{
	std::random_device					randomDevice;
	std::mt19937						marsenneTwister(randomDevice());
	std::uniform_real_distribution<>	dist(a, b);

	return dist(marsenneTwister);
}

inline double Sigmoid(double activation, double flatness)
{
	return 1 / (1 + pow(E_CONSTANT, (-activation)/flatness));
}

inline double CalculateError(double target, double activation)
{
	return (target - activation) * (activation * (1 - activation));
}

 /* ************************************************************************************
	This code is taken from http://flassari.is/2008/11/line-line-intersection-in-cplusplus/
	and modified to fit my needs.
*/
inline bool Intersection(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4) 
{
	// Epsilon to compensate for rounding errors
	const float epsilon = 0.00001f;

	// Store the values for fast access and easy
	// equations-to-code conversion
	float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
	float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
 
	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) return false;
 
	// Get the x and y
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
	float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
 
	// Check if the x and y coordinates are within both lines
	if (x < (min(x1, x2) - epsilon) ||
		x > (max(x1, x2) + epsilon) ||
		x < (min(x3, x4) - epsilon) ||
		x > (max(x3, x4) + epsilon))
				return false;
	if (y < (min(y1, y2) - epsilon) ||
		y > (max(y1, y2) + epsilon) ||
		y < (min(y3, y4) - epsilon) ||
		y > (max(y3, y4) + epsilon))
				return false;
	/*
	// Point of intersection if needed later
	sf::Vertex* ret = new sf::Vertex();
	ret->position.x = x;
	ret->position.y = y;
	*/
	// Return true if there is an intersection
	return true;
}
/*************************************************************/

#endif