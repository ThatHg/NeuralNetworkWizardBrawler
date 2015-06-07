#ifndef NEURON_H
#define NEURON_H

#include <vector>

class Neuron
{
public:
	Neuron(const std::vector<double>& inputs, const std::vector<double>& weights, const bool justRaw);
	~Neuron();
	Neuron(const Neuron& neuron);
	Neuron& operator=(const Neuron& neuron);

	void			Update();

	const double	GetActivation()				const;
	const double	GetRawSum()					const;
	const double	GetError()					const;
	const double	GetWeight(const int index)	const;
	const double	GetOldWeight()				const;

	const std::vector<double>&	GetInputs()		const;
	const std::vector<double>&	GetWeights()	const;

	void			SetActivation(const double activation);
	void			SetError(const double error);
	void			SetWeight(const int index, const double value);
	void			SetOldWeight(const double weight);
	void			SetRaw(const bool raw);

	void			SetInputs(const std::vector<double>& inputs);
	void			SetWeights(const std::vector<double>& weights);

private:
	double	m_rawSum;
	double	m_activation;
	double	m_error;
	double	m_oldWeight;
	// If this neuron is raw, this means its activition should just be calculated like sum (weight*input) sigmoid(sum(w*i))
	// This is nessesary for input neurons and bias neurons.
	bool	m_isRaw;	
	std::vector<double>	m_inputs;
	std::vector<double>	m_weights;	
};

#endif