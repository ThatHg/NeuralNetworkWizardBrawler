#include "Actor.h"
#include "Pattern.h"
#include "NeuralNetwork.h"

const static int HIDDEN_LAYERS = 1;
const static int NEURON_PER_HIDDEN = 9;

using namespace std;

Actor::Actor() : 
	m_Patterns(new Pattern()),
	m_ANN(new NeuralNetwork(m_Patterns->GetValuesPerPattern(), m_Patterns->GetPatternCount(), HIDDEN_LAYERS, NEURON_PER_HIDDEN)),
	m_matchedPattern(-1),
	m_smoothVectorSize((m_Patterns->GetValuesPerPattern()/2) + 1),
	m_raw(),
	m_smoothed(),
	m_testPattern(),
	m_lastAnswer(),
	m_concentrating(),
	m_shape(6.0f, 30U),
	m_wSaver(),
	m_drawing(false)
{
	m_shape.setFillColor(sf::Color(255,255,255,150));
}

Actor::~Actor()
{
	delete m_ANN;
	delete m_Patterns;
}

Actor::Actor(const Actor& actor) :
	m_Patterns(actor.m_Patterns),
	m_ANN(actor.m_ANN),
	m_matchedPattern(actor.m_matchedPattern),
	m_smoothVectorSize(actor.m_smoothVectorSize),
	m_raw(actor.m_raw),
	m_smoothed(actor.m_smoothed),
	m_testPattern(actor.m_testPattern),
	m_lastAnswer(actor.m_lastAnswer),
	m_concentrating(actor.m_concentrating),
	m_shape(actor.m_shape),
	m_wSaver(actor.m_wSaver),
	m_drawing(actor.m_drawing)
{
}

Actor& Actor::operator=(const Actor& actor)
{
	m_Patterns			= actor.m_Patterns;
	m_ANN				= actor.m_ANN;
	m_matchedPattern	= actor.m_matchedPattern;
	m_smoothVectorSize	= actor.m_smoothVectorSize;
	m_raw				= actor.m_raw;
	m_smoothed			= actor.m_smoothed;
	m_testPattern		= actor.m_testPattern;
	m_lastAnswer		= actor.m_lastAnswer;
	m_concentrating		= actor.m_concentrating;
	m_shape				= actor.m_shape;
	m_wSaver			= actor.m_wSaver;
	m_drawing			= actor.m_drawing;

	return *this;
}

void Actor::Initialize(sf::RenderWindow& window)
{
	// This loads network weights
	//m_wSaver.Load();							
	//m_ANN->Initialize(m_wSaver.GetWeights());

	// This generates new weights
	m_ANN->Initialize();
	m_ANN->Train(m_Patterns, window);
	m_wSaver.Save(m_ANN->GetWeights());
}

void Actor::Update(sf::RenderWindow& window)
{
	if(m_drawing)
		Record(window);
}

void Actor::Render(sf::RenderWindow& window)
{
	for(MouseData::iterator itr = m_raw.begin(); itr != m_raw.end(); ++itr)
	{
		m_shape.setPosition(*itr);
		window.draw(m_shape);
	}
}

void Actor::Evaluate()
{
	if(SmoothMouseData())
	{
		CreateTestData();		// Create data that the neural network can evaluate
		MatchTestData();		// Get output from network from evaluated data
		FindMatchingPattern();	// Use the output to determine the pattern the network recognized
	}
	Clear();				// Clean up the data.
}

const int Actor::GetMatchedPattern() const
{
	return m_matchedPattern;
}

const bool Actor::IsDrawing() const
{
	return m_drawing;
}

void Actor::SetDrawing(const bool drawing)
{
	m_drawing = drawing;
}

void Actor::SetConcentrating(const bool value)
{
	m_concentrating = value;
}

void Actor::Clear()
{
	m_smoothed.clear();
	m_raw.clear();
	m_testPattern.clear();
	m_drawing = false;
}

void Actor::Record(sf::RenderWindow& window)
{
	sf::Vector2f position((float)(sf::Mouse::getPosition(window)).x, (float)(sf::Mouse::getPosition(window).y));
	m_raw.push_back(position);
}

/*Slightly modified Smooth-function from the book "AI Techniques For Game Programming" chapter 9*/
bool Actor::SmoothMouseData()
{
	m_matchedPattern = -1;
	if(m_raw.size() < m_smoothVectorSize)
		return false;

	m_smoothed = m_raw;
	
	float x			= 0;
	float y			= 0;
	double shortest	= 999999;
	double distance	= 0;
	int pointer		= 0;

	while(m_smoothed.size() > m_smoothVectorSize)
	{
		// From m_smoothed[0] to m_smoothed[last] find the shortest span
		for(int i = 2; i < m_smoothed.size() - 1; ++i)
		{
			distance = Distance(m_smoothed[i - 1], m_smoothed[i]);
			if(distance < shortest)
			{
				shortest	= distance;
				pointer		= i;
			}		
		}
		if(pointer == m_smoothed.size())
		{
			return false;
		}
		sf::Vector2f newPoint;
		// Approximate a new middlepoint between the shortest span
		newPoint.x = (m_smoothed[pointer - 1].x + m_smoothed[pointer].x)/2;
		newPoint.y = (m_smoothed[pointer - 1].y + m_smoothed[pointer].y)/2;

		// Replace the first endpoint
		m_smoothed[pointer - 1] = newPoint;

		// Delete the other
		m_smoothed.erase(m_smoothed.begin() + pointer);
	}

	return true;
}

void Actor::CreateTestData()
{
	sf::Vector2f vector;
	for(int i = 1; i < m_smoothVectorSize; ++i)
	{
		vector = m_smoothed[i] - m_smoothed[i-1];
		Normalize(vector);
		m_testPattern.push_back(vector.x);
		m_testPattern.push_back(vector.y);
	}
}

void Actor::MatchTestData()
{
	m_lastAnswer =  m_ANN->CalculateOutput(m_testPattern);
}

void Actor::FindMatchingPattern()
{
	double highetsValue = 0;
	for(int i = 0; i < m_lastAnswer.size(); ++i)
	{
		if(m_lastAnswer[i] > highetsValue)
		{
			highetsValue = m_lastAnswer[i];
			m_matchedPattern = i;
		}
	}
}