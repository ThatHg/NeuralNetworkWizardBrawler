#ifndef ACTOR_H
#define ACTOR_H

#include <SFML\Graphics.hpp>
#include <vector>
#include "WeightSaver.h"

class NeuralNetwork;
class Pattern;

class Actor
{
public:
	Actor();
	~Actor();
	Actor(const Actor& actor);
	Actor& operator=(const Actor& actor);

	void		Initialize(sf::RenderWindow& window);
	void		Update(sf::RenderWindow& window);
	void		Render(sf::RenderWindow& window);

	void		Evaluate();
	const int	GetMatchedPattern()	const;
	const bool	IsDrawing()			const;

	void		SetConcentrating(const bool value);
	void		SetDrawing(const bool drawing);

private:
	typedef std::vector<sf::Vector2f> MouseData;

	void		Clear();
	void		Record(sf::RenderWindow& window);	// Activaties when player holds shift and left mousebutton
	bool		SmoothMouseData();
	void		CreateTestData();
	void		MatchTestData();
	void		FindMatchingPattern();

	Pattern*			m_Patterns;
	NeuralNetwork*		m_ANN;
	int					m_matchedPattern;
	int					m_smoothVectorSize;
	MouseData			m_raw;
	MouseData			m_smoothed;
	std::vector<double> m_testPattern;
	std::vector<double>	m_lastAnswer;
	bool				m_concentrating;
	sf::CircleShape		m_shape;
	WeightSaver			m_wSaver;
	bool				m_drawing;
};

#endif