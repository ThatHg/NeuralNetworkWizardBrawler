#include "NeuralNetwork.h"
#include "Pattern.h"
#include "Values.h"
#include <cmath>
#include <iostream>

NeuralNetwork::NeuralNetwork() : 
	m_neuronsPerHiddenLayer(Values::nn_neuronsPerHiddenLayer),
	m_hiddenLayerCount(Values::nn_hiddenLayerCount),
	m_outputCount(Values::nn_outputCount),
	m_inputCount(Values::nn_inputCount),
	m_useSigmoid(Values::nn_useSigmoid),
	m_trainingCount(0),
	m_networkTraied(false),
	m_totalError(7777)
{
	Initialize();
}

void NeuralNetwork::Initialize()
{
	if(m_hiddenLayerCount <= 0)
	{
		m_layers.push_back(NeuronLayer(m_outputCount, m_inputCount));
		return;
	}

	// First layer
	m_layers.push_back(NeuronLayer(m_neuronsPerHiddenLayer, m_inputCount));

	// Hidden layers
	for(int i=0; i<m_hiddenLayerCount-1; ++i)
	{
		m_layers.push_back(NeuronLayer(m_neuronsPerHiddenLayer, m_neuronsPerHiddenLayer));
	}

	// Output layer
	m_layers.push_back(NeuronLayer(m_outputCount, m_neuronsPerHiddenLayer));
}

std::vector<double> NeuralNetwork::Calculate(const std::vector<double>& inputs)
{
	int					inputIndex	= 0;
	double				inputTotal	= 0;

	std::vector<double> temp		= inputs;
	std::vector<double> outputs;

	// Dont have the correct amount of inputs, then just return empty vector
	if(temp.size() != m_inputCount)
		return outputs;

	for(int i=0; i<m_layers.size(); ++i)
	{
		// Store the old value of outputs in temp for the next output calculation
		if(i > 0)
			temp = outputs;

		outputs.clear();
		// Calculate every neurons activition value and put it through a sigmoid function
		for(int j=0; j<m_layers[i].CountNeurons(); ++j)
		{
			inputTotal = 0;
			int inputCount = m_layers[i].Neurons()[j].Count();

			// Iterate through every weight and input, but skipp the last which is the BIAS
			inputIndex = 0;
			for(int k=0; k<inputCount - 1; ++k)
				inputTotal += m_layers[i].Neurons()[j].Weights()[k] * temp[inputIndex++];

			inputTotal += m_layers[i].Neurons()[j].Weights()[inputCount - 1] * Values::nn_bias;

			// Put inputTotal through a sigmoid function to get the final output value
			double sigmoid = Sigmoid(inputTotal);
			m_layers[i].Neurons()[j].SetInputValue(sigmoid);
			outputs.push_back(sigmoid);
		}
	}

	return outputs;
}

void NeuralNetwork::SetWeights(const std::vector<double>& weights)
{
	std::vector<double>::const_iterator first	= weights.begin();
	std::vector<double>::const_iterator last	= weights.begin();
	int neuronCount = 0;

	for(int i=0; i<m_hiddenLayerCount + 1; ++i)
	{
		for(int j=0; j<m_layers[i].CountNeurons(); ++j)
		{
			neuronCount = m_layers[i].Neurons()[j].Count();
			last		+=  neuronCount - 1;

			m_layers[i].Neurons()[j].SetWeights(std::vector<double>(first, last));

			last	+= 1;
			first	+= neuronCount;
		}
	}
}

int NeuralNetwork::WeightsCount() const
{
	int numWeights = 0;

	// Get the total number of weights in the network
	for(int i=0; i<m_hiddenLayerCount + 1; ++i)
	{
		for(int j=0; j<m_layers[i].CountNeurons(); ++j)
		{
			numWeights += m_layers[i].Neurons()[j].Count();
		}
	}

	return numWeights;
}

const std::vector<double>&	NeuralNetwork::Weights()
{
	m_weights.clear();

	for(int i=0; i<m_hiddenLayerCount + 1; ++i)
	{
		for(int j=0; j<m_layers[i].CountNeurons(); ++j)
		{
			for(int k=0; k<m_layers[i].Neurons()[j].Count(); ++k)
			{
				m_weights.push_back(m_layers[i].Neurons()[j].Weights()[k]);
			}
		}
	}

	return m_weights;
}

double NeuralNetwork::Sigmoid(double activation, double flatness) const
{
	return 1 / (1 + pow(Values::e_constant, (-activation)/flatness));
}

int NeuralNetwork::Step(double activation, double limit) const
{
	if(activation >= limit)
		return 1;
	else
		return 0;
}

bool NeuralNetwork::TrainNet(std::vector<double>& inputVector, std::vector<double>& outputVector)
{
	m_totalError	= 0;
	double errorVal = 0;
	std::vector<double> outputs;
	std::vector<double>	weights;
	std::vector<Neuron> hiddenNeurons = m_layers[0].Neurons(), 
						outputNeurons = m_layers[m_layers.size() - 1].Neurons();
	

	outputs = Calculate(inputVector);
	std::cout << "last output: \t"  << outputs[0];
	if(outputs.size() == 0)
		return false;

	for(int j=0; j<m_outputCount; ++j)
	{
		errorVal = 0;
		// Calculate error value ( Error = (expectedOutput - realOutput) * realOutput(1 - realOutput))
		errorVal = (outputVector[j] - outputs[j]) * outputs[j] * (1 - outputs[j]);

		
		m_totalError += (outputVector[j] - outputs[j]) * (outputVector[j] - outputs[j]);

		// Store error value within neuron
		m_layers[m_layers.size()-1].Neurons()[j].SetErrorValue(errorVal);

		// If everything has worked as it should, this check should be true
		if(hiddenNeurons.size() == weights.size()-1)
		{
			// Skipp updating the weight for bias, hence -1
			// Adjusting neuron weights
			for(size_t k=0; k<weights.size() - 1; ++k)
			{
				m_layers[m_layers.size()-1].Neurons()[k].AddToWeight(errorVal * Values::nn_learingRate * hiddenNeurons[k].InputValue(),k);
			}

			// The bias
			m_layers[m_layers.size()-1].Neurons()[m_neuronsPerHiddenLayer].AddToWeight(errorVal * Values::nn_learingRate * Values::nn_bias, m_neuronsPerHiddenLayer);
		}
	}
		

	for(size_t j=0; j<hiddenNeurons.size(); ++j)
	{
		errorVal = 0;
		// Iterate through every neuron in the output layer and sum their weights * error to get the neurons total errorValue
		for(size_t k=0; k<outputNeurons.size(); ++k)
		{
			errorVal += outputNeurons[k].ErrorValue() * outputNeurons[k].Weights()[j];
		}

		// Calculate error
		errorVal *= hiddenNeurons[j].InputValue() * (1 - hiddenNeurons[j].InputValue());

		// Adjust the error.
		for(int k=0; k<m_inputCount; ++k)
		{
			m_layers[0].Neurons()[j].AddToWeight(errorVal * Values::nn_learingRate * inputVector[j], k);
		}

		m_layers[0].Neurons()[j].AddToWeight(errorVal * Values::nn_learingRate * Values::nn_bias, m_inputCount);
	}
	
	return true;
}

bool NeuralNetwork::Train(Pattern* pattern)
{
	std::vector<double> trainingPattern	= pattern->GetTrainingPattern();
	std::vector<double> expectedValue	= pattern->GetExpectedValue();
	m_expectedValues.push_back(expectedValue[0]);

	// Train the net until it reaches below a threshold
	while(m_totalError > Values::nn_errorThreshold)
	{
		std::cout << "\t Error: \t" << m_totalError << std::endl;
		TrainNet(trainingPattern, expectedValue);
		m_trainingCount++;
	}

	m_networkTraied = true;

	return true;
}

bool NeuralNetwork::Trained() const
{
	return m_networkTraied;
}

double NeuralNetwork::GetTotalError() const
{
	return m_totalError;
}

int NeuralNetwork::TrainingCount() const
{
	return m_trainingCount;
}

const std::vector<double>& NeuralNetwork::GetExpectedValues() const
{
	return m_expectedValues;
}

double NeuralNetwork::CalculateErrorValue(double target, double outputFromNeuron)
{
	return ((target - outputFromNeuron) *  outputFromNeuron * (1 - outputFromNeuron));
}