#include "Actor.h"
#include <sstream>
#include "Values.h"


// Broken 7 pattern
const double number[64] =
{
	1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 1, 1, 1, 1, 1,
};

Actor::Actor() :
	m_neuralNetwork(NeuralNetwork()),
	m_pattern(Pattern()),
	m_finalOutput(0),
	m_patternFound(false),
	m_patternCount(1)
{
	for(int i=0; i<64; ++i)
		m_brokenSeven.push_back(number[i]);
}

Actor::~Actor()
{
}

void Actor::TrainAndTest()
{
	TrainNetwork();
	TestForMatch();
}

void Actor::Render(sf::RenderWindow& window)
{
	std::stringstream ss;
	ss << "Neuron Output: " << m_finalOutput << std::endl;
	ss << "Target Output: " << m_neuralNetwork.GetExpectedValues()[0] << std::endl;
	ss << "Error Value: " << m_neuralNetwork.CalculateErrorValue(m_neuralNetwork.GetExpectedValues()[0], m_finalOutput) << std::endl;
	ss << "Pattern Count: " << m_patternCount << std::endl;
	ss << "Pattern Found: " << m_patternFound << std::endl;
	ss << "Total Times Trained: " << m_neuralNetwork.TrainingCount() << std::endl;
	

	sf::Font font;
	font.loadFromFile("framd.ttf");
	sf::Text text(ss.str(), font);
	text.setCharacterSize(12);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Yellow);

	window.draw(text);
}

bool Actor::TestForMatch()
{
	// Test if the network can recognize a broken seven
	m_finalOutput = m_neuralNetwork.Calculate(m_brokenSeven)[0];	
	
	// Calculate error value and if it is under a threshold then the pattern i found
	if(m_neuralNetwork.CalculateErrorValue(m_neuralNetwork.GetExpectedValues()[0], m_finalOutput) <= Values::nn_errorThreshold)
		m_patternFound = true;
	else
		m_patternFound = false;

	return m_patternFound;
}

bool Actor::TrainNetwork()
{
	if(!m_neuralNetwork.Train(&m_pattern))
	{
		return false;
	}
	return true;
}