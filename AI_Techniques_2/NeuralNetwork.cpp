#include "NeuralNetwork.h"
#include "Values.h"
#include "Pattern.h"
#include <iostream>
#include <sstream>

using namespace std;

NeuralNetwork::NeuralNetwork(const int inputCount, const int outputCount, const int hiddenCount, const int neuronsPerHidden) :
	m_layers(),
	m_outputs(),
	m_netError(999999),
	m_epochCount(0),
	m_inputCount(inputCount),
	m_outputCount(outputCount),
	m_hiddenCount(hiddenCount),
	m_neuronsPerHidden(neuronsPerHidden),
	m_weights()
{
	m_clock.restart();
}

NeuralNetwork::~NeuralNetwork()
{
}
	
NeuralNetwork::NeuralNetwork(const NeuralNetwork& network) :
	m_layers(network.m_layers),
	m_outputs(network.m_outputs),
	m_netError(network.m_netError),
	m_epochCount(network.m_epochCount),
	m_inputCount(network.m_inputCount),
	m_outputCount(network.m_outputCount),
	m_hiddenCount(network.m_hiddenCount),
	m_neuronsPerHidden(network.m_neuronsPerHidden),
	m_weights(network.m_weights)
{
}

NeuralNetwork& NeuralNetwork::operator=(const NeuralNetwork& network)
{
	m_layers			= network.m_layers;
	m_outputs			= network.m_outputs;
	m_netError			= network.m_netError;
	m_epochCount		= network.m_epochCount;
	m_inputCount		= network.m_inputCount;
	m_outputCount		= network.m_outputCount;
	m_hiddenCount		= network.m_hiddenCount;
	m_neuronsPerHidden	= network.m_neuronsPerHidden;
	m_weights			= network.m_weights;

	return *this;
}

void NeuralNetwork::Save()
{
	m_weights.clear();
	for(int i=1; i<m_layers.size(); ++i)
	{
		int NEURONS = 0;
		if(i == 1)
			NEURONS = m_layers[i].GetNeurons().size() - 1;
		else
			NEURONS = m_layers[i].GetNeurons().size();
		for(int j=0; j<NEURONS; ++j)
		{
			const int WEIGHTS = m_layers[i].GetNeurons()[j].GetWeights().size();
			for(int k=0; k<WEIGHTS; ++k)
			{
				m_weights.push_back(m_layers[i].GetNeurons()[j].GetWeights()[k]);
			}
		}
	}
}

void NeuralNetwork::Initialize(const vector<double>& savedWeights)
{
	//  Input Layer
	NeuronLayer::Neurons	neurons;
	vector<double>			weights;
	vector<double>			inputs;
	int						w_index = 0;

	for(int input = 0; input < m_inputCount; ++input)
	{
		neurons.push_back(Neuron(vector<double>(1,0.0),vector<double>(1,1.0), true));
	}
	neurons.push_back(Neuron(vector<double>(1,Values::nn_bias),vector<double>(1,1.0), true));
	m_layers.push_back(neurons);

	//	Hidden Layer
	for(int hidLyr = 0; hidLyr < m_hiddenCount; ++hidLyr)
	{
		neurons.clear();
		for(int neuron = 0; neuron < m_neuronsPerHidden; ++neuron)
		{
			if(hidLyr == 0)
			{
				for(int inNeuron = 0; inNeuron < m_inputCount; ++inNeuron)
				{
					weights.push_back(savedWeights[w_index]);
					w_index++;
					inputs.push_back(0.0);
				}
			}
			else
			{
				for(int inNeuron = 0; inNeuron < m_neuronsPerHidden; ++inNeuron)
				{
					weights.push_back(savedWeights[w_index]);
					w_index++;
					inputs.push_back(0.0);
				}
			}
			// BIAS from previous layer to this
			weights.push_back(savedWeights[w_index]);
			w_index++;
			inputs.push_back(Values::nn_bias);
			neurons.push_back(Neuron(inputs, weights, false));
			neurons.back().SetRaw(false);
			inputs.clear();
			weights.clear();
		}
		neurons.push_back(Neuron(vector<double>(1,Values::nn_bias),vector<double>(1,1.0), true));
		m_layers.push_back(neurons);
	}

	//	Output Layer
	neurons.clear();
	inputs.clear();
	weights.clear();
	for(int output = 0; output < m_outputCount; ++output)
	{
		for(int inNeuron = 0; inNeuron < m_layers[m_layers.size()-1].GetNeurons().size() - 1; ++inNeuron)
		{
			weights.push_back(savedWeights[w_index]);
			w_index++;
			inputs.push_back(0.0);
		}
		// BIAS from previous layer
		weights.push_back(savedWeights[w_index]);
		w_index++;
		inputs.push_back(Values::nn_bias);

		neurons.push_back(Neuron(inputs, weights, false));
		inputs.clear();
		weights.clear();
	}
	m_layers.push_back(neurons);
}

void NeuralNetwork::Initialize()
{
	//  Input Layer
	NeuronLayer::Neurons	neurons;
	vector<double>			weights;
	vector<double>			inputs;

	for(int input = 0; input < m_inputCount; ++input)
	{
		neurons.push_back(Neuron(vector<double>(1,0.0),vector<double>(1,1.0), true));
	}
	neurons.push_back(Neuron(vector<double>(1,Values::nn_bias),vector<double>(1,1.0), true));
	m_layers.push_back(neurons);

	//	Hidden Layer
	for(int hidLyr = 0; hidLyr < m_hiddenCount; ++hidLyr)
	{
		neurons.clear();
		for(int neuron = 0; neuron < m_neuronsPerHidden; ++neuron)
		{
			if(hidLyr == 0)
			{
				for(int inNeuron = 0; inNeuron < m_inputCount; ++inNeuron)
				{
					weights.push_back(Random(-1.0, 1.0));
					inputs.push_back(0.0);
				}
			}
			else
			{
				for(int inNeuron = 0; inNeuron < m_neuronsPerHidden; ++inNeuron)
				{
					weights.push_back(Random(-1.0, 1.0));
					inputs.push_back(0.0);
				}
			}
			// BIAS from previous layer to this
			weights.push_back(Random(-1.0, 1.0));
			inputs.push_back(Values::nn_bias);
			neurons.push_back(Neuron(inputs, weights, false));
			neurons.back().SetRaw(false);
			inputs.clear();
			weights.clear();
		}
		neurons.push_back(Neuron(vector<double>(1,Values::nn_bias),vector<double>(1,1.0), true));
		m_layers.push_back(neurons);
	}

	//	Output Layer
	neurons.clear();
	inputs.clear();
	weights.clear();
	for(int output = 0; output < m_outputCount; ++output)
	{
		for(int inNeuron = 0; inNeuron < m_layers[m_layers.size()-1].GetNeurons().size() - 1; ++inNeuron)
		{
			weights.push_back(Random(-1.0, 1.0));
			inputs.push_back(0.0);
		}
		// BIAS from previous layer
		weights.push_back(Random(-1.0, 1.0));
		inputs.push_back(Values::nn_bias);

		neurons.push_back(Neuron(inputs, weights, false));
		inputs.clear();
		weights.clear();
	}
	m_layers.push_back(neurons);
}

void NeuralNetwork::Train(const Pattern* trainingPatterns, sf::RenderWindow& window)
{
	vector<vector<double>> training			= trainingPatterns->GetTrainingPatterns();
	vector<vector<double>> expectedValues	= trainingPatterns->GetExpectedValues();
	Render(window);
	while(m_netError > Values::nn_errorThreshold)
	{
		TrainingEpoch(training, expectedValues);
		m_epochCount ++;
		if(m_clock.getElapsedTime().asSeconds() >= 1)
		{
			Render(window);
			m_clock.restart();
		}
	}
	Save();
}

const vector<double>& NeuralNetwork::CalculateOutput(const vector<double>& inputs)
{
	// Put the inputs inside the first layer
	for(int input = 0; input < inputs.size(); ++input)
	{
		vector<double> in(1, inputs[input]);
		m_layers[0].GetNeurons()[input].SetInputs(in);
	}
	// Calculate new activition value for every neuron in this layer
	// just set activition value to input value for the first layer neurons
	// (update( true ) = is input layer )
	m_layers[0].Update();

	for(int lyr = 1; lyr < m_layers.size(); ++lyr)
	{
		const int NEURON_COUNT = m_layers[lyr].GetNeurons().size();
		for(int neuron = 0; neuron < NEURON_COUNT; ++neuron)
		{
			// inputs = sigmoid values from past layer
			
			if(lyr != m_layers.size()-1 && NEURON_COUNT - 1 == neuron)
				m_layers[lyr].GetNeurons()[neuron].SetInputs(vector<double>(1, Values::nn_bias));	// BIAS
			else
				m_layers[lyr].GetNeurons()[neuron].SetInputs(m_layers[lyr-1].GetActivations());
		}
		m_layers[lyr].Update();
	}

	m_outputs = m_layers.back().GetActivations();

	return m_layers.back().GetActivations();
}

const double NeuralNetwork::GetNetError() const
{
	return m_netError;
}

const NeuralNetwork::Layers& NeuralNetwork::GetLayers() const
{
	return m_layers;
}

const vector<double>& NeuralNetwork::GetWeights() const
{
	return m_weights;
}

void NeuralNetwork::SetLayers(const Layers& layers)
{
	m_layers = layers;
}
	
void NeuralNetwork::TrainingEpoch(vector<vector<double>>& trainingPatterns, vector<vector<double>>& expectedValues)
{
	m_netError = 0;
	for(int pattern = 0; pattern < trainingPatterns.size(); ++pattern)
	{
		CalculateOutput(trainingPatterns[pattern]);

		// Start back propagation from output layer
		const int NUM_OUTPUTS = m_outputs.size();
		for(int out = 0; out < NUM_OUTPUTS; ++out)
		{
			// Calculate and set error for neuron
			double error = CalculateError(expectedValues[pattern][out], m_outputs[out]);

			m_layers.back().GetNeurons()[out].SetError(error);

			m_netError += (expectedValues[pattern][out] - m_outputs[out]) * (expectedValues[pattern][out] - m_outputs[out]);

			double oldDelta = 0 ,deltaWeight = 0, newWeight = 0;

			// Adjust weights
			const int WEIGHT_COUNT = m_layers.back().GetNeurons()[out].GetWeights().size();
			for(int weight = 0; weight < WEIGHT_COUNT-1; ++weight)
			{

					oldDelta	= m_layers.back().GetNeurons()[out].GetOldWeight();
					deltaWeight	= (error * Values::nn_learingRate * (m_layers.end()-2)->GetNeurons()[weight].GetActivation()) + (Values::nn_momentum * oldDelta);
					newWeight	= m_layers.back().GetNeurons()[out].GetWeight(weight) + deltaWeight;

				m_layers.back().GetNeurons()[out].SetOldWeight(deltaWeight);
				m_layers.back().GetNeurons()[out].SetWeight(weight, newWeight);
			}
			oldDelta	= m_layers.back().GetNeurons()[out].GetOldWeight();
			deltaWeight	= (error * Values::nn_learingRate * Values::nn_bias) + (Values::nn_momentum * oldDelta);
			newWeight	= m_layers.back().GetNeurons()[out].GetWeight(WEIGHT_COUNT-1) + deltaWeight;
			m_layers.back().GetNeurons()[out].SetOldWeight(deltaWeight);
			m_layers.back().GetNeurons()[out].SetWeight(WEIGHT_COUNT-1, newWeight);
		}

		// Propagate further backwards until we reaches input layer then we´re finished
		double error = 0;
		const int NUM_LAYERS = m_layers.size();
		for(int lyr = NUM_LAYERS-2; lyr >= 1; --lyr)
		{

			// Kolla om bias kommer med i räkningen!!!!!S
			const int NEURON_COUNT = m_layers[lyr].GetNeurons().size();
			for(int neuron = 0; neuron < NEURON_COUNT; ++neuron)
			{
				error = 0;
				// Sum every error from previous layer
				const int PAST_NEURON_COUNT = m_layers[lyr+1].GetNeurons().size();
				for(int past_neuron = 0; past_neuron < PAST_NEURON_COUNT; ++past_neuron)
				{
					error += m_layers[lyr+1].GetNeurons()[past_neuron].GetError();
				}

				// Calculate error of this neuron with previous layers net error
				error *= m_layers[lyr].GetNeurons()[neuron].GetActivation() * (1 - m_layers[lyr].GetNeurons()[neuron].GetActivation());

				double oldDelta = 0 ,deltaWeight = 0, newWeight = 0;

				// Adjust weights
				const int WEIGHT_COUNT = m_layers[lyr].GetNeurons()[neuron].GetWeights().size();
				for(int weight = 0; weight < WEIGHT_COUNT-2; ++weight)
				{
					oldDelta	= m_layers[lyr].GetNeurons()[neuron].GetOldWeight();
					deltaWeight	= (error * Values::nn_learingRate * m_layers[lyr-1].GetNeurons()[weight].GetActivation()) + (Values::nn_momentum * oldDelta);
					newWeight	= m_layers[lyr].GetNeurons()[neuron].GetWeight(weight) + deltaWeight;

					m_layers[lyr].GetNeurons()[neuron].SetOldWeight(deltaWeight);
					m_layers[lyr].GetNeurons()[neuron].SetWeight(weight, newWeight);
				}
				oldDelta	= m_layers[lyr].GetNeurons()[neuron].GetOldWeight();
				deltaWeight	= (error * Values::nn_learingRate * Values::nn_bias) + (Values::nn_momentum * oldDelta);
				newWeight	= m_layers[lyr].GetNeurons()[neuron].GetWeight(WEIGHT_COUNT-1) + deltaWeight;
				m_layers[lyr].GetNeurons()[neuron].SetOldWeight(deltaWeight);
				m_layers[lyr].GetNeurons()[neuron].SetWeight(WEIGHT_COUNT-1, newWeight);
			}
		}
	}
	m_netError /= trainingPatterns.size();
}
void NeuralNetwork::Render(sf::RenderWindow& window)
{
	sf::Font font;
	sf::Text text;
	sf::Vector2f pos;

	font.loadFromFile("Assets/Fonts/consola.ttf");

	pos.x	= window.getSize().x/2;
	pos.y	= window.getSize().y/2;

	double procent =  (Values::nn_errorThreshold / m_netError) * 100;

	window.clear(sf::Color(140,140,140,255));

	text.setFont(font);
	text.setCharacterSize(24);
	text.setColor(sf::Color(120,120,120,255));
	text.setPosition(pos);
	text.setString("Learning Magic");
	window.draw(text);

	pos.x	= window.getSize().x/2 - 500;
	pos.y	= window.getSize().y/2 + 13;
	stringstream ss;
	ss << procent << "%";
	text.setCharacterSize(200);
	text.setPosition(pos);
	text.setString(ss.str());
	window.draw(text);

	pos.y	= window.getSize().y/2 + 214;
	stringstream sss;
	sss << "Error: " << m_netError << "\tEpoch: " << m_epochCount;
	text.setCharacterSize(32);
	text.setPosition(pos);
	text.setString(sss.str());
	window.draw(text);

	window.draw(text);
	window.display();
}