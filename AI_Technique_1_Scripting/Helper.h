#ifndef HELPER_H
#define HELPER_H

#include <math.h>
#include <random>
#include <SFML\Graphics.hpp>

#define PI (3.141592653589793)


inline double Length(sf::Vector2f vector)
{
	return std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
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

#endif