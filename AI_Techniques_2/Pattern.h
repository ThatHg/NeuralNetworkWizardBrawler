#ifndef PATTERN_H
#define PATTERN_H

#include <vector>

class Pattern
{
public:
	
	Pattern();
	~Pattern();
	Pattern(const Pattern& pattern);
	Pattern& operator=(const Pattern& pattern);

	const int								GetPatternCount()		const;
	const int								GetValuesPerPattern()	const;
	const std::vector<std::vector<double>>&	GetTrainingPatterns()	const;
	const std::vector<std::vector<double>>&	GetExpectedValues()		const;

	void				SetTrainingPatterns(const std::vector<std::vector<double>>& trainingPatterns);
	void				SetExpectedValues(const std::vector<std::vector<double>>& expectedValues);
	
private:
	int									m_patternCount;
	int									m_valuesPerPattern;
	std::vector<std::vector<double>>	m_trainingPatterns;
	std::vector<std::vector<double>>	m_expectedValues;
};

#endif