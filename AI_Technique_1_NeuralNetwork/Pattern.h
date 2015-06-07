#ifndef PATTERN_H
#define PATTERN_H

#include <vector>

class Pattern
{
public:
	Pattern();

	const std::vector<double>& GetTrainingPattern() const;
	const std::vector<double>& GetExpectedValue() const;
	
private:
	std::vector<double> m_trainingPattern;		// This holds the answer for the right pattern
	std::vector<double> m_expectedValue;		// This holds the attempt to reach the right answer
};

#endif