#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "NeuronLayer.h"
#include <vector>

class Pattern;

class NeuralNetwork
{
public:
	NeuralNetwork();

	// Calculate output values from given input values and puts the sum of weights*inputs thourgh a step och sigmoid function
	std::vector<double>			Calculate(const std::vector<double>& inputs);		

	int							WeightsCount() const;
	void						SetWeights(const std::vector<double>& weights);
	const std::vector<double>&	Weights();
	bool						Trained() const;
	double						GetTotalError() const;
	int							TrainingCount() const;
	const std::vector<double>&	GetExpectedValues() const;

	// Takes the pattern and uses TrainNet over and over again to train the network
	bool						Train(Pattern* pattern);

	double						CalculateErrorValue(double target, double outputFromNeuron);

private:	
	void						Initialize();

	// This method uses backpropagation to train the net one iteration with given traininginputs and expected outputs
	bool						TrainNet(std::vector<double>& trainingPattern, std::vector<double>& expectedOutput);

	// Activation is the sum of every weight*inputs. Higher value of flatness give a flatter response curve default is 1
	double						Sigmoid(double activation, double flatness = 1) const;

	// If activation is >= limit, then return 1. Default for limit is 0
	int							Step(double activation, double limit = 0) const;


	int							m_neuronsPerHiddenLayer;
	int							m_hiddenLayerCount;
	int							m_outputCount;
	int							m_inputCount;
	bool						m_useSigmoid;

	int							m_trainingCount;			// Keeps an eye on how many times the net needed training until the expected value has been reached
	bool						m_networkTraied;			// True if the network is trained
	double						m_totalError;				// The total sum of every calculated error value of outputs subtracted from expected values

	std::vector<double>			m_expectedValues;			// These are the expected values the networks last output layer should output
	std::vector<double>			m_weights;
	std::vector<NeuronLayer>	m_layers;
	
};

#endif