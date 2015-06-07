#ifndef NEURON_LAYER_H
#define NEURON_LAYER_H

#include "Neuron.h"
#include <vector>

class NeuronLayer
{
public:
	NeuronLayer(int numNeurons, int numLinksPerNeuron);

	const std::vector<Neuron>&	Neurons() const;
	std::vector<Neuron>&		Neurons();
	int							CountNeurons() const;
	
private:
	std::vector<Neuron>	m_neurons;
	int					m_numNeurons;
};

#endif