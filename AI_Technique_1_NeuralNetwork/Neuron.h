/*
	This is a basic neuron stucture. It stores the number of 
	input links	and what weight the inputs have.
*/

#ifndef NEURON_H
#define NEURON_H

#include <vector>

class Neuron
{
public:
	Neuron(int numInputs);

	int							Count() const;
	const std::vector<double>&	Weights() const;
	void						SetWeights(const std::vector<double>& weights);
	void						AddToWeight(const double weight, const int index);
	void						SetErrorValue(const double error);
	void						SetInputValue(const double input);
	double						ErrorValue() const;
	double						InputValue() const;

private:
	int					m_numInputs;
	std::vector<double>	m_weights;
	double				m_inputValue;
	double				m_errorValue;
};

#endif
