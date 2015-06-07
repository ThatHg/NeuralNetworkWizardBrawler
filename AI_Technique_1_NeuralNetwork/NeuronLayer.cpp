#include "NeuronLayer.h"

NeuronLayer::NeuronLayer(int numNeurons, int numLinksPerNeuron) : m_numNeurons(numNeurons)
{
	for(int i=0; i<numNeurons; ++i)
	{
		m_neurons.push_back(Neuron(numLinksPerNeuron));
	}
}

int NeuronLayer::CountNeurons() const
{
	return m_numNeurons;
}

const std::vector<Neuron>&	NeuronLayer::Neurons() const
{
	return m_neurons;
}

std::vector<Neuron>& NeuronLayer::Neurons()
{
	return m_neurons;
}