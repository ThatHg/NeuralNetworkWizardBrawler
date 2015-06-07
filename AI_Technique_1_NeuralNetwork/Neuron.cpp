#include "Neuron.h"
#include <random>

double random(double a, double b);
Neuron::Neuron(int numInputs) : 
	m_numInputs(numInputs+1),
	m_inputValue(0),
	m_errorValue(0)
{
	// Put the weights in vector. +1 is for the BIAS
	for(int i=0; i<numInputs+1; ++i)
	{
		m_weights.push_back(random(-1, 1));
	}
}

int Neuron::Count() const
{
	return m_numInputs;
}

const std::vector<double>&	Neuron::Weights() const
{
	return m_weights;
}

void Neuron::SetWeights(const std::vector<double>& weights)
{
	m_weights.clear();

	for(std::vector<double>::const_iterator itr = weights.begin(); itr != weights.end(); ++itr)
		m_weights.push_back(*itr);
}

void Neuron::SetErrorValue(const double error)
{
	m_errorValue = error;
}

void Neuron::SetInputValue(const double input)
{
	m_inputValue = input;
}

double Neuron::ErrorValue() const
{
	return m_errorValue;
}

double Neuron::InputValue() const
{
	return m_inputValue;
}

void Neuron::AddToWeight(const double weight, const int index)
{
	if(index < m_weights.size() && index > 0)
		m_weights[index] += weight;
}

// Helper function to get random values between two doubles
double random(double a, double b)
{
	std::random_device					randomDevice;
	std::mt19937						marsenneTwister(randomDevice());
	std::uniform_real_distribution<>	dist(a, b);

	return dist(marsenneTwister);
}