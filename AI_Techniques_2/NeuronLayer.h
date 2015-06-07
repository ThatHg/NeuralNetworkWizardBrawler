#ifndef NEURON_LAYER_H
#define NEURON_LAYER_H

#include "Neuron.h"
#include <vector>

class NeuronLayer
{
public:
	typedef std::vector<Neuron>	Neurons;

	NeuronLayer(const Neurons& neurons);
	~NeuronLayer();
	NeuronLayer(const NeuronLayer& layer);
	NeuronLayer& operator=(const NeuronLayer& layer);

	void					Update();

	const std::vector<double>&	GetActivations() const;

	Neurons&	GetNeurons();
	void		SetNeurons(const Neurons& neurons);

private:
	Neurons				m_neurons;
	std::vector<double>	m_activations;
};

#endif