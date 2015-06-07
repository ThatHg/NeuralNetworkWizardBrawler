#include "Pattern.h"

// Training data that should resemble a number 7
const double number[64] =
{
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 1, 1, 1, 0, 0,
	0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};

Pattern::Pattern() : m_expectedValue(1, 1)
{
	// Initialize inputVector with the training set
	// and output with zeros
	for(int i=0; i<64; ++i)
	{
		m_trainingPattern.push_back(number[i]);
	}
}

const std::vector<double>& Pattern::GetTrainingPattern() const
{
	return m_trainingPattern;
}

const std::vector<double>& Pattern::GetExpectedValue() const
{
	return m_expectedValue;
}