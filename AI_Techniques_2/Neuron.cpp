#include "Neuron.h"
#include "Helper.h"
#include <iostream>

using namespace std;

Neuron::Neuron(const std::vector<double>& inputs, const std::vector<double>& weights, const bool justRaw) :
	m_rawSum(-1.0),
	m_activation(-1.0),
	m_error(0.0),
	m_oldWeight(0.0),
	m_isRaw(justRaw),
	m_inputs(inputs),
	m_weights(weights)
{
}

Neuron::~Neuron()
{
}

Neuron::Neuron(const Neuron& neuron) :
	m_rawSum(neuron.m_rawSum),
	m_activation(neuron.m_activation),
	m_error(neuron.m_error),
	m_oldWeight(neuron.m_oldWeight),
	m_isRaw(neuron.m_isRaw),
	m_inputs(neuron.m_inputs),
	m_weights(neuron.m_weights)
{
}

Neuron& Neuron::operator=(const Neuron& neuron)
{
	m_rawSum		= neuron.m_rawSum;
	m_activation	= neuron.m_activation;
	m_error			= neuron.m_error;
	m_oldWeight		= neuron.m_oldWeight;
	m_isRaw			= neuron.m_isRaw;
	m_inputs		= neuron.m_inputs;
	m_weights		= neuron.m_weights;
	
	return *this;
}

void Neuron::Update()
{
	if(m_inputs.size() != m_weights.size())
	{
		cerr << "\nERROR: m_inputs.size() != m_weights.size() in Neuron.";
		return;
	}

	double netInput = 0;
	for(size_t i = 0; i < m_inputs.size(); ++i)
	{
		netInput += m_inputs[i] * m_weights[i];	
	}
	m_rawSum			= netInput;

	if(m_isRaw == true)
		m_activation	= m_rawSum;
	else
		m_activation	= Sigmoid(netInput, 1.0);
}

const double Neuron::GetActivation() const
{
	return m_activation;
}

const double Neuron::GetRawSum() const
{
	return m_rawSum;
}

const double Neuron::GetError() const
{
	return m_error;
}

const std::vector<double>& Neuron::GetInputs() const
{
	return m_inputs;
}

const std::vector<double>& Neuron::GetWeights() const
{
	return m_weights;
}

const double Neuron::GetWeight(const int index) const
{
	return m_weights[index];
}

const double Neuron::GetOldWeight() const
{
	return m_oldWeight;
}

void Neuron::SetRaw(const bool raw)
{
	m_isRaw = raw;
}

void Neuron::SetActivation(const double activition)
{
	m_activation = activition;
}

void Neuron::SetError(const double error)
{
	m_error = error;
}

void Neuron::SetInputs(const std::vector<double>& inputs)
{
	m_inputs = inputs;
}

void Neuron::SetWeights(const std::vector<double>& weights)
{
	m_weights = weights;
}

void Neuron::SetWeight(const int index, const double value)
{
	m_weights[index] = value;
}

void Neuron::SetOldWeight(const double weight)
{
	m_oldWeight = weight;
}