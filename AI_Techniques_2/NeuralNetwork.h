#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "Neuron.h"
#include "NeuronLayer.h"
#include "Helper.h"
#include <vector>

class Pattern;

class NeuralNetwork
{
public:
	typedef std::vector<NeuronLayer>	Layers;

	NeuralNetwork(const int inputCount, const int outputCount, const int hiddenCount, const int neuronsPerHidden);
	~NeuralNetwork();
	NeuralNetwork(const NeuralNetwork& network);
	NeuralNetwork& operator=(const NeuralNetwork& network);
	void						Save();
	void						Initialize();
	void						Initialize(const std::vector<double>& weights);
	void						Train(const Pattern* trainingPatterns, sf::RenderWindow& window);
	const std::vector<double>&	CalculateOutput(const std::vector<double>& inputs);
	
	const double				GetNetError()	const;
	const Layers&				GetLayers()		const;
	const std::vector<double>&	GetWeights()	const;

	void						SetLayers(const Layers& layers);
	
private:
	void						TrainingEpoch(std::vector<std::vector<double>>& trainingPatterns, std::vector<std::vector<double>>& expectedValues);
	void						Render(sf::RenderWindow& window);

	Layers				m_layers;
	std::vector<double>	m_outputs;
	double				m_netError;
	int					m_epochCount;
	int					m_inputCount;
	int					m_outputCount;
	int					m_hiddenCount;
	int					m_neuronsPerHidden;
	sf::Clock			m_clock;
	std::vector<double>	m_weights;
};

#endif