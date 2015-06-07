/*
	This class uses the neural network
	and render stats neural network stats
*/

#ifndef ACTOR_H
#define ACTOR_H

#include "Pattern.h"
#include <SFML\Graphics.hpp>
#include <vector>
#include "NeuralNetwork.h"

class Actor
{
public:
	Actor();
	~Actor();
	void Render(sf::RenderWindow& window);
	void TrainAndTest();

private:
	NeuralNetwork		m_neuralNetwork;
	Pattern				m_pattern;

	// network stats
	double				m_finalOutput;
	bool				m_patternFound;
	int					m_patternCount;
	std::vector<double> m_brokenSeven;

	// Try to find a pattern the network has learned.
	bool				TestForMatch();
	
	bool				TrainNetwork();

};

#endif