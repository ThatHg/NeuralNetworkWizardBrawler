#include "NeuronLayer.h"

NeuronLayer::NeuronLayer(const Neurons& neurons) :
	m_neurons(neurons),
	m_activations()
{
	for(int i = 0; i < m_neurons.size(); ++i)
	{
		m_neurons[i].Update();	// Calculate activation value
		m_activations.push_back(m_neurons[i].GetActivation());
	}
}

NeuronLayer::~NeuronLayer()
{
}

NeuronLayer::NeuronLayer(const NeuronLayer& layer) : 
	m_neurons(layer.m_neurons),
	m_activations(layer.m_activations)
{
}

NeuronLayer& ::NeuronLayer::operator=(const NeuronLayer& layer)
{
	m_neurons = layer.m_neurons;
	m_activations = layer.m_activations;

	return *this;
}

void NeuronLayer::Update()
{
	m_activations.clear();
	for(int i = 0; i < m_neurons.size(); ++i)
	{
		m_neurons[i].Update();	// Calculate activation value
		m_activations.push_back(m_neurons[i].GetActivation());
	}
}

const std::vector<double>& NeuronLayer::GetActivations() const
{
	return m_activations;
}

NeuronLayer::Neurons&	NeuronLayer::GetNeurons()
{
	return m_neurons;
}

void NeuronLayer::SetNeurons(const Neurons& neurons)
{
	m_neurons = neurons;
}